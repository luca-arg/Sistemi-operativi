#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }

    int nprocessi = atoi(argv[1]);
    if (nprocessi <= 0) {
        return 1;
    }

    struct stat st;
    if (stat(argv[2], &st) == -1) {
        return 1;
    }

    if (!S_ISREG(st.st_mode)) {
        return 1;
    }

    off_t half_size = st.st_size / 2;
    off_t base_chunk = half_size / nprocessi;

    for (int i = 0; i < nprocessi; i++) {
        pid_t pid = fork();
        
        if (pid == -1) {
            return 1;
        }

        if (pid == 0) {
            int fd = open(argv[2], O_RDWR);
            if (fd == -1) {
                exit(1);
            }

            off_t left_start = i * base_chunk;//punto di partenza del processo i-esimo
            off_t left_end = (i == nprocessi - 1) ? half_size : (i + 1) * base_chunk;//punto di fine del processo i-esimo
            
            off_t left = left_start;//testina del processo i-esimo
            off_t right = st.st_size - left_start;//testina del processo i-esimo che parte da destra
            
            size_t chunk = 1024;
            char buf_left[1024];
            char buf_right[1024];

            while (left < left_end) {
                off_t remaining = left_end - left;
                size_t current_chunk = (remaining >= (off_t)chunk) ? chunk : (size_t)remaining;

                if (lseek(fd, left, SEEK_SET) == -1) { close(fd); exit(1); }
                if (read(fd, buf_left, current_chunk) != (ssize_t)current_chunk) { close(fd); exit(1); }

                if (lseek(fd, right - current_chunk, SEEK_SET) == -1) { close(fd); exit(1); }
                if (read(fd, buf_right, current_chunk) != (ssize_t)current_chunk) { close(fd); exit(1); }

                for (size_t j = 0; j < current_chunk; j++) {
                    char temp = buf_left[j];
                    buf_left[j] = buf_right[current_chunk - 1 - j];
                    buf_right[current_chunk - 1 - j] = temp;
                }

                if (lseek(fd, left, SEEK_SET) == -1) { close(fd); exit(1); }
                if (write(fd, buf_left, current_chunk) != (ssize_t)current_chunk) { close(fd); exit(1); }

                if (lseek(fd, right - current_chunk, SEEK_SET) == -1) { close(fd); exit(1); }
                if (write(fd, buf_right, current_chunk) != (ssize_t)current_chunk) { close(fd); exit(1); }

                left += current_chunk;
                right -= current_chunk;
            }

            close(fd);
            exit(0);
        }
    }

    for (int i = 0; i < nprocessi; i++) {
        wait(NULL);
    }

    return 0;
}