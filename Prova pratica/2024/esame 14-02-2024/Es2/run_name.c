#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/wait.h>
#include <limits.h>

#define PATH_MAX 4096

void search_and_run(const char *dir_path, int argc, char *argv[]) {
    DIR *dir = opendir(dir_path);
    if (!dir) return;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        char path[PATH_MAX];
        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

        struct stat st;
        if (lstat(path, &st) == -1) continue;

        if (S_ISDIR(st.st_mode)) {
            search_and_run(path, argc, argv);
        }
         else if (S_ISREG(st.st_mode)) {
            if ((st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH)) {
                if (strcmp(entry->d_name, argv[1]) == 0) {
                    pid_t pid = fork();
                    if (pid == 0) {
                        if (chdir(dir_path) == -1) exit(1);

                        char **exec_argv = malloc(argc * sizeof(char *));
                        if (!exec_argv) exit(1);

                        char local_target[PATH_MAX];
                        snprintf(local_target, sizeof(local_target), "./%s", argv[1]);
                        exec_argv[0] = local_target;

                        for (int i = 2; i < argc; i++) {
                            exec_argv[i - 1] = argv[i];
                        }
                        exec_argv[argc - 1] = NULL;

                        execv(local_target, exec_argv);
                        free(exec_argv);
                        exit(1);
                    } 
                    else if (pid > 0) {
                        waitpid(pid, NULL, 0);
                    }
                }
            }
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc < 2) return 1;
    search_and_run(".", argc, argv);
    return 0;
}