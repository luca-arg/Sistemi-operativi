#define _XOPEN_SOURCE 700
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    struct stat st;
    if (stat(argv[1], &st) == -1) {
        return 1;
    }

    if (!S_ISREG(st.st_mode)) {
        return 1;
    }

    int fd = open(argv[1], O_RDWR);
    if (fd == -1) {
        return 1;
    }

    off_t left = 0;
    off_t right = st.st_size;
    size_t chunk = 1024;
    
    char buf_left[1024];
    char buf_right[1024];

    while (left < right) {
        off_t remaining = right - left;
        size_t current_chunk = (remaining / 2 >= (off_t)chunk) ? chunk : (size_t)(remaining / 2);

        if (current_chunk == 0) {
            break;
        }

        if (lseek(fd, left, SEEK_SET) == -1) {
            close(fd);
            return 1;
        }
        if (read(fd, buf_left, current_chunk) != (ssize_t)current_chunk) {
            close(fd);
            return 1;
        }

        if (lseek(fd, right - current_chunk, SEEK_SET) == -1) {
            close(fd);
            return 1;
        }
        if (read(fd, buf_right, current_chunk) != (ssize_t)current_chunk) {
            close(fd);
            return 1;
        }

        for (size_t i = 0; i < current_chunk; i++) {
            char temp = buf_left[i];
            buf_left[i] = buf_right[current_chunk - 1 - i];
            buf_right[current_chunk - 1 - i] = temp;
        }

        if (lseek(fd, left, SEEK_SET) == -1) {
            close(fd);
            return 1;
        }
        if (write(fd, buf_left, current_chunk) != (ssize_t)current_chunk) {
            close(fd);
            return 1;
        }

        if (lseek(fd, right - current_chunk, SEEK_SET) == -1) {
            close(fd);
            return 1;
        }
        if (write(fd, buf_right, current_chunk) != (ssize_t)current_chunk) {
            close(fd);
            return 1;
        }

        left += current_chunk;
        right -= current_chunk;
    }

    close(fd);
    return 0;
}