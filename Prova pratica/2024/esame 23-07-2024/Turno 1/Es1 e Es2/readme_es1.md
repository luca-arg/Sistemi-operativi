# Esercizio 1 - Spostamento Atomico e Symlink

Questo programma sposta tutti i file regolari della directory corrente in una sottocartella chiamata `...`, rimpiazzando gli originali con link simbolici relativi in modo garantito e atomico.

## 1. Compilazione

```bash
gcc es1_atomic_move.c -o es1_atomic_move

```

## 2. Creazione dell'ambiente di test
Creiamo una directory isolata con alcuni file regolari, una directory (che deve essere ignorata) e un link simbolico (che deve essere ignorato).

```
mkdir test_atomico
cd test_atomico

# Copia l'eseguibile nella cartella di test per poterlo lanciare
cp ../es1_atomic_move .

# Crea file di test
echo "Dati del file 1" > file1.txt
echo "Dati del file 2" > file2.txt

# Crea una cartella e un link per testare che vengano ignorati
mkdir cartella_ignorata
ln -s file1.txt link_ignorato.txt
```

##3. Esecuzione
Avvia semplicemente il programma (non richiede parametri):

```
./es1_atomic_move
```
4. Verifica dell'Output
Controlliamo cosa è successo nella directory:

```
ls -la
```
Output atteso:

file1.txt e file2.txt (e l'eseguibile stesso es1_atomic_move) ora appariranno azzurri o ciano (se il tuo terminale supporta i colori) e avranno una freccia -> .../file1.txt, a dimostrazione che sono diventati link simbolici relativi.

La directory ... sarà stata creata.

Verifica che i file originali siano al sicuro dentro ...:

```
ls -la ...
cat file1.txt
```

_______

# Esercizio 2 - Undo dello Spostamento Atomico

Questo programma inverte gli effetti dell'Esercizio 1, ripristinando i file originali al posto dei link simbolici in modo atomico.

## 1. Compilazione

```bash
gcc es2_undo_atomic.c -o es2_undo_atomic
```

```
./es2_undo_atomic
```

Verifica dell'Output
Controlla il contenuto della cartella:

```
ls -la
```