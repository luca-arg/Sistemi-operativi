#define _POSIX_C_SOURCE 200809L
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>

void setup_test_env() {
    int fd;
    
    fd = open("file_ref.txt", O_CREAT | O_WRONLY, 0644);
    if (fd != -1) close(fd);
    
    fd = open("clone_temporale.txt", O_CREAT | O_WRONLY, 0644);
    if (fd != -1) close(fd);
    
    struct stat st;
    if (stat("file_ref.txt", &st) == 0) {
        struct timespec ts[2];
        ts[0] = st.st_atim;
        ts[1] = st.st_mtim;
        utimensat(AT_FDCWD, "clone_temporale.txt", ts, 0);
    }
    
    link("file_ref.txt", "hard_link.txt");
    
    symlink("file_ref.txt", "sym_link.txt");
    
    if (stat("file_ref.txt", &st) == 0) {
        struct timespec ts[2];
        ts[0] = st.st_atim;
        ts[1] = st.st_mtim;
        utimensat(AT_FDCWD, "sym_link.txt", ts, AT_SYMLINK_NOFOLLOW);
    }
}

int main() {
    setup_test_env();
    return 0;
}