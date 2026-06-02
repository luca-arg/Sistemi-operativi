
#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

void recursive_dir(const char *dir_name, time_t ref_time, ino_t ref_ino) {
    DIR *d = opendir(dir_name);
    if (d == NULL) {
        perror(dir_name);
        return;
    }

    struct dirent *dir;
    char path[1024];

    while ((dir = readdir(d)) != NULL) {
        if (strcmp(dir->d_name, ".") == 0 || strcmp(dir->d_name, "..") == 0) {
            continue;
        }

        snprintf(path, sizeof(path), "%s/%s", dir_name, dir->d_name);

        struct stat st;
        if (lstat(path, &st) == -1) {
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            recursive_dir(path, ref_time, ref_ino);
        } 
        
        else if (st.st_mtime == ref_time) {
            if (stat(path, &st) == 0 && st.st_ino != ref_ino) {
                printf("%s\n", path);
            }
        }
    }
    closedir(d);
}


void process_target(const char *target_path, time_t ref_time, ino_t ref_ino) {
    struct stat st_target; 

    if (stat(target_path, &st_target) == -1) {
        return;
    }

    if (S_ISDIR(st_target.st_mode)) {
        recursive_dir(target_path, ref_time, ref_ino);
    } 
    else {
        struct stat st_l;
        if (lstat(target_path, &st_l) == 0) {
            if (st_l.st_mtime == ref_time && st_target.st_ino != ref_ino) {
                printf("%s\n", target_path);
            }
        }
    }
}



int main(int argc, char *argv[]) {
    if (argc < 2 || argc > 3) {
        return 1;
    }

    struct stat st_ref;
    if (stat(argv[1], &st_ref) == -1) {
        return 1;
    }
    time_t ref_time = st_ref.st_mtime;
    ino_t ref_ino = st_ref.st_ino;

    if (argc == 2) {
        recursive_dir(".", ref_time, ref_ino);
    } 
    else if (argc == 3) {
        process_target(argv[2], ref_time, ref_ino);
    }

    return 0;
}

