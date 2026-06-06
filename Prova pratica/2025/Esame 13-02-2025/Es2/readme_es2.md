# Esercizio 2 - ckfile (Ricerca per Contenuto)

Questa versione estesa del programma `ckfile` cerca all'interno di una directory (e nel suo sottoalbero) i file che hanno lo stesso contenuto di un file target, oppure che condividono con esso un prefisso iniziale di lunghezza specificata.

## Compilazione

Per compilare il programma, usa il seguente comando nel terminale:

```bash
gcc  ckfile.c -o ckfile
```

## creazione ambiente

```
# Crea la cartella di test
mkdir -p test_env_es2/sotto_cartella

# 1. Crea il file target con una frase specifica
echo "Sistemi Operativi: la gestione della memoria e dei processi è fondamentale." > test_env_es2/target.txt

# 2. Crea un file con il CONTENUTO IDENTICO
echo "Sistemi Operativi: la gestione della memoria e dei processi è fondamentale." > test_env_es2/sotto_cartella/file_identico.txt

# 3. Crea un file con un PREFISSO IN COMUNE (primi 30 caratteri uguali)
# "Sistemi Operativi: la gestione" = 30 byte/caratteri
echo "Sistemi Operativi: la gestione del file system è un altro argomento chiave." > test_env_es2/file_prefisso.txt

# 4. Crea un HARD LINK al target (deve essere ignorato dalla ricerca)
ln test_env_es2/target.txt test_env_es2/sotto_cartella/hardlink_ignorato

# 5. Crea un file completamente diverso
echo "File di testo casuale per fare volume." > test_env_es2/sotto_cartella/file_diverso.txt
```

## Esecuzione e Testing
```
./ckfile test_env_es2/target.txt test_env_es2

./ckfile -p 30 test_env_es2/target.txt test_env_es2

```