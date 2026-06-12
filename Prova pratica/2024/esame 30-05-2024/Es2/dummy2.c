#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    printf("--- PROCESSO ATTIVO (dummy2) ---\n");
    printf("PID: %d\n", getpid());
    
    char cwd[1024];
    if (getcwd(cwd, sizeof(cwd)) != NULL) {
        printf("Directory Corrente (CWD): %s\n", cwd);
    }

    printf("Argomenti:\n");
    for (int i = 0; i < argc; i++) {
        printf("  [%d]: %s\n", i, argv[i]);
    }
    
    char *test_var = getenv("ESAME_OS_VAR");
    printf("Variabile ESAME_OS_VAR: %s\n", test_var ? test_var : "NON DEFINITA");

    printf("\nIn attesa per 60 secondi...\n");
    sleep(60);
    
    return 0;
}