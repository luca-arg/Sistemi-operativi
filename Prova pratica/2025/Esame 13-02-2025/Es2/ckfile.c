#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <dirent.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>

void compare_content(const char *path, const char *target_path, int p_len, off_t target_size, ino_t target_ino) {
    struct stat st;
    if (stat(path, &st) == -1) return;

    if (st.st_ino == target_ino) return;

    if (p_len == 0 && st.st_size != target_size) return;
    if (p_len > 0 && (st.st_size < p_len || target_size < p_len)) return;

    int fd = open(path, O_RDONLY);
    int fd_target = open(target_path, O_RDONLY);
    if (fd == -1 || fd_target == -1) {
        if (fd != -1) close(fd);
        if (fd_target != -1) close(fd_target);
        return;
    }

    size_t bytes_to_check = (p_len > 0) ? (size_t)p_len : (size_t)target_size;
    char buf1[4096];
    char buf2[4096];
    size_t total_read = 0;
    int match = 1;

    while (total_read < bytes_to_check) {
        size_t to_read = sizeof(buf1);

        if (bytes_to_check - total_read < to_read) // serve per evitare di leggere oltre la fine del file all'ultima iterazione
        {
            to_read = bytes_to_check - total_read;
        }

        ssize_t r1 = read(fd, buf1, to_read);
        ssize_t r2 = read(fd_target, buf2, to_read);

        if (r1 <= 0 || r2 <= 0 || r1 != r2 || memcmp(buf1, buf2, r1) != 0) {
            match = 0;
            break;
        }
        total_read += r1;
    }

    if (match && total_read == bytes_to_check) {
        printf("%s\n", path);
    }

    close(fd);
    close(fd_target);
}



void search_dir(const char *dir_path, int mode, int p_len, const char *target_real, ino_t target_ino, dev_t target_dev, const char *target_path, off_t target_size) {
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
            search_dir(path, mode, p_len, target_real, target_ino, target_dev, target_path, target_size);
        } 
        else if (mode == 'l') {
            if (!S_ISLNK(st.st_mode) && st.st_ino == target_ino && st.st_dev == target_dev) {
                printf("%s\n", path);
            }
        } 
        else if (mode == 's') {
            if (S_ISLNK(st.st_mode)) {
                char link_real[PATH_MAX];
                if (realpath(path, link_real) != NULL && strcmp(link_real, target_real) == 0) {
                    printf("%s\n", path);
                }
            }
        } 
        else if (S_ISREG(st.st_mode) && mode != 's' && mode != 'l') {
            compare_content(path, target_path, p_len, target_size, target_ino);
        }
    }
    closedir(dir);
}

int main(int argc, char *argv[]) {
    int mode = 0, p_len = 0, idx = 1;

    if (argc == 5 && strcmp(argv[1], "-p") == 0) {
        mode = 'p';
        p_len = atoi(argv[2]);
        idx = 3;
    }
    else if (argc == 4 && (strcmp(argv[1], "-s") == 0 || strcmp(argv[1], "-l") == 0)) {
        mode = argv[1][1];
        idx = 2;
    }
    else if (argc == 3) {
        mode = 0;
        idx = 1;
    }
    else {
        return 1;
    }

    const char *f_path = argv[idx];
    const char *d_path = argv[idx + 1];

    struct stat target_st;
    char target_real[PATH_MAX] = {0};
    
    if (stat(f_path, &target_st) == -1) return 1;
    realpath(f_path, target_real);

    search_dir(d_path, mode, p_len, target_real, target_st.st_ino, target_st.st_dev, f_path, target_st.st_size);
    return 0;
}