#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>
#include <string.h>

#define PATH_MAX 4096

int main(int argc, char *argv[]) {
    if (argc != 2) {
        return 1;
    }

    char exe_path_proc[PATH_MAX];
    char exe_path[PATH_MAX];

    snprintf(exe_path_proc, sizeof(exe_path_proc), "/proc/%s/exe", argv[1]);// Costruisce il percorso per leggere il link simbolico dell'eseguibile del processo

    ssize_t len = readlink(exe_path_proc, exe_path, sizeof(exe_path) - 1);// Legge il percorso dell'eseguibile del processo specificato
    if (len == -1) {
        return 1;
    }
    exe_path[len] = '\0';

    char cmdline_path[PATH_MAX];
    snprintf(cmdline_path, sizeof(cmdline_path), "/proc/%s/cmdline", argv[1]);

    int fd = open(cmdline_path, O_RDONLY);
    if (fd == -1) {
        return 1;
    }

    size_t buf_size = 64 * 1024;
    char *cmd_buf = malloc(buf_size);//array di caratteri per memorizzare il contenuto del file cmdline
    if (!cmd_buf) {
        close(fd);
        return 1;
    }

    ssize_t bytes_read = read(fd, cmd_buf, buf_size - 1);
    close(fd);

    if (bytes_read <= 0) {
        free(cmd_buf);
        return 1;
    }
    cmd_buf[bytes_read] = '\0';

    char *cmd_argv[1024];// Array per memorizzare i puntatori agli argomenti del comando
    int argc_cloned = 0;
    char *p = cmd_buf;

    while (p < cmd_buf + bytes_read && argc_cloned < 1023) {
        cmd_argv[argc_cloned++] = p;
        p += strlen(p) + 1;
    }
    cmd_argv[argc_cloned] = NULL;

    execv(exe_path, cmd_argv);

    free(cmd_buf);
    return 1;
}