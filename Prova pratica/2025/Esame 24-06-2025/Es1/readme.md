# Esercizio 1: Comunicazione Inter-Processo (IPC) Base tramite Segnali

Questo progetto implementa un sistema di trasmissione di stringhe tra due processi (mittente e ricevitore) a livello di singolo bit, utilizzando esclusivamente i segnali POSIX (`SIGUSR1` e `SIGUSR2`).

## Funzionamento
* **`semrecv.c` (Ricevitore):** Si mette in ascolto bloccante. Usa il segnale `SIGUSR1` per i bit `0` e `SIGUSR2` per i bit `1`. Ricompone i bit in caratteri e stampa la stringa appena riceve il terminatore `\0`. Invia un ACK (`SIGUSR1`) al mittente dopo ogni bit ricevuto.
* **`semsend.c` (Mittente):** Scompone una stringa in singoli bit tramite shift e maschere bit a bit. Attende rigorosamente l'ACK dal ricevitore tramite `sigsuspend` prima di inviare il bit successivo, evitando *Race Conditions*.

## Comandi di Test

1. **Compilazione:**
   ```bash
   gcc  -o semrecv semrecv.c
   gcc  -o semsend semsend.c


   ------
   ./semrecv

   -----
   ./semsend 12345 "Messaggio di prova bit a bit"
