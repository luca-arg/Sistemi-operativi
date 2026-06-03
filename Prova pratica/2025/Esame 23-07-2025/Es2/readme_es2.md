# README - Esercizio 2 (sha1diff)

Questo programma confronta i file presenti in una directory sorgente con le loro "firme" SHA-1 salvate nell'albero speculare di destinazione (generato tramite `sha1dir`). Stampa a video l'elenco dei file sorgente il cui contenuto è stato alterato.

## Compilazione

Compila l'eseguibile utilizzando `gcc` attivando i warning per sicurezza:

```bash
gcc -Wall -Wextra -o sha1diff sha1diff.c
```

## Simulazione e Testing
Per testare correttamente il programma, dobbiamo avere una directory già processata dal programma dell'Esercizio 1, per poi modificare volutamente un file e innescare la rilevazione di sha1diff.

1. Modifica di un file esistente
Aggiungi del testo a uno dei file creati durante il test dell'Esercizio 1, cambiandone così l'hash.

```
echo "Testo aggiunto per alterare il file" >> cartella_sorgente/file1.txt
```

## Esecuzione del controllo
Lancia il programma sha1diff passandogli l'albero originale e l'albero clonato contenente i vecchi hash.

```
./sha1diff cartella_sorgente cartella_destinazione
```