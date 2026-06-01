# Esercizi Laboratorio Sistemi Operativi - IPC tramite Segnali (Esercizio 2)

Questo progetto contiene la soluzione all'es 2 della prova pratica di laboratorio del 09 febbraio 2026. L'esercizio estende il precedente, permettendo l'invio di stringhe di lunghezza arbitraria tramite segnali `sigqueue`.

La stringa viene frammentata in pacchetti di 8 byte e la comunicazione è sincronizzata tramite un meccanismo di ACK (acknowledgment).

## File Inclusi
* `sigrx.c`: Il processo ricevitore. Attende segnali `SIGUSR1`, stampa a schermo gli 8 byte ricevuti e invia un segnale di conferma (`SIGUSR2`) al mittente usando il PID estratto da `siginfo_t`.
* `sigtx.c`: Il processo trasmettitore. Invia i frammenti della stringa tramite `SIGUSR1` e attende in pausa (`pause()`) la ricezione di `SIGUSR2` prima di inviare i successivi 8 byte.

## Compilazione
Per compilare i file sorgente, utilizza `gcc`:
```bash
gcc sigrx.c -o sigrx
gcc sigtx.c -o sigtx
```

## Test 
```bash
lato rivevente: ./sigrx
lato trasmittente: ./sigtx 12345 "Questa_e_una_stringa_molto_lunga_per_testare_IPC"
```


