#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>

void recursive_dir(const char *dir_name, time_t ref_time) {
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

        snprintf(path, sizeof(path), "%s/%s", dir_name, dir->d_name);// non stampa il nome del file, ma costruisce un percorso completo per poterlo utilizzare successivamente. snprintf è usato per evitare buffer overflow, assicurandosi che il percorso non superi la dimensione del buffer.
        
        struct stat st;
        if (lstat(path, &st) == -1) {
            perror(path);
            continue;
        }

        if (S_ISDIR(st.st_mode)) {
            recursive_dir(path, ref_time);
        } 
        else if (S_ISREG(st.st_mode)) {
            if (st.st_mtime > ref_time) {
                printf("%s\n", path);
            }
        }
    }
    closedir(d);
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

    //1) utente può specificare una directory o un file come secondo argomento. Se non specifica nulla, si assume che voglia esaminare la directory corrente.
    if (argc == 2) {
        recursive_dir(".", ref_time);
    } 

    /*2) Se l'utente specifica un secondo argomento, controlliamo se è una directory o un file. 
     - Se è una directory, chiamiamo la funzione ricorsiva per esplorarla. 
     - Se è un file, confrontiamo il suo tempo di modifica(st_target) con quello del file di riferimento e stampiamo il nome del file se è più recente.*/
    else if (argc == 3) {
        struct stat st_target;
        if (lstat(argv[2], &st_target) == -1) {
            return 1;
        }

        if (S_ISDIR(st_target.st_mode)) {
            recursive_dir(argv[2], ref_time);
        } 
        else if (S_ISREG(st_target.st_mode)) {
            if (st_target.st_mtime > ref_time) {
                printf("%s\n", argv[2]);
            }
        }
    }

    return 0;
}