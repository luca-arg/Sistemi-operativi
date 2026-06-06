# Esercizio 2 - Ricerca Link Simbolici

Questo programma esplora un sottoalbero di directory e stampa i percorsi di tutti i link simbolici che puntano a un file target specificato.

## Compilazione

Per compilare il sorgente C, esegui questo comando nel terminale:

```bash
gcc num_link.c -o num_link
```

## creazione ambiente 

```
# Crea la struttura delle directory
mkdir -p test_es2/cartella_a
mkdir -p test_es2/cartella_b

# 1. Crea il file target principale
echo "Contenuto del file target" > test_es2/target.txt

# 2. Crea un file "esca" (regolare, non è un link)
echo "Sono un file a caso" > test_es2/cartella_a/file_normale.txt

# 3. Crea un LINK SIMBOLICO VALIDO (con percorso relativo)
ln -s ../target.txt test_es2/cartella_a/link_corretto_relativo

# 4. Crea un LINK SIMBOLICO VALIDO (con percorso assoluto)
ln -s "$(pwd)/test_es2/target.txt" test_es2/cartella_b/link_corretto_assoluto

# 5. Crea un HARD LINK al target (deve essere ignorato!)
ln test_es2/target.txt test_es2/hardlink_ingannevole

# 6. Crea un LINK SIMBOLICO SBAGLIATO (punta a un altro file)
ln -s ../cartella_a/file_normale.txt test_es2/cartella_b/link_sbagliato
```


## esecuzione
```
./num_link test_es2/target.txt test_es2
```