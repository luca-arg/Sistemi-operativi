#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>

void search_dir(const char *dir_path, off_t target_size, ino_t target_ino, dev_t target_dev) {
    DIR *dir = opendir(dir_path);
    if (!dir) return;

    struct dirent *entry;
    struct stat st;
    char path[PATH_MAX];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) continue;
        
        snprintf(path, sizeof(path), "%s/%s", dir_path, entry->d_name);
        
        if (lstat(path, &st) == -1) continue;

        if (S_ISDIR(st.st_mode)) {
            search_dir(path, target_size, target_ino, target_dev);
        } 
        else if (S_ISREG(st.st_mode)) {
            if (st.st_size == target_size) {
                if (st.st_ino != target_ino || st.st_dev != target_dev) {
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

    struct stat target_st;
    if (stat(f_path, &target_st) == -1) {
        return 1;
    }

    search_dir(d_path, target_st.st_size, target_st.st_ino, target_st.st_dev);

    return 0;
}