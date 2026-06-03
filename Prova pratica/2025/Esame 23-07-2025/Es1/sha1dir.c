#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

void calculate_hash(const char *filepath, char *out_hash) {
    int fd[2];
    if (pipe(fd) == -1) exit(1);

    if (fork() == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        
        execlp("sha1sum", "sha1sum", filepath, NULL);
        exit(1);
    }

    close(fd[1]);
    int bytes_read = read(fd[0], out_hash, 40);
    close(fd[0]);
    wait(NULL);
    
    if (bytes_read == 40) {
        out_hash[40] = '\0';
    } else {
        out_hash[0] = '\0';
    }
}



void process_dir(const char *src, const char *dest) {
    DIR *dir = opendir(src);
    if (!dir) return;

    struct dirent *entry;
    struct stat st;
    char src_path[PATH_MAX];
    char dest_path[PATH_MAX];
    char hash[41];

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }

        snprintf(src_path, sizeof(src_path), "%s/%s", src, entry->d_name);
        snprintf(dest_path, sizeof(dest_path), "%s/%s", dest, entry->d_name);

        if (lstat(src_path, &st) == 0) {
            if (S_ISDIR(st.st_mode)) {
                mkdir(dest_path, 0700);
                process_dir(src_path, dest_path);
            } 
            else if (S_ISREG(st.st_mode)) {
                calculate_hash(src_path, hash);

                if (hash[0] != '\0') {
                    int fd = open(dest_path, O_CREAT | O_WRONLY | O_TRUNC, 0600);
                    if (fd != -1) {
                        write(fd, hash, 40);
                        close(fd);
                    }
                }
            }
        }
    }
    closedir(dir);
}


int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "Uso: %s <sorgente> <destinazione>\n", argv[0]);
        return 1;
    }

    struct stat st;
    if (stat(argv[2], &st) == 0) {
        fprintf(stderr, "Errore: la directory di destinazione '%s' esiste gia'.\n", argv[2]);
        return 1; 
    }

    if (mkdir(argv[2], 0700) != 0) {
        perror("Errore nella creazione della directory");
        return 1;
    }

    process_dir(argv[1], argv[2]);

    return 0;
}