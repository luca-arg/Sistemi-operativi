# Sistemi-operativi

Raccolta esercizi svolti su  Bash e C.

---

## BASH

### Come testare i codici

Per provare che tutto funzioni correttamente, apri il terminale, assicurati di essere nella cartella dove hai i file e segui questi passaggi:

1.  **Salva lo script** con estensione `.sh`.
2.  Se sei su **Linux/macOS**, rendilo eseguibile digitando:
    ```bash
    chmod +x nome_file.sh
    ```
3.  Se sei su **Windows (PowerShell)**, avvia lo script con Bash (WSL o Git Bash):
    ```powershell
    bash .\nome_file.sh
    ```

---

### Esercizi del 03/12/2025

Di seguito la descrizione e le funzionalità degli script realizzati:

#### 1. Menu Selezione Ruolo (`Es1_(03_12).sh`)
Script interattivo che simula la gestione di ruoli utente.
* **Funzionamento**: Utilizza un ciclo `while` infinito per mostrare un menu.
* **Logica**: Associa a ogni numero (1-3) una funzione specifica (`administrator`, `student`, `teacher`) che stampa il ruolo a video.
* **Uscita**: Digitando `0`, la variabile `stop` viene impostata a 1, interrompendo il ciclo.

#### 2. Monitoraggio Spazio Disco (`Es2_(03_12).sh`)
Utility per individuare i file o le cartelle che occupano più spazio nella directory `/tmp`.
* **Parametri**: Accetta un numero come argomento per limitare i risultati (es. `./Es2.sh 10`).
* **Default**: Se non viene passato alcun argomento, mostra i primi 50 risultati.
* **Comando core**: Utilizza `du -s /tmp/* | sort -gr | head -$lines` per calcolare e ordinare le dimensioni.

#### 3. Generatore Tabelline (`Es3_(03_12).sh`)
Genera una tavola pitagorica basata su un valore massimo fornito dall'utente.
* **Utilizzo**: Richiede un argomento numerico (es. `./Es3.sh 5`).
* **Logica**: Sfrutta due cicli `while` annidati e il comando `expr` per calcolare i prodotti tra le variabili `x` e `y`.

#### 4. Pulizia Backup Emacs (`Es4_(03_12).sh`)
Script per la rimozione selettiva dei file di backup temporanei (caratterizzati dal suffisso `~`).
* **Funzionamento**: Esegue un ciclo `for` su tutti i file trovati tramite `ls *~`.
* **Sicurezza**: Prima di ogni eliminazione (`rm -f`), richiede una conferma esplicita all'utente digitando `Y` o `y`.

#### 5. Rimozione Sicura (`Es_saferem.sh`)
Script avanzato per la gestione di un cestino personalizzato con supporto al ripristino e gestione omonimie.

---

### Come testare lo script `Es_saferem.sh`

Dopo aver reso lo script eseguibile, assicurati di avere le cartelle `trash` e `ripristinati` nella stessa directory.

**1. Creazione dei file fittizi per i test**
```bash
touch file1.txt file2.txt file_omonimo.txt

**2. Test spostamento nel cestino**
"Cancella" i primi due file:
```bash
./Es_saferem.sh file1.txt file2.txt
```

**3. Test visualizzazione cestino (`-L`)**
Verifica che i file siano effettivamente nel cestino:
```bash
./Es_saferem.sh -L
```

**4. Test ripristino (`-R`)**
Ripristina il primo file (verrà spostato dal cestino alla cartella `ripristinati`):
```bash
./Es_saferem.sh -R file1.txt
```

**5. Test gestione omonimie**
Sposta il file omonimo nel cestino:
```bash
./Es_saferem.sh file_omonimo.txt
```
Ora crea un **nuovo file** con lo stesso identico nome e spostalo di nuovo nel cestino:
```bash
touch file_omonimo.txt
./Es_saferem.sh file_omonimo.txt
```
Se controlli il cestino (`./Es_saferem.sh -L`), troverai due file: uno chiamato `file_omonimo.txt` e l'altro rinominato in automatico con un timestamp (es. `file_omonimo.txt.1712345678`).

**6. Test svuotamento totale (`-P`)**
Infine, pulisci definitivamente il cestino svuotando la cartella:
```bash
./Es_saferem.sh -P
```



---

### Esercizi Lezioni

In questa sezione sono raccolti gli script focalizzati sulle basi del linguaggio Bash: gestione dei parametri, variabili speciali, input/output e operatori logici.

#### 1. Variabili di Sistema e Parametri (`info.sh`)
Uno script per visualizzare le informazioni di contesto fornite dalla shell.
* **Funzionamento**: Stampa i metadati dello script in esecuzione.
* **Variabili mostrate**: 
    * `$0`: Nome del file dello script.
    * `$$`: PID (Process ID) dell'istanza corrente.
    * `$#`: Conteggio dei parametri passati.
    * `$*`: Stringa contenente tutti i parametri.

#### 2. Calcolatrice con `expr` (`calc.sh`)
Esegue operazioni aritmetiche e confronti logici tra due numeri passati come argomenti.
* **Operazioni**: Calcola somma, differenza e prodotto.
* **Confronto**: Utilizza `expr $1 \> $2` per verificare se il primo numero è maggiore del secondo, restituendo un risultato booleano gestito da un costrutto `if`.

#### 3. Gestione Output con Here-Document (`cat.sh`)
Dimostra l'uso del costrutto `here-document` per gestire blocchi di testo multilinea.
* **Funzionamento**: Invia allo standard output un messaggio preformattato che integra dinamicamente i parametri `$1` (argomento) e `$2` (destinazione).

#### 4. Controllo File Vuoti (`checkfile.sh`)
Verifica se un file è vuoto confrontandolo con il dispositivo nullo del sistema.
* **Logica**: Utilizza il comando `cmp` tra un file locale e `/dev/null`.
* **Redirezione**: L'output e gli errori sono rediretti in `/dev/null` (`2>&1`) per mantenere la pulizia del terminale.
* **Exit Status**: Sfrutta la variabile `$?` per determinare se il file è vuoto (status 0) o meno.

#### 5. Test e Operatori Logici (`testinit.sh`)
Approfondimento sull'uso del comando `test` (sintassi `[]`) per il confronto tra interi.
* **Confronti**: Utilizza i flag `-gt` (greater than), `-eq` (equal) e `-lt` (less than).
* **Negazione**: Mostra l'uso dell'operatore `!` per invertire una condizione logica (es. verificare se un numero *non* è negativo).

---


---

## PYTHON (Moduli di Sistema)

### Come testare i codici

Per provare che tutto funzioni correttamente, apri il terminale, assicurati di essere nella cartella dove hai i file e segui questi passaggi:

1.  **Salva lo script** con estensione `.py`.
2.  Assicurati di avere Python 3 installato sul tuo sistema.
3.  Avvia lo script digitando:
    ```bash
    python3 nome_file.py [argomenti]
    ```
    *(In alternativa, su Windows o ambienti configurati diversamente, potrebbe bastare il comando `python nome_file.py`).*
4.  Per visualizzare l'help interattivo e i parametri accettati dallo script (generato in automatico tramite `argparse`), usa:
    ```bash
    python3 nome_file.py -h
    ```

---

### Esercizi Pratici (Esami)

## VERSIONE PYTHON
Di seguito la descrizione dello script realizzato utilizzando i moduli standard di Python per l'interazione con il sistema operativo:

#### 1. Ricerca e Raggruppamento Link Simbolici (`Es3.py`)
Script che analizza ricorsivamente un sottoalbero di directory e raggruppa i link simbolici che fanno riferimento allo stesso file reale.

* **Moduli utilizzati**: 
    * `os`: Navigazione del file system (`os.walk`), controllo della natura dei file (`os.path.islink`) e risoluzione dei percorsi (`os.path.realpath`).
    * `sys`: Gestione degli errori fatali ed exit code specifici (`sys.stderr`, `sys.exit`).
    * `argparse`: Creazione di un'interfaccia a riga di comando robusta e auto-documentata.
    * `collections`: Uso di `defaultdict` per semplificare la logica di inserimento in dizionario.
* **Logica**:
    * Sfrutta `os.walk` per scansionare sia file che cartelle.
    * Risolve il percorso reale (gestendo link relativi, assoluti e a cascata) restituendo un path canonico assoluto.
    * Raggruppa i link in un dizionario usando il target reale come chiave.
* **Filtro**: Mostra a video solo i file fisici a cui puntano *almeno due* link simbolici distinti, ignorando i link orfani o univoci.

### Come testare lo script `Es3.py`

Per verificare il corretto funzionamento, è necessario ricreare una struttura di file e link (sia assoluti che relativi) all'interno di una cartella temporanea (es. `/tmp/test`).

**1. Creazione della struttura e dei file reali**
Crea la directory principale e una sottocartella, poi aggiungi due file reali vuoti:
```bash
mkdir -p /tmp/test/d
touch /tmp/test/file1
touch /tmp/test/file2
```

### 2. Creazione dei link simbolici
Spostati nella cartella principale e crea i link (simulando percorsi relativi e assoluti):
```bash
cd /tmp/test
ln -s file1 sl1
ln -s file1 sl1bis
ln -s file2 sl2
ln -s /tmp/test/file1 d/gsl1
ln -s ../file1 d/sl1
```

### 3. Esecuzione dello script
Spostati nella cartella dove hai salvato Es3.py e avvialo passando la cartella di test come parametro:
```bash
python3 Es3.py /tmp/test
```

### 4. Risultato atteso
Lo script ignorerà sl2 (poiché è l'unico link a puntare a file2) e raggrupperà correttamente tutti gli altri sotto file1:
```bash
File di destinazione (risolto): /tmp/test/file1
  -> /tmp/test/sl1
  -> /tmp/test/sl1bis
  -> /tmp/test/d/gsl1
  -> /tmp/test/d/sl1
--------------------------------------------------
```

### 5. Pulizia (Opzionale)
Terminato il test, rimuovi la cartella temporanea dal file system per fare pulizia:
```bash
rm -r /tmp/test
```
---
## VERSIONE BASH
### Punti 1 e 2 come prima

### 3. Rendere eseguibile ed eseguire lo script
Torna nella cartella dove hai salvato lo script, dagli i permessi di esecuzione e avvialo:

```bash
chmod +x Es3.sh
./Es3.sh /tmp/test
```

### Punti 4 e 5 come prima

---
---
## C

### Come compilare ed eseguire i codici

Per i file scritti in linguaggio C, è necessario trasformare il codice sorgente in un file eseguibile tramite un compilatore (come `gcc`).

1.  **Apri il terminale** nella cartella dove si trova il file `.c`.
2.  **Compila il file** digitando:
    ```bash
    gcc nome_file.c -o nome_file
    ```
    *(Il parametro `-o` serve a specificare il nome dell'eseguibile finale).*

3.  **Esegui il programma** generato:
    * Su **Linux/macOS**:
        ```bash
        ./nome_file
        ```
    * Su **Windows (Prompt/PowerShell)**:
        ```powershell
        .\nome_file.exe
        ```
---