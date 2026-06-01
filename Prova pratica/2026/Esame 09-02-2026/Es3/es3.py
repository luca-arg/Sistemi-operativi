import sys
import os
import pathlib

if len(sys.argv) != 2:
    sys.exit(1)

pattern = sys.argv[1]  # Il pattern da cercare nei file
risultati = []

def esplora(directory):
    try:
        p = pathlib.Path(directory)
        for x in p.iterdir():
            if x.is_dir():
                esplora(x)
            elif x.is_file():
                try:
                    f = open(x, "r", encoding="ascii", errors="ignore")
                    contenuto = f.read()
                    f.close()
                    
                    if pattern in contenuto:
                        stat_info = os.stat(x)
                        risultati.append((x, stat_info.st_mtime))
                except OSError:
                    pass
    except OSError:
        pass



esplora('.')

risultati.sort(key=lambda val: val[1])# ordina i risultati in base alla data di modifica (st_mtime) ovvero in ordine crescente (dal più vecchio al più recente) 
#key=lambda val: val[1] indica che la chiave di ordinamento è il secondo elemento della tupla (st_mtime)

for f, t in risultati:
    print(f)