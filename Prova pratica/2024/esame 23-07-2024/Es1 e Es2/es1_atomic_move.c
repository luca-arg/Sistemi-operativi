#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif


/*Il nome file1.txt nella directory corrente non si riferisce più al file originale, ma al link simbolico.
Il contenuto originale del file si trova in .../file1.txt.
Il link simbolico file1.txt punta a .../file1.txt.*/

int main() {
    struct stat st;
    
    if (stat("...", &st) == -1) {
        if (mkdir("...", 0700) == -1) {
            return 1;
        }
    }

    DIR *dir = opendir(".");
    if (!dir) return 1;

    struct dirent *entry;
    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0 ||
            strcmp(entry->d_name, "...") == 0) 
            {
            continue;
        }

        if (lstat(entry->d_name, &st) == -1) continue;

        if (S_ISREG(st.st_mode)) {
            // Percorso del file nella sottodirectory '...'
            char target_path[PATH_MAX];
            snprintf(target_path, sizeof(target_path), ".../%s", entry->d_name);

            // Percorso per il link simbolico temporaneo
            char tmp_link_path[PATH_MAX];
            snprintf(tmp_link_path, sizeof(tmp_link_path), "%s.tmp", entry->d_name);

            // 1. Crea un hard link al file nella directory di destinazione.
            //    Ora lo stesso file ha due nomi. Il nome originale nella directory
            //    corrente non è stato toccato, garantendo che non sia mai inesistente.
    
            if (link(entry->d_name, target_path) == -1) {
                perror("link");
                continue; // Passa al prossimo file in caso di errore
            }

            // 2. Crea un link simbolico temporaneo che punta alla nuova posizione del file.
            //    Il target del link deve essere il percorso relativo alla nuova posizione.
            if (symlink(target_path, tmp_link_path) == -1) {
                perror("symlink");
                // Se la creazione del symlink fallisce, rimuovi l'hard link creato prima.
                unlink(target_path);
                continue;
            }

            // 3. Sostituisci atomicamente il file originale con il link simbolico.
            //    rename() garantisce che la sostituzione avvenga in un'unica operazione indivisibile.
            //    In nessun istante il nome 'entry->d_name' risulta inesistente.
            if (rename(tmp_link_path, entry->d_name) == -1) {
                perror("rename");
                // Se la rename fallisce, pulisci sia l'hard link che il symlink temporaneo.
                unlink(target_path);
                unlink(tmp_link_path);
                continue;
            }
        }
    }
    
    closedir(dir);
    return 0;
}