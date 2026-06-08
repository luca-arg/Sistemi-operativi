# Esercizio 2 - Timeout con Auto-Restart ritardato

Questo programma esegue un comando. Se il comando fallisce (exit code != 0) *prima* che scada il timeout, il programma padre aspetta che il timer scada, e poi lo riavvia.

## Compilazione

```bash
gcc timeout_restart.c -o timeout_restart
```

## Creazione del processo "Instabile"
Creiamo uno script di test che fallisce al primo tentativo (in 0 secondi) ma ha successo al secondo.
Esegui questi comandi nel terminale:

```
echo '#!/bin/bash' > test_instabile.sh
echo 'if [ ! -f /tmp/flag_es2 ]; then' >> test_instabile.sh
echo '  echo "-> Tentativo 1: CRASH immediato!"' >> test_instabile.sh
echo '  touch /tmp/flag_es2' >> test_instabile.sh
echo '  exit 1' >> test_instabile.sh
echo 'else' >> test_instabile.sh
echo '  echo "-> Tentativo 2: Funziona!"' >> test_instabile.sh
echo '  rm /tmp/flag_es2' >> test_instabile.sh
echo '  exit 0' >> test_instabile.sh
echo 'fi' >> test_instabile.sh
chmod +x test_instabile.sh
```


## Esecuzione del Test
Lanceremo il programma con un timeout di 4 secondi (4000 ms).
Usiamo il comando time per assicurarci che il padre abbia aspettato il tempo corretto prima di riavviarlo.


```
time ./timeout_restart 4000 ./test_instabile.sh
```

Output Atteso
Il programma farà questo:

Esegue lo script. Lo script stampa "CRASH immediato!" ed esce con errore.

Il padre se ne accorge tramite poll, ma invece di riavviarlo subito, aspetta pazientemente che passino i 4 secondi che avevi impostato all'inizio.

Scaduti i 4 secondi, lo riavvia.

Lo script stampa "Funziona!" ed esce con 0.

Il padre vede il successo e termina.

L'output mostrerà le due stampe a distanza di 4 secondi l'una dall'altra.
Alla fine, time ti mostrerà che il tempo totale di esecuzione reale (real) è stato di circa 4.00x secondi.