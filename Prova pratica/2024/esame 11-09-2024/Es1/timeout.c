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

int main(int argc, char *argv[]) {
    if (argc < 3) {
        return 1;
    }

    long ms = atol(argv[1]); 
    if (ms <= 0) return 1;

    int tfd = timerfd_create(CLOCK_MONOTONIC, 0);
    if (tfd == -1) return 1;

    struct itimerspec ts = {0}; // struttura per specificare il timer da passare a timerfd_settime
    ts.it_value.tv_sec = ms / 1000;
    ts.it_value.tv_nsec = (ms % 1000) * 1000000;

    if (timerfd_settime(tfd, 0, &ts, NULL) == -1) {
        return 1;
    }

    pid_t pid = fork();
    if (pid == -1) {
        return 1;
    }

    if (pid == 0) {
        execvp(argv[2], &argv[2]);// v e p di exec: v: array di stringhe, p: cerca il comando nella PATH, e: termina con NULL. passando &argv[2] si passa l'array di stringhe a partire da argv[2], che contiene il comando e i suoi argomenti. es: se argv è ["timeout", "1000", "ls", "-l"], allora &argv[2] è ["ls", "-l", NULL], che è l'array di stringhe che execvp si aspetta. se execvp fallisce,
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

    if (poll(pfd, 2, -1) == -1) {// poll a cui si passa l'array di strutture pollfd e il numero di file descriptor da monitorare (2 in questo caso) e il timeout (-1 per attendere indefinitamente). poll restituirà quando uno dei file descriptor è pronto per l'operazione specificata negli eventi (POLLIN in questo caso, che indica che c'è qualcosa da leggere). se poll restituisce -1, significa che c'è stato un errore, quindi si uccide il processo figlio e si attende la sua terminazione prima di restituire 1
        kill(pid, SIGKILL);
        waitpid(pid, NULL, 0);
        return 1;
    }

    if (pfd[1].revents & POLLIN) {// verifico se il timer è scaduto controllando se il campo revents del secondo elemento dell'array pfd (che corrisponde al timer) ha il flag POLLIN impostato. se è così, significa che il timer è scaduto e quindi si uccide il processo figlio con kill(pid, SIGKILL);
        kill(pid, SIGKILL);
    }

    waitpid(pid, NULL, 0);

    close(pidfd);
    close(tfd);

    return 0;
}