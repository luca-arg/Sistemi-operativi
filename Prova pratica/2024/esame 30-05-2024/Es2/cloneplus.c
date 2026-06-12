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

    char proc_path[PATH_MAX];
    char exe_path[PATH_MAX];
    char cwd_path[PATH_MAX];

    snprintf(proc_path, sizeof(proc_path), "/proc/%s/exe", argv[1]);
    ssize_t len = readlink(proc_path, exe_path, sizeof(exe_path) - 1);
    if (len == -1) return 1;
    exe_path[len] = '\0';


    snprintf(proc_path, sizeof(proc_path), "/proc/%s/cwd", argv[1]);
    len = readlink(proc_path, cwd_path, sizeof(cwd_path) - 1);
    if (len == -1) return 1;
    cwd_path[len] = '\0';

    
    if (chdir(cwd_path) == -1) return 1;


    snprintf(proc_path, sizeof(proc_path), "/proc/%s/cmdline", argv[1]);
    int fd_cmd = open(proc_path, O_RDONLY);

    if (fd_cmd == -1) return 1;


    size_t cmd_buf_size = 64 * 1024;
    char *cmd_buf = malloc(cmd_buf_size);

    ssize_t cmd_read = read(fd_cmd, cmd_buf, cmd_buf_size - 1);
    close(fd_cmd);

    if (cmd_read <= 0) { free(cmd_buf); return 1; }
    cmd_buf[cmd_read] = '\0';

    char *cmd_argv[1024];
    int argc_cloned = 0;
    char *p = cmd_buf;


    while (p < cmd_buf + cmd_read && argc_cloned < 1023) {
        cmd_argv[argc_cloned++] = p;
        p += strlen(p) + 1;
    }
    cmd_argv[argc_cloned] = NULL;

    snprintf(proc_path, sizeof(proc_path), "/proc/%s/environ", argv[1]);
    int fd_env = open(proc_path, O_RDONLY);

    if (fd_env == -1) { free(cmd_buf); return 1; }
    
    size_t env_buf_size = 256 * 1024;
    char *env_buf = malloc(env_buf_size);
    ssize_t env_read = read(fd_env, env_buf, env_buf_size - 1);
    close(fd_env);
    
    char *env_argv[4096];
    int envc = 0;
    if (env_read > 0) {
        env_buf[env_read] = '\0';
        char *e = env_buf;
        while (e < env_buf + env_read && envc < 4095) {
            env_argv[envc++] = e;
            e += strlen(e) + 1;
        }
    }
    env_argv[envc] = NULL;

    execve(exe_path, cmd_argv, env_argv);

    free(cmd_buf);
    free(env_buf);
    return 1;
}