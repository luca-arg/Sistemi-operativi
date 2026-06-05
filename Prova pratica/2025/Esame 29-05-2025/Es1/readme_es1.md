# Esercizio 1: Ricerca File Path Ricorsivi (search_prec)

Questo programma in C esplora la directory corrente alla ricerca di file "path ricorsivi". Un file è considerato "path ricorsivo" se il suo contenuto in byte corrisponde esattamente al suo pathname assoluto.

## Funzionamento
* Il programma recupera il percorso assoluto della directory corrente tramite `getcwd`.
* Utilizza `opendir` e `readdir` per ciclare su tutte le entry della directory, saltando `.` e `..`.
* Ottimizzazione: Tramite la system call `stat`, verifica innanzitutto che la voce sia un file regolare e che la sua dimensione in byte (`st_size`) sia rigorosamente uguale alla lunghezza in caratteri del suo pathname assoluto.
* Se le dimensioni coincidono, legge il contenuto del file in blocco con `fread` e usa `memcmp` per il confronto finale.

## Comandi di Test

1. **Compilazione:**
   ```bash
   gcc -Wall -Wextra -o search_prec search_prec.c
   ```

   Setup dell'ambiente di test:
Crea un file esca (che verrà ignorato) e un file path ricorsivo valido (usando echo -n per omettere l'invisibile terminatore di riga \n):

```
echo "Contenuto casuale" > esca.txt
echo -n "$(pwd)/target_valido.txt" > target_valido.txt
```