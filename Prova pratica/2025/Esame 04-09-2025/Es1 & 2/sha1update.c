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


void process_symlink(const char *target_dir, const char *index_dir, const char *hash_name) {
    char sym_link_path[PATH_MAX * 2];
    snprintf(sym_link_path, sizeof(sym_link_path), "%s/%s", index_dir, hash_name);

    struct stat link_st, target_st;

    if (lstat(sym_link_path, &link_st) != 0) return;
    if (!S_ISLNK(link_st.st_mode)) return;

    if (stat(sym_link_path, &target_st) != 0) {
        unlink(sym_link_path);
        return;
    }

    if (target_st.st_mtime > link_st.st_mtime) {
        char target_buf[PATH_MAX];
        ssize_t len = readlink(sym_link_path, target_buf, sizeof(target_buf) - 1);// readlink serve per leggere il percorso a cui punta il link simbolico, e lo memorizza in target_buf. Il valore restituito è la lunghezza del percorso letto, o -1 in caso di errore

        
        if (len != -1) {
            target_buf[len] = '\0';
            
            char original_filepath[PATH_MAX * 2];
            const char *filename = target_buf;
            
            if (strncmp(filename, "../", 3) == 0) {
                filename += 3;
            }
            
            snprintf(original_filepath, sizeof(original_filepath), "%s/%s", target_dir, filename);

            char new_hash[41];
            calculate_hash(original_filepath, new_hash);

            if (new_hash[0] != '\0') {
                unlink(sym_link_path);
                
                char new_sym_link_path[PATH_MAX * 2];
                snprintf(new_sym_link_path, sizeof(new_sym_link_path), "%s/%s", index_dir, new_hash);
                symlink(target_buf, new_sym_link_path);// crea un nuovo link simbolico con il nome dell'hash aggiornato che punta al file originale
            }
        }
    }
}



void update_directory(const char *target_dir) {
    char index_dir_path[PATH_MAX];
    snprintf(index_dir_path, sizeof(index_dir_path), "%s/.sha1index", target_dir);
    
    DIR *dir = opendir(index_dir_path);
    if (!dir) return;

    struct dirent *entry;
    
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
            continue;
        }
        process_symlink(target_dir, index_dir_path, entry->d_name);
    }
    
    closedir(dir);
}



int main(int argc, char *argv[]) {
    if (argc > 2) {
        fprintf(stderr, "Usage: %s [directory]\n", argv[0]);
        return 1;
    }
    const char *target_dir = (argc > 1) ? argv[1] : ".";
    
    update_directory(target_dir);
    
    return 0;
}