# Esercizio 3 - Ricerca testuale e ordinamento cronologico (Python)

Questo script ricerca un determinato pattern testuale all'interno di tutti i file presenti nella directory corrente e nel suo intero sottoalbero. I file che contengono la stringa cercata vengono stampati a terminale in ordine cronologico, dal più vecchio al più recente (basandosi sul tempo di ultima modifica).

## Architettura e Moduli Utilizzati
Lo script si appoggia alle librerie standard di Python illustrate a lezione:
* `sys`: per la gestione degli argomenti da riga di comando (`sys.argv`) e la gestione delle uscite di emergenza (`sys.exit`).
* `pathlib`: per l'attraversamento ricorsivo object-oriented dell'albero delle directory (`iterdir()`, `is_file()`, `is_dir()`).
* `os`: per l'estrazione dei metadati del file system tramite `os.stat()`.

La ricerca gestisce le eccezioni `OSError` per ignorare file protetti o non leggibili senza far crashare il programma, decodificando in formato ASCII (ignorando caratteri invalidi) per garantire una scansione sicura anche in presenza di binari compilati mescolati ai sorgenti.

## Guida al Test (Esercizio 3)

### Passo 1: Creazione dell'ambiente di test
Prima di lanciare lo script, creiamo un po' di file di test con tempi di modifica differenti. Apri il terminale nella directory di lavoro e digita:

```bash
# Creiamo due directory
mkdir -p dir_A dir_B

# Creiamo tre file con la parola "segreto"
echo "Questo file ha la parola segreto." > dir_A/file1.txt
sleep 2 # Aspettiamo 2 secondi per falsare il tempo di modifica
echo "Anche qui c'è il segreto, ma è più recente." > dir_B/file2.txt
sleep 2
echo "Ultimo segreto creato." > file3.txt

# Creiamo un file senza il pattern
echo "Questo file non c'entra nulla." > dir_A/file_vuoto.txt
```

## Passo 2: test
```bash
python3 es3.py segreto
```