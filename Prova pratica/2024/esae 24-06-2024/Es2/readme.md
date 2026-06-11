# Esercizio 2 - Inotimrun (Multi-Command Runner)

Questo programma estende il demone inotify permettendogli di leggere ed eseguire sequenzialmente blocchi di comandi multipli dallo stesso file trigger, separati da una riga vuota.

## 1. Preparazione e Avvio (Terminale 1)

Crea la directory, compila e avvia il demone:

```bash
mkdir -p test_dir_multi
gcc inotimrun.c -o inotimrun
./inotimrun test_dir_multi
```

## 2. Creazione del file multi-comando (Terminale 2)
Creeremo un singolo file che contiene due blocchi distinti. Il primo blocco stamperà il contenuto di /tmp, il secondo blocco leggerà il file del nome di rete della macchina (/etc/hostname).
(Nota: il comando echo -e converte i \n in veri e propri ritorni a capo).

Bash
```
echo -e "/bin/ls\nls\n/tmp\n\n/bin/cat\ncat\n/etc/hostname" > test_dir_multi/comandi_multipli.txt

```
3. Verifica dei Risultati
Nel Terminale 1, non appena viene rilasciato il file, vedrai prima comparire il listato della directory /tmp, e immediatamente dopo (in modo strettamente sequenziale) il nome del tuo computer.

Nel Terminale 2, controlla che il file sia stato rimosso solo alla fine dell'intero ciclo:

Bash

```
ls -la test_dir_multi
```