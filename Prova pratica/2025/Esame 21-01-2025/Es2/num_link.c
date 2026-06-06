#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>

void search_symlinks(const char *dir_path, const char *target_real) {
    DIR *dir = opendir(dir_path);
    if (!dir) return;

    struct dirent *entry;
    struct stat st;
    char path[PATH_MAX];
    char link_real[PATH_MAX];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;

        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

        if (lstat(path, &st) == -1) continue;

        if (S_ISDIR(st.st_mode)) {
            search_symlinks(path, target_real);
        } 
        else if (S_ISLNK(st.st_mode)) {
            if (realpath(path, link_real) != NULL) {
                if (strcmp(link_real, target_real) == 0) {
                    printf("%s\n", path);
                }
            }
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }

    const char *f_path = argv[1];
    const char *d_path = argv[2];

    char target_real[PATH_MAX];
    if (realpath(f_path, target_real) == NULL) {
        return 1;
    }

    search_symlinks(d_path, target_real);

    return 0;
}