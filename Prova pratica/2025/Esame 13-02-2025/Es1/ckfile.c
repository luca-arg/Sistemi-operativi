#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>

void search_dir(const char *dir_path, int mode, const char *target_real, ino_t target_ino, dev_t target_dev) {
    DIR *dir = opendir(dir_path);
    if (!dir) return;

    struct dirent *entry;
    struct stat st;
    char path[PATH_MAX];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);

        if (lstat(path, &st) == -1) {
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            search_dir(path, mode, target_real, target_ino, target_dev);
        } 
        else if (mode == 'l') {
            if (!S_ISLNK(st.st_mode) && st.st_ino == target_ino && st.st_dev == target_dev) {
                printf("%s\n", path);
            }
        }
         else if (mode == 's') {
            if (S_ISLNK(st.st_mode)) {
                char link_real[PATH_MAX];
                if (realpath(path, link_real) != NULL) {
                    if (strcmp(link_real, target_real) == 0) {
                        printf("%s\n", path);
                    }
                }
            }
        }
    }
    closedir(dir);
}



int main(int argc, char *argv[]) {
    if (argc != 4) {
        return 1;
    }

    int mode = 0;

    if (strcmp(argv[1], "-s") == 0) {
        mode = 's';
    }
     else if (strcmp(argv[1], "-l") == 0) {
        mode = 'l';
    } 
    else {
        return 1;
    }

    const char *f_path = argv[2];
    const char *d_path = argv[3];

    struct stat target_st;
    memset(&target_st, 0, sizeof(target_st));
    char target_real[PATH_MAX] = {0};

    if (mode == 'l') {
        if (stat(f_path, &target_st) == -1) {
            return 1;
        }
    } 
    else if (mode == 's') {
        if (realpath(f_path, target_real) == NULL) {
            return 1;
        }
    }

    search_dir(d_path, mode, target_real, target_st.st_ino, target_st.st_dev);

    return 0;
}