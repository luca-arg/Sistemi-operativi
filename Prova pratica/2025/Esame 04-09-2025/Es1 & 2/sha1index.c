#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <limits.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

void calculate_hash(const char *filepath, char *out_hash) {

    //FASE 1: preparare il processo figlio per eseguire sha1sum e leggere l'output tramite una pipe
    int fd[2];
    if (pipe(fd) == -1) exit(1);

    if (fork() == 0) {// Child process
        close(fd[0]);// Close read end
        dup2(fd[1], STDOUT_FILENO);// Redirect stdout to pipe
        close(fd[1]);
    
        //FASE 2: eseguire sha1sum sul file specificato e scrivere l'output nella pipe
        execlp("sha1sum", "sha1sum", filepath, NULL);
        exit(1);
    }

    //FASE 3: il processo padre chiude l'estremità di scrittura della pipe, legge l'hash generato dal processo figlio e lo memorizza in out_hash
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


void create_symlink(const char *index_dir, const char *filename, const char *hash) {
    char sym_target[PATH_MAX];
    char sym_link[PATH_MAX];
    
    snprintf(sym_target, sizeof(sym_target), "../%s", filename);// il link simbolico punta al file originale
    snprintf(sym_link, sizeof(sym_link), "%s/%s", index_dir, hash);// il nome del link simbolico è l'hash del file originale
    
    symlink(sym_target, sym_link);// crea il link simbolico con il nome dell'hash che punta al file originale
}



void process_entry(const char *target_dir, const char *index_dir, const char *filename) {
    char filepath[PATH_MAX];
    struct stat st_info;
    char hash[41];
    
    snprintf(filepath, sizeof(filepath), "%s/%s", target_dir, filename);

    if (lstat(filepath, &st_info) == 0 && S_ISREG(st_info.st_mode)) {
        calculate_hash(filepath, hash);

        if (hash[0] != '\0') {
            create_symlink(index_dir, filename, hash);
        }
    }
}



void analyze_directory(const char *target_dir) {
    DIR *dir = opendir(target_dir);
    if (!dir) exit(1);

    char index_dir_path[PATH_MAX];
    snprintf(index_dir_path, sizeof(index_dir_path), "%s/.sha1index", target_dir);
    mkdir(index_dir_path, 0700);
    
    struct dirent *entry;
    
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        process_entry(target_dir, index_dir_path, entry->d_name);
    }
    
    closedir(dir);
}



int main(int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [directory]\n", argv[0]);
        return 1;
    }
    const char *target_dir = (argc > 1) ? argv[1] : ".";
    
    analyze_directory(target_dir);
    
    return 0;
}