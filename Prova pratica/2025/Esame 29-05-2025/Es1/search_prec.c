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

    //ricerca ricorsiva nei file regolari della directory corrente
    //inizio
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
    //fine della ricerca ricorsiva

    
        char full_path[4096*2];
        snprintf(full_path, sizeof(full_path), "%s/%s", cwd, entry->d_name);
        size_t path_len = strlen(full_path);

        int fd = open(entry->d_name, O_RDONLY);
        if (fd == -1) {
            continue;
        }

        char *buf = malloc(st.st_size + 1);
        if (!buf) {
            close(fd);
            continue;
        }

        ssize_t read_bytes = read(fd , buf, st.st_size);

        for (ssize_t i = 0; i <= read_bytes - (ssize_t)path_len; i++) {
            if (memcmp(buf + i, full_path, path_len) == 0) {
                printf("%s\n", full_path);
            }
        }

        
        free(buf);
        close(fd);
    }

    closedir(dir);
    return 0;
}