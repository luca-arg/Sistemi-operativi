#!/bin/bash

# Controllo sul numero di parametri passati allo script
if [ $# -ne 1 ]; then
    echo "Usage: $(basename $0) <directory>"
    exit 65
fi

DIR="$1"

# Controllo che l'argomento sia effettivamente una directory
if [ ! -d "$DIR" ]; then
    echo "Errore fatale: '$DIR' non è una directory valida." >&2
    exit 66
fi

# Scansioniamo la directory per trovare i link simbolici (-type l)
# Per ogni link, otteniamo il suo path assoluto e risolviamo il file di destinazione reale
find "$DIR" -type l 2>/dev/null | while read -r link; do # -type l filtra solo i link simbolici all'interno di DIR e le sottocartelle; 2>/dev/null sopprime eventuali errori di permessi buttando nel cestino do sistema;| while read -r link; do: Prendiamo l'elenco dei link trovati e li passiamo riga per riga tramite una pipe (|)  a un ciclo while. Ad ogni giro, il percorso del link viene salvato nella variabile link
    target=$(realpath "$link" 2>/dev/null)
    
    # Se il target esiste, stampiamo "target|link" per processarlo successivamente
    if [ -n "$target" ] && [ -e "$target" ]; then
        echo "$target|$link"
    fi
# Passiamo l'output a awk per il raggruppamento
#done | awk -F'|' ' serve per processare l'output del ciclo while, che è nel formato "target|link". Il -F'|' dice ad awk di usare il carattere '|' come delimitatore di campo. In questo modo, $1 conterrà il target (file di destinazione) e $2 conterrà il link simbolico.
done | awk -F'|' ' 
{
    # $1 è il target, $2 è il link
    target = $1; 
    link = $2;
    
    # Incrementiamo il contatore per questo specifico target
    count[target]++;
    
    # Salviamo i link associati accodandoli in una stringa
    links[target] = links[target] "\n  -> " link;
}
END {
    trovati = 0;
    # Cicliamo su tutti i target trovati
    for (t in count) {
        # Se un file fisico ha più di un link che punta a esso, lo stampiamo
        if (count[t] > 1) {
            trovati = 1;
            print "File di destinazione (risolto): " t;
            print links[t];
            print "--------------------------------------------------";
        }
    }
    
    if (trovati == 0) {
        print "Nessun gruppo di link simbolici che puntano allo stesso file è stato trovato.";
    }
}'