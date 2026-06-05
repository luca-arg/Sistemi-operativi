#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(void) {
    char cwd[4096];

    if (getcwd(cwd, sizeof(cwd)) == NULL) {
        return 1;
    }

    char **paths = NULL;
    int num_paths = 0;
    int capacity = 0;

    DIR *dir = opendir(".");
    if (!dir) {
        return 1;
    }

    struct dirent *entry;
    struct stat st;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        if (stat(entry->d_name, &st) == -1) {
            continue;
        }

        if (!S_ISREG(st.st_mode)) {
            continue;
        }

        if (num_paths >= capacity) {
            capacity = (capacity == 0) ? 64 : capacity * 2;
            char **new_paths = realloc(paths, capacity * sizeof(char *));
            if (!new_paths) {
                closedir(dir);
                return 1;
            }
            paths = new_paths;
        }

        char full_path[4096 * 2];
        snprintf(full_path, sizeof(full_path), "%s/%s", cwd, entry->d_name);
        paths[num_paths] = strdup(full_path);
        num_paths++;
    }
    
    closedir(dir);



    for (int i = 0; i < num_paths; i++) {

        if (stat(paths[i], &st) == -1) {
            continue;
        }

        int fd = open(paths[i], O_RDONLY);
        if (fd == -1) {
            continue;
        }

        char *buf = malloc(st.st_size + 1);
        if (!buf) {
            close(fd);
            continue;
        }

        ssize_t read_bytes = read(fd, buf, st.st_size);
        close(fd);

        if (read_bytes > 0) {
            int found = 0;
            
            for (int p = 0; p < num_paths && !found; p++) {
                size_t path_len = strlen(paths[p]);
                
                if ((size_t)read_bytes >= path_len) {
                    for (ssize_t j = 0; j <= read_bytes - (ssize_t)path_len; j++) {
                        if (memcmp(buf + j, paths[p], path_len) == 0) {
                            printf("%s\n", paths[i]);
                            found = 1;
                            break;
                        }
                    }
                }
            }
        }
        
        free(buf);
    }

    for (int i = 0; i < num_paths; i++) {
        free(paths[i]);
    }
    free(paths);

    return 0;
}