# Sistemi-operativi

Raccolta esercizi svolti su C e Bash.

---

## BASH

### Come testare i codici

Per provare che tutto funzioni correttamente, apri il terminale, assicurati di essere nella cartella dove hai i file e segui questi passaggi:

1. Salva lo script.

2. Se sei su **Linux/macOS**, rendilo eseguibile digitando:
   ```bash
   chmod +x file.sh
   ```

3. Se sei su **Windows (PowerShell)**, `chmod` non esiste: avvia lo script con Bash (WSL o Git Bash), ad esempio:
  ```powershell
  bash .\file.sh
  ```

  Se invece sei gia nel terminale **Bash/WSL**, non usare `bash .\file.sh` (sintassi PowerShell):
  ```bash
  ./file.sh
  ```

  Se usi WSL, puoi anche usare:
  ```powershell
  wsl bash ./file.sh
  ```

### Esercizi vari

* **Esercizi 03_12_2025**
  * `Es_saferem.sh`

---

### Come testare lo script `Es_saferem.sh`

Dopo aver reso lo script eseguibile, assicurati di avere le cartelle `trash` e `ripristinati` nella stessa directory dello script. Poi segui questi passaggi per verificare tutte le funzionalità:

**1. Creazione dei file fittizi per i test**
Genera tre file vuoti da usare per le prove:
```bash
touch file1.txt file2.txt file_omonimo.txt
```


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