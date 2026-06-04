### Esercizio 2: Trasmissione Concorrente / Multiplexer (`README.md`)


# Esercizio 2: IPC Concorrente con Multiplexing dei Segnali

Evoluzione dell'Esercizio 1 per gestire trasmissioni simultanee da parte di mittenti multipli. Gestisce l'accavallamento dei segnali e ricostruisce i messaggi separatamente per ogni mittente.

## Funzionamento
* **`semrecv.c` (Ricevitore Avanzato):** Utilizza il flag `SA_SIGINFO` per estrarre il PID dei mittenti (`info->si_pid`). Mantiene uno stato separato (buffer, bit ricevuti, carattere corrente) per ogni PID tramite un array di struct `Client`. Stampa i messaggi completi solo quando viene ricevuto il carattere `\0`.
* **`semsend.c` (Mittente con Jitter):** Include un ritardo casuale (`usleep` variabile) prima dell'invio di ogni bit per forzare lo scheduler del sistema operativo a generare accavallamenti realistici (interleaving) dei messaggi in arrivo al ricevitore.

## Comandi di Stress Test

1. **Compilazione:**
   ```bash
   gcc  -o semrecv semrecv.c
   gcc  -o semsend semsend.c


   ----
   ./semrecv

   -----
   in terminali differenti:

   
   ./semsend 9999 "Primo messaggio concorrente" 
   ./semsend 9999 "Secondo messaggio in parallelo" 
   ./semsend 9999 "Terzo messaggio di stress test" &



