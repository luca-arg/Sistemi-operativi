#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <dirent.h>
#include <string.h>
#include <limits.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif


// Modo 1
int main() {
    DIR *dir = opendir(".");
    if (!dir) return 1;

    struct dirent *entry;
    struct stat st;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0 ||
            strcmp(entry->d_name, "...") == 0) {
            continue;
        }

        if (lstat(entry->d_name, &st) == -1) continue;

        if (S_ISLNK(st.st_mode)) {
            char target[PATH_MAX];
            ssize_t len = readlink(entry->d_name, target, sizeof(target) - 1);
            
            if (len != -1) {
                target[len] = '\0';
                
                char expected_target[PATH_MAX];
                snprintf(expected_target, sizeof(expected_target), ".../%s", entry->d_name);

                if (strcmp(target, expected_target) == 0) {
                    char tmp_name[PATH_MAX];
                    snprintf(tmp_name, sizeof(tmp_name), "%s.tmp", entry->d_name);

                    if (link(target, tmp_name) == 0) {
                        if (rename(tmp_name, entry->d_name) == 0) {
                            unlink(target);
                        } 
                        else {
                            unlink(tmp_name);
                        }
                    }
                }
            }
        }
    }
    closedir(dir);
    
    rmdir("...");
    
    return 0;
}




//modo 2
int main() {
    DIR *dir = opendir(".");
    if (!dir) return 1;

    struct dirent *entry;
    struct stat st;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0 ||
            strcmp(entry->d_name, "...") == 0) {
            continue;
        }

        if (lstat(entry->d_name, &st) == -1) continue;

        if (S_ISLNK(st.st_mode)) {
            char target_path[PATH_MAX];
            ssize_t len = readlink(entry->d_name, target_path, sizeof(target_path) - 1);
            
            if (len == -1) {
                perror("readlink");
                continue;
            }
            target_path[len] = '\0';
            
            char expected_target[PATH_MAX];
            snprintf(expected_target, sizeof(expected_target), ".../%s", entry->d_name);

            if (strcmp(target_path, expected_target) == 0) {
                char tmp_file_path[PATH_MAX];
                snprintf(tmp_file_path, sizeof(tmp_file_path), "%s.tmp", entry->d_name);

                if (link(target_path, tmp_file_path) == -1) {
                    perror("link");
                    continue;
                }

                if (rename(tmp_file_path, entry->d_name) == -1) {
                    perror("rename");
                    unlink(tmp_file_path);
                    continue;
                }

                if (unlink(target_path) == -1) {
                    perror("unlink");
                }
            }
        }
    }
    
    closedir(dir);
    rmdir("...");
    
    return 0;
}






//modo 3
int main() {
    DIR *dir = opendir(".");
    if (!dir) return 1;

    struct dirent *entry;
    struct stat st;

    while ((entry = readdir(dir)) != NULL) {
        if (strcmp(entry->d_name, ".") == 0 ||
            strcmp(entry->d_name, "..") == 0 ||
            strcmp(entry->d_name, "...") == 0) {
            continue;
        }

        if (lstat(entry->d_name, &st) == -1) continue;

        if (S_ISLNK(st.st_mode)) {
            char target_path[PATH_MAX];
            ssize_t len = readlink(entry->d_name, target_path, sizeof(target_path) - 1);
            
            if (len == -1) {
                perror("readlink");
                continue;
            }
            target_path[len] = '\0';
            
            char expected_target[PATH_MAX];
            snprintf(expected_target, sizeof(expected_target), ".../%s", entry->d_name);

            if (strcmp(target_path, expected_target) == 0) {

                if (rename(target_path, entry->d_name) == -1) {
                    perror("rename");
                    continue;
                }

            }
        }
    }
    
    closedir(dir);
    rmdir("...");
    
    return 0;
}
