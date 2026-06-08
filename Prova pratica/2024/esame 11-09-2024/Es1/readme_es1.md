# Esercizio 1 - Timeout basato su Eventi

Questo programma esegue un comando figlio e lo termina forzatamente se la sua esecuzione supera una soglia massima impostata in millisecondi, usando `poll`, `pidfd_open` e `timerfd`.

## Compilazione

Compila il programma dal terminale con i classici flag:

```bash
gcc timeout.c -o timeout

```

## Esecuzione e Testing
Non c'è bisogno di creare file o directory fittizie per questo test. Useremo il comando di sistema sleep, che fa semplicemente mettere in pausa il processo per i secondi specificati.

Anteporremo la parola chiave time ai nostri comandi per visualizzare il tempo effettivo di esecuzione.

Caso 1: Il processo termina IN TEMPO (Nessun omicidio)
Impostiamo un timeout di 5000 millisecondi (5 secondi) per un processo sleep che dura 2 secondi.

```
time ./timeout 5000 sleep 2
```
------

Caso 2: Il processo va IN TIMEOUT (Uccisione)
Impostiamo un timeout di 3000 millisecondi (3 secondi) per un processo sleep che dura 5 secondi.

```
time ./timeout 3000 sleep 5
```