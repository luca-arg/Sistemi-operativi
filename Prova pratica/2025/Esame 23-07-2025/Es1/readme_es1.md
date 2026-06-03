# README - Esercizio 1 (sha1dir)

Il programma `sha1dir` prende in input due parametri: una directory sorgente esistente e il nome di una directory di destinazione non ancora esistente. Il programma ricrea l'albero delle directory della sorgente all'interno della destinazione. Tutti i file regolari clonati conterranno al loro interno la firma SHA-1 del file originale corrispondente.

## Compilazione

Per compilare il sorgente C, utilizza il compilatore `gcc`:

```bash
gcc sha1dir.c -o sha1dir

```

## test
```bash
# Crea la directory principale
mkdir cartella_sorgente

# Crea un file al livello radice
echo "Sistemi Operativi" > cartella_sorgente/file1.txt

# Crea una sottocartella e inserisci un altro file
mkdir cartella_sorgente/sottocartella
echo "Test di ricorsione" > cartella_sorgente/sottocartella/file2.txt
```

## Esecuzione
```bash
./sha1dir cartella_sorgente cartella_destinazione
```

## verifica dei risultati

Controlliamo che la struttura ad albero sia stata rispettata e che il contenuto dei nuovi file sia stato sostituito correttamente.

1. Verifica della struttura
Puoi usare il comando ls -R per vedere l'intero albero creato:
```bash

ls -R cartella_destinazione
```
Dovrai vedere una struttura speculare a quella di partenza, con il file file1.txt e la directory sottocartella contenente file2.txt.

2. Verifica del contenuto
Ispeziona il contenuto di uno dei file generati usando il comando cat:

```bash
cat cartella_destinazione/file1.txt

```