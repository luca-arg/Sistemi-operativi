# Esercizio 1 - ckfile

Questo programma in C cerca all'interno di una directory (e in tutto il suo sottoalbero) i link simbolici o i link fisici che puntano a un file target specificato.

## Compilazione

Per compilare il programma, apri il terminale nella directory contenente `ckfile.c` ed esegui:

```bash
gcc ckfile.c -o ckfile
```

## Creazione dell'ambiente di test
Prima di eseguire il programma, puoi creare un ambiente di test eseguendo questi comandi nel terminale. Questo creerà una directory base, un file target, un hard link e un symbolic link sparsi in varie sottocartelle:

```
# Crea la struttura delle directory
mkdir -p test_env/subdir1
mkdir -p test_env/subdir2

# Crea il file target originale
echo "Contenuto del file originale" > test_env/target.txt

# Crea un hard link al file target in subdir1
ln test_env/target.txt test_env/subdir1/hardlink_al_target

# Crea un symbolic link al file target in subdir2 (usando un path relativo)
ln -s ../target.txt test_env/subdir2/symlink_al_target


# Crea un symbolic link con PATH ASSOLUTO in subdir1
# Usiamo $(pwd) per concatenare il percorso assoluto della cartella di lavoro attuale
ln -s "$(pwd)/test_env/target.txt" test_env/subdir1/symlink_assoluto

# Crea un file casuale che non c'entra nulla
echo "Altro file" > test_env/subdir1/altro_file.txt
```

## 1 . Ricerca dei Symbolic Link (Opzione -s)
Per trovare tutti i link simbolici che puntano a target.txt partendo dalla cartella test_env:
```
./ckfile -s test_env/target.txt test_env
```


## 2. Ricerca degli Hard Link (Opzione -l)
Per trovare tutti i link fisici del file target.txt partendo dalla cartella test_env:
```
./ckfile -l test_env/target.txt test_env
```