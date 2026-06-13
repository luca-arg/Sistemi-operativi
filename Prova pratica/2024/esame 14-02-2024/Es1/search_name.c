#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

#define PATH_MAX 4096

void search_dir(const char *dir_path, const char *target_name) {
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
            search_dir(path, target_name);
        } 
        else if (S_ISREG(st.st_mode)) {
            if ((st.st_mode & S_IXUSR) || (st.st_mode & S_IXGRP) || (st.st_mode & S_IXOTH)) {
                if (strcmp(entry->d_name, target_name) == 0) {
                    int fd = open(path, O_RDONLY);
                    if (fd != -1) {
                        unsigned char magic[4];
                        ssize_t n = read(fd, magic, 4);
                        if (n >= 2 && magic[0] == '#' && magic[1] == '!') {
                            printf("%s: script\n", path);
                        } 
                        else if (n >= 4 && magic[0] == 0x7f && magic[1] == 'E' && magic[2] == 'L' && magic[3] == 'F') {
                            printf("%s: ELF executable\n", path);
                        }
                        close(fd);
                    }
                }
            }
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 2) return 1;
    search_dir(".", argv[1]);
    return 0;
}