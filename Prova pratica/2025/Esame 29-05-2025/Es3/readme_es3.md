# Esercizio 3: Identificazione Collegamenti (cklink / cksymlink)

Questo script Python cerca all'interno di una directory specifica tutti i collegamenti (fisici o simbolici) che puntano a un determinato file bersaglio. Il comportamento dello script è dinamico e cambia in base al nome con cui viene invocato.

## Funzionamento
* **Se chiamato come `cklink`:** Cerca i collegamenti fisici (Hard Link). Ignora i symlink e confronta l'Identificativo Inode (`st_ino`) e il Device ID (`st_dev`) di ogni file con quelli del bersaglio per garantire l'esatta corrispondenza fisica sul disco.
* **Se chiamato come `cksimlink` o `cksymlink`:** Cerca i collegamenti simbolici (Soft Link). Verifica se il file è un link e utilizza `realpath` per risolvere il percorso e controllare se punta al percorso assoluto del file bersaglio.

## Istruzioni di Setup e Test

Per testare correttamente lo script, è necessario creare dei link simbolici al file sorgente originale (`cklink.py`), omettendo l'estensione `.py` come richiesto dalle specifiche.

### 1. Preparazione dell'eseguibile
Rendere lo script eseguibile e creare gli alias necessari:
```bash
chmod +x es3.py
ln -s es3.py cklink
ln -s es3.py cksymlink
```

### 2. Creazione dell'ambiente di test
Creare un file bersaglio, una cartella di test e alcuni file di prova (un hard link, un symlink e un'esca):

```
# Crea bersaglio e cartella

echo "Dati originali" > bersaglio.txt
mkdir test_dir

# Crea i collegamenti validi

ln bersaglio.txt test_dir/hardlink_valido
ln -s ../bersaglio.txt test_dir/symlink_valido

# Crea un'esca che deve essere ignorata

ln -s /tmp test_dir/symlink_falso
```

## 3. Esecuzione dei Test

Testare la ricerca degli Hard Link (utilizzando l'alias cklink):
```
./cklink bersaglio.txt test_dir

# Output atteso: test_dir/hardlink_valido
```


Testare la ricerca dei Link Simbolici (utilizzando l'alias cksymlink):

```
./cksymlink bersaglio.txt test_dir
# Output atteso: test_dir/symlink_valido
```