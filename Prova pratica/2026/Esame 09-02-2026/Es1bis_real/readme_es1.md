# Esercizi Laboratorio Sistemi Operativi - IPC tramite Segnali

Questo progetto contiene la soluzione all' es 1 
prova pratica di laboratorio del 09 febbraio 2026. I programmi dimostrano la comunicazione tra processi (IPC) su architetture a 64 bit, sfruttando il payload dei segnali (`sigqueue`) per trasmettere stringhe fino a 8 caratteri.


## File Inclusi
* `sigrx.c`: Il processo ricevitore. Attende segnali `SIGUSR1` in modo asincrono ed estrae i dati fisicamente scritti nei 64 bit del puntatore del payload.
* `sigtx.c`: Il processo trasmettitore. Invia un segnale `SIGUSR1` a un PID bersaglio, incapsulando una stringa convertita all'interno della struttura nativa del segnale.

## Preparazione dell'Ambiente (Esercizio 0)
Prima di procedere con la compilazione e i test, metti in sicurezza l'ambiente di lavoro eseguendo questi comandi nel terminale:
```bash
# 1. Rende inaccessibile la tua home directory
chmod 700 ~

# 2. Crea la cartella pubblica con il tuo username
mkdir -p /public/$USER

# 3. Imposta i permessi corretti alla cartella pubblica
chmod 700 /public/$USER

# 4. Spostati nella cartella per lavorare
cd /public/$USER
```

## Esercizio 1: Trasmettitore (`sigtx.c`) e Ricevitore (`sigrx.c`)

## Compilazione
Per compilare i file sorgente, utilizza `gcc`. Non sono necessarie librerie esterne particolari:
```bash
gcc sigrx.c -o sigrx
gcc sigtx.c -o sigtx
```

## Guida al Test (Esercizio 1)

Per testare il corretto passaggio dei messaggi, apri due terminali separati (entrambi posizionati nella cartella `/public/tuousername`).

### Passo 1: Avviare il Ricevitore (Terminale 1)
Lancia il ricevitore. Il programma stamperà a schermo il proprio PID vitale per la comunicazione.
```bash
./sigrx
```

**Output atteso:**
> PID sigrx: 12345
> In attesa di segnali...

*(Prendi nota del PID stampato a schermo, nell'esempio 12345).*

### Passo 2: Inviare il Messaggio (Terminale 2)
Usa il trasmettitore passando come argomenti il PID appena letto e un messaggio lungo al massimo 8 caratteri.
```bash
./sigtx 12345 PROVA_OS
```

**Output atteso sul Terminale 2:**
> Messaggio 'PROVA_OS' inviato con successo al PID 12345.

### Passo 3: Verificare la Ricezione
Torna sul Terminale 1. Il processo in background si sarà risvegliato per intercettare il segnale, confermando l'avvenuta ricezione dei byte:

**Output atteso sul Terminale 1:**
> Messaggio ricevuto: PROVA_OS