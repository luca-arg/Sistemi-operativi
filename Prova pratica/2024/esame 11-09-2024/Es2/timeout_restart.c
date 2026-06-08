#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/timerfd.h>
#include <poll.h>
#include <signal.h>
#include <sys/syscall.h>
#include <stdint.h>

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }

    long ms = atol(argv[1]);
    if (ms <= 0) return 1;

    int tfd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (tfd == -1) return 1;

    struct itimerspec ts = {0};
    ts.it_value.tv_sec = ms / 1000;
    ts.it_value.tv_nsec = (ms % 1000) * 1000000;




    while (1) {
        if (timerfd_settime(tfd, 0, &ts, NULL) == -1) {
            return 1;
        }

        pid_t pid = fork();
        if (pid == -1) return 1;

        if (pid == 0) {
            execvp(argv[2], &argv[2]);
            exit(1);
        }

        int pidfd = syscall(SYS_pidfd_open, pid, 0);
        if (pidfd == -1) {
            kill(pid, SIGKILL);
            waitpid(pid, NULL, 0);
            return 1;
        }

        struct pollfd pfd[2];
        pfd[0].fd = pidfd;
        pfd[0].events = POLLIN;
        pfd[1].fd = tfd;
        pfd[1].events = POLLIN;

        if (poll(pfd, 2, -1) == -1) {
            kill(pid, SIGKILL);
            waitpid(pid, NULL, 0);
            return 1;
        }

        if (pfd[0].revents & POLLIN) {
            int status;
            waitpid(pid, &status, 0);
            close(pidfd);

            if (WIFEXITED(status) && WEXITSTATUS(status) == 0) {// wifexited(status) verifica se il processo figlio è terminato normalmente, e wexitstatus(status) restituisce il codice di uscita del processo figlio. se il codice di uscita è 0, significa che il processo figlio è terminato con successo, quindi si chiude il file descriptor pidfd e si esce dal ciclo while con
                break;
            }
             else {
                struct pollfd t_pfd;
                t_pfd.fd = tfd;
                t_pfd.events = POLLIN;
                
                poll(&t_pfd, 1, -1);// attesa solo sul timerfd, se il processo figlio è terminato con un codice di uscita diverso da 0, si attende che il timer scada prima di continuare con la prossima iterazione del ciclo while. in questo modo, si garantisce che il processo figlio abbia un tempo limitato per completare la sua esecuzione prima di essere terminato e riavviato.
                
                uint64_t exp;
                read(tfd, &exp, sizeof(exp));
                
                continue;
            }
        } 
        else if (pfd[1].revents & POLLIN) {
            kill(pid, SIGKILL);
            waitpid(pid, NULL, 0);
            close(pidfd);
            break;
        }
    }

    close(tfd);
    return 0;
}