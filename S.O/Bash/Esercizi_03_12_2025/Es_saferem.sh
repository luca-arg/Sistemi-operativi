#!/bin/bash

#Descrizione
#• Scrivere uno script che abbia le funzionalità di rm, ma che invece di cancellare
#definitivamente i file li sposti in una directory .trash nella vostra home
#• Usage:
#• saferm –L elenca il contenuto del cestino
#• saferm –P svuota (“purge”) il cestino
#• saferm –R files ripristina il file file
#• saferm files rimuove i file spostandoli nel cestino
#• Nota: le varie opzioni sono esclusive; ovvero, non si può lanciare un comando
#saferm –L –P ; generate un errore e stampate l’usage dello script nel caso


#Esercizio 1: saferm
# Gestione di file con lo stesso nome:
#• se un nome di file da inserire nel cestino esiste già, rinominare il file esistente
#concatenando la sua data
#• suggerimento: utilizzate date –r +%s
#• Esempio:
#• Se nel cestino c’è un file prova.sh, e volete aggiungere un altro file prova.sh,
#rinominate il primo come “prova.sh.1030606290” e poi spostate il secondo nel
#cestino
# Estensioni
#• tenete conto della possibilità di ripristinare file precedenti



# Definisco la cartella trash nella Home (creandola se non esiste)
TRASH_DIR="./trash" #ci andrebbe anche $HOME/.trash/ ma non è necessario, io voglio che sia nella cartella corrente per comodità

#if [ ! -d "$TRASH_DIR" ]; then
#    mkdir "$TRASH_DIR"
#fi
RIPRISTINATE="./ripristinati"
# Funzione per stampare l'uso corretto dello script (come richiesto in caso di errore)

stampa_usage() {
    echo "Usage: $0 [-L | -P | -R file | file ...]"
    exit 1
}

# Se non viene passato nessun parametro, mostro l'usage ed esco
if [ $# -eq 0 ]; then
    stampa_usage
fi

# Analizzo il PRIMO parametro passato
case "$1" in
    -L)
        # Controllo esclusività: se ci sono altri argomenti (es: -L -P), do errore
        if [ $# -ne 1 ]; then stampa_usage; fi
        ls -l "$TRASH_DIR"
        ;;
        
    -P)
        if [ $# -ne 1 ]; then stampa_usage; fi
        # Svuoto il cestino
        rm -rf "$TRASH_DIR"/* # ATTENZIONE: questo comando è pericoloso, assicuratevi di aver definito correttamente $TRASH_DIR
        echo "Cestino svuotato."
        ;;
        
    -R)
        # Il ripristino richiede esattamente 2 parametri (es: saferm -R file.txt)
        if [ $# -ne 2 ]; then stampa_usage; fi
        FILE_RIPRISTINO="$2"
        
        # Controllo se il file esiste nel cestino prima di spostarlo
        if [ -f "$TRASH_DIR/$FILE_RIPRISTINO" ]; then #controllo se il file da ripristinare esiste nel cestino con -f (per file regolari) e "$TRASH_DIR/$FILE_RIPRISTINO" per specificare il percorso completo
            mv "$TRASH_DIR/$FILE_RIPRISTINO" "$RIPRISTINATE/"
            echo "File $FILE_RIPRISTINO ripristinato nella cartella ripristinati."
        else
            echo "Errore: $FILE_RIPRISTINO non trovato nel cestino."
        fi
        ;;
        
    -*)
        # Catturo qualsiasi altra opzione con il trattino non valida
        stampa_usage
        ;;
        
    *)
        # CASO BASE: Spostamento dei file nel cestino.
        # Uso "$@" per ciclare su tutti i file passati (es: saferm file1 file2 file3)
        for FILE in "$@"; do
            if [ ! -e "$FILE" ]; then #controllo se il file da spostare esiste con -e (per qualsiasi tipo di file) e "$FILE" per specificare il percorso completo
                echo "Il file $FILE non esiste, lo salto."
                continue
            fi
            
            # Ricavo solo il nome del file senza il percorso
            NOME_FILE=$(basename "$FILE")
            
            # GESTIONE OMONIMIE (Esercizio pagina 84)
            if [ -e "$TRASH_DIR/$NOME_FILE" ]; then
                # Recupero la data del file GIA' PRESENTE nel cestino
                TIMESTAMP=$(date -r "$TRASH_DIR/$NOME_FILE" +%s) # date -r per ottenere la data di modifica del file, +%s per ottenere il timestamp in secondi      
                # Lo rinomino
                mv "$TRASH_DIR/$NOME_FILE" "$TRASH_DIR/${NOME_FILE}.${TIMESTAMP}"
            fi
            
            # Sposto il file nel cestino
            mv "$FILE" "$TRASH_DIR/"
            echo "File $FILE spostato nel cestino."
        done
        ;;
esac

exit 0