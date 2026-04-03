# Esercizio 3: Python o bash: 10 punti
# Scrivere un programma python o uno script bash che data una directory passata come parametro
# produca una lista dei link simbolici presenti nel sottoalbero che fanno riferimento allo stesso file.
# Esempio, in questo caso:
# $ ls -lR /tmp/test
# /tmp/test:
# total 4
# drwxr-xr-x 2 renzo renzo 4096 Sep 10 15:45 d
# -rw-r--r-- 1 renzo renzo 0 Sep 10 15:41 file1
# -rw-r--r-- 1 renzo renzo 0 Sep 10 15:41 file2
# lrwxrwxrwx 1 renzo renzo 5 Sep 10 15:42 sl1 -> file1
# lrwxrwxrwx 1 renzo renzo 5 Sep 10 15:42 sl1bis -> file1
# lrwxrwxrwx 1 renzo renzo 5 Sep 10 15:49 sl2 -> file2
# /tmp/test/d:
# total 0
# lrwxrwxrwx 1 renzo renzo 15 Sep 10 15:45 gsld -> /tmp/test/file1
# lrwxrwxrwx 1 renzo renzo 8 Sep 10 15:43 sld -> ../file1
# il programma lanciato con parametro /tmp/test deve trovare che sl1, sl1bis, d/sld e d/gllsd indicano lo
# stesso file. (similmente dovrebbe rilevare altri insiemi di link simbolici che indicano lo stesso file)
import os
import sys
import argparse
from collections import defaultdict

def trova_link_similari(directory):
    """
    Scansiona la directory e raggruppa i link simbolici che puntano allo stesso file.
    """
    # Usiamo defaultdict: crea automaticamente una lista vuota se la chiave non esiste
    mappa_link = defaultdict(list)
    
    # os.walk scansiona tutto l'albero delle directory in modo efficiente
    for root, dirs, files in os.walk(directory):
        # Uniamo file e cartelle, poiché anche le cartelle possono essere linkate
        for name in files + dirs:
            full_path = os.path.join(root, name)
            
            # Controlliamo se l'elemento è effettivamente un symlink
            if os.path.islink(full_path):
                try:
                    # os.path.realpath risolve tutti i symlink (anche a cascata) 
                    # restituendo il percorso assoluto e canonico finale
                    target_reale = os.path.realpath(full_path)
                    
                    # Raggruppiamo il link usando il target reale come chiave
                    mappa_link[target_reale].append(full_path)
                except OSError as e:
                    # Gestione di eventuali permessi negati o errori di I/O
                    print(f"Avviso: Impossibile leggere il link {full_path} ({e})", file=sys.stderr)

    # Output formattato dei risultati
    trovati = False
    for target, links in mappa_link.items():
        # Ci interessano solo i file che hanno PIÙ DI UN link che punta a loro
        if len(links) > 1:
            trovati = True
            print(f"File di destinazione (risolto): {target}")
            for link in links:
                print(f"  -> {link}")
            print("-" * 50)
            
    if not trovati:
        print("Nessun gruppo di link simbolici che puntano allo stesso file è stato trovato.")


if __name__ == "__main__":
    # Utilizziamo argparse (come da teoria) per un'interfaccia a riga di comando professionale
    parser = argparse.ArgumentParser(
        description="Trova e raggruppa i link simbolici in un sottoalbero che puntano allo stesso file reale."
    )
    parser.add_argument(
        "directory", 
        help="Il percorso della directory da scansionare"
    )
    
    # Parsa gli argomenti passati allo script
    args = parser.parse_args()
    
    # Validazione dell'input
    if not os.path.isdir(args.directory):
        print(f"Errore fatale: '{args.directory}' non è una directory valida o non esiste.", file=sys.stderr)
        sys.exit(66) # 66 è spesso usato in Unix per indicare "cannot open input" o file non trovati
        
    trova_link_similari(args.directory)
