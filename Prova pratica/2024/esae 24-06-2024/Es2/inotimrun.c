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

    int fd = inotify_init();
    if (fd < 0) {
        return 1;
    }

    int wd = inotify_add_watch(fd, argv[1], IN_CLOSE_WRITE | IN_MOVED_TO);
    if (wd < 0) {
        close(fd);
        return 1;
    }

    char buf[BUF_LEN];

    while (1) {
        int numRead = read(fd, buf, BUF_LEN);
        if (numRead <= 0) {
            break;
        }

        for (char *p = buf; p < buf + numRead; ) {
            struct inotify_event *event = (struct inotify_event *)p;
            
            if (event->len > 0) {
                char filepath[PATH_MAX];
                snprintf(filepath, sizeof(filepath), "%s/%s", argv[1], event->name);

                FILE *f = fopen(filepath, "r");
                if (f) {
                    char *line = NULL;
                    size_t line_len = 0;

                    while (getline(&line, &line_len, f) != -1) {
                        if (strcmp(line, "\n") == 0) {
                            continue;
                        }

                        line[strcspn(line, "\n")] = '\0';
                        char *exec_path = strdup(line);

                        char *cmd_argv[128];
                        int i = 0;

                        while (getline(&line, &line_len, f) != -1 && i < 127) {
                            if (strcmp(line, "\n") == 0) {
                                break;
                            }
                            line[strcspn(line, "\n")] = '\0';
                            cmd_argv[i] = strdup(line);
                            i++;
                        }
                        cmd_argv[i] = NULL;

                        pid_t pid = fork();

                        if (pid == 0) {
                            execv(exec_path, cmd_argv);
                            exit(1);
                        } 
                        else if (pid > 0) {
                            waitpid(pid, NULL, 0);
                        }

                        for (int j = 0; j < i; j++) {
                            free(cmd_argv[j]);
                        }
                        free(exec_path);
                    }
                    free(line);
                    fclose(f);
                    
                    unlink(filepath);
                }
            }
            p += EVENT_SIZE + event->len;
        }
    }

    inotify_rm_watch(fd, wd);
    close(fd);
    return 0;
}