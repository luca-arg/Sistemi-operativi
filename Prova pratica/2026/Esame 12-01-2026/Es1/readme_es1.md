# Esercizio 1 - Confronto temporale di modifica file (modifcmp)

Questo progetto contiene la soluzione all'Esercizio 1 della prova pratica.Il programma C `modifcmp` confronta il tempo di ultima modifica tra file e può operare in tre modalità distinte a seconda degli argomenti forniti da terminale.

## Compilazione
Per compilare il sorgente, utilizzare il compilatore `gcc`:
```bash
gcc modifcmp.c -o modifcmp
```

## Guida al test
```bash
# 1. Creiamo il file di riferimento più "vecchio"
echo "File di riferimento" > file_vecchio.txt

# Attendiamo 2 secondi
sleep 2

# 2. Creiamo un file più recente nella directory corrente
echo "File più recente" > file_recente.txt

# 3. Creiamo una directory con all'interno un altro file recente
mkdir -p dir_test
echo "File recente in sotto-cartella" > dir_test/file_interno.txt
```

## Test effettivo (mod 1)
```bash
./modifcmp file_vecchio.txt


Output atteso:

./file_recente.txt
./dir_test/file_interno.txt
```

## Test effettivo (mod 2)
```bash
./modifcmp file_vecchio.txt file_recente.txt


Output atteso:

file_recente.txt

(Se invece si esegue ./modifcmp file_recente.txt file_vecchio.txt, il programma terminerà silenziosamente senza stampare nulla).
```


## Test effettivo (mod 3)
```bash
./modifcmp file_vecchio.txt dir_test


Output atteso:

dir_test/file_interno.txt
```

