#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/inotify.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>

#define EVENT_SIZE  (sizeof(struct inotify_event))
#define BUF_LEN     (1024 * (EVENT_SIZE + 16))
#define PATH_MAX 4096

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    int fd = inotify_init();// inizializza inotify ovvero crea un file descriptor per monitorare eventi sui file
    if (fd < 0) {
        return 1;
    }

    int wd = inotify_add_watch(fd, argv[1], IN_CLOSE_WRITE | IN_MOVED_TO);// aggiunge un watch per i file nella directory specificata, sia per la chiusura di un file dopo la scrittura che per lo spostamento di un file nella directory
    if (wd < 0) {
        close(fd);
        return 1;
    }

    char buf[BUF_LEN];

    while (1) {
        int numRead = read(fd, buf, BUF_LEN);// legge gli eventi in arrivo e li memorizza nel buffer. qui viene bloccato finché non arriva un evento, e quando arriva, numRead contiene il numero di byte letti nel buffer
        if (numRead <= 0) {
            break;
        }

        for (char *p = buf; p < buf + numRead; ) {
            struct inotify_event *event = (struct inotify_event *)p;// interpreta i byte letti come un evento inotify. event ora punta alla struttura che descrive l'evento appena letto che contiene informazioni come il nome del file coinvolto e il tipo di evento. al prossimo ciclo, p viene aggiornato per puntare al prossimo evento nel buffer, tenendo conto della dimensione dell'evento e della lunghezza del nome del file (event->len). ci creiamo come degli stampini per leggere tutti gli eventi che sono arrivati in questo ciclo di lettura, e per ogni evento, eseguiamo le azioni necessarie in base al tipo di evento e al nome del file coinvolto

            /*questo è possibile perche la struttura inotify_event è ben definita e ci permette di accedere facilmente alle informazioni sugli eventi. è strutturata come segue: */
            /*
            struct inotify_event {
                int wd;           // Watch descriptor
                uint32_t mask;    // Mask of events
                uint32_t cookie;  // Unique cookie associato all'evento
                uint32_t len;     // Lunghezza del nome del file
                char name[];      // Nome del file (variabile)
            };

            tale struttura ci permette di accedere facilmente alle informazioni sugli eventi, come il nome del file coinvolto (event->name) e la lunghezza del nome del file (event->len). in questo modo possiamo gestire dinamicamente i file che vengono creati o modificati nella directory monitorata, eseguendo le azioni necessarie in base al tipo di evento e al nome del file coinvolto.
            */

            if (event->len > 0) {
                char filepath[PATH_MAX];
                snprintf(filepath, sizeof(filepath), "%s/%s", argv[1], event->name);

                FILE *f = fopen(filepath, "r");
                if (f) {
                    char *exec_path = NULL;
                    size_t len = 0;
                    
                    if (getline(&exec_path, &len, f) != -1) {// getline legge la prima riga del file, che dovrebbe contenere il percorso dell'eseguibile da eseguire. se la lettura ha successo, exec_path conterrà il percorso dell'eseguibile da eseguire e len conterrà la lunghezza della riga letta. se la lettura fallisce, exec_path rimarrà NULL e len rimarrà 0
                        exec_path[strcspn(exec_path, "\n")] = '\0';// rimuove il carattere di nuova linea alla fine del percorso dell'eseguibile, se presente. strcspn restituisce la posizione del primo carattere di nuova linea nella stringa exec_path. a quella posizione viene  sostituito con il carattere null ('\0'), terminando così la stringa in quel punto e rimuovendo il carattere di nuova linea alla fine del percorso dell'eseguibile, se presente. questo è importante perché quando si esegue un comando, non vogliamo che ci siano caratteri di nuova linea o spazi extra che potrebbero causare problemi nell'esecuzione del comando

                        char *cmd_argv[128];
                        int i = 0;
                        char *line = NULL;
                        size_t line_len = 0;

                        while (getline(&line, &line_len, f) != -1 && i < 127) {
                            line[strcspn(line, "\n")] = '\0';
                            cmd_argv[i] = strdup(line);// serve per mantenere una copia della riga letta, in modo che possiamo liberare la memoria allocata per line alla fine del ciclo. se non facessimo questo, cmd_argv[i] punterebbe alla stessa area di memoria di line, e quando liberiamo line alla fine del ciclo, perderemmo anche i dati memorizzati in cmd_argv[i]. utilizzando strdup, creiamo una copia separata della stringa letta, che possiamo gestire e liberare indipendentemente da line
                            i++;
                        }
                        cmd_argv[i] = NULL;

                        pid_t pid = fork();

                        if (pid == -1) {
                            perror("fork");
                            exit(1);
                        } 
                        else if (pid == 0) {
                            execv(exec_path, cmd_argv);
                            exit(1);
                        } 
                        else {
                            waitpid(pid, NULL, 0);
                        }

                        for (int j = 0; j < i; j++) {
                            free(cmd_argv[j]);
                        }
                        free(line);// libera la memoria allocata per line dalla chiamata a getline
                    }
                    free(exec_path);// in questo punto possiamo liberare la memoria allocata per exec_path dalla chiamata a getline
                    fclose(f);
                    
                    unlink(filepath);// rimuove il file dopo averlo letto e processato, in modo che non venga processato di nuovo in futuro. questo è importante perché altrimenti, se il file rimane nella directory monitorata, potrebbe essere letto e processato più volte, causando esecuzioni multiple del comando specificato nel file. rimuovendo il file dopo averlo processato, garantiamo che ogni comando venga eseguito solo una volta e che la directory monitorata rimanga pulita da file temporanei o inutili
                }
            }
            p += EVENT_SIZE + event->len;
        }
    }

    inotify_rm_watch(fd, wd);
    close(fd);
    return 0;
}