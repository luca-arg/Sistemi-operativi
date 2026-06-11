# Documentazione: inotirun (Inotify Command Runner)
Questo documento descrive l'ordine cronologico degli eventi gestiti dal programma e fornisce le istruzioni pratiche per testarne il funzionamento localmente.

## L'Ordine Cronologico degli Eventi
Il programma gestisce due flussi di dati separati: il buffer degli eventi di inotify e lo stream testuale (FILE *) del singolo file elaborato. Ecco cosa accade passo passo quando un utente crea il file comando1.txt nella directory monitorata:

1. Apertura: Il programma apre fisicamente comando1.txt e crea lo stream f (il "tubo" di comunicazione per leggere i caratteri).

2. Estrazione dell'Eseguibile: Viene effettuata la prima chiamata a getline(..., f). Questa estrae la riga 1 (il percorso assoluto dell'eseguibile, es. /bin/ls) e sposta automaticamente il cursore di lettura alla riga 2.

3. Ingresso nel Ciclo: Il programma entra nel ciclo while (getline(..., f) != -1).

4. Estrazione degli Argomenti: Il ciclo inizia a "succhiare" dallo stream f tutte le righe rimanenti, salvandole una per una nell'array cmd_argv (es. ls, -l, /tmp).

5. Fine File (EOF): Quando comando1.txt è stato letto fino all'ultima riga, getline non trova più dati e restituisce -1.

6. Uscita dal Ciclo: L'esecuzione esce dal while. L'array dei comandi è pronto.

7. Esecuzione (Fork & Exec): Il processo genera un figlio che lancia il comando assemblato utilizzando la system call execv.

8. Pulizia: Il padre chiude il tubo di lettura con fclose(f) e cancella fisicamente comando1.txt dalla cartella tramite unlink().

9. Ritorno in Ascolto: Solo a questo punto il blocco di codice relativo al file termina. Il ciclo for esterno fa un passo in avanti sul buffer grezzo di inotify per controllare se, nel frattempo, è stato inserito un altro file (es. comando2.txt). In caso affermativo, l'intero processo riparte dal punto 1 aprendo un nuovo tubo f.

# Esecuzione e Test dell'Ambiente
Per verificare correttamente il comportamento reattivo e asincrono di inotify, è necessario utilizzare due sessioni terminale separate.

## 1. Preparazione e Avvio (Terminale 1)
Crea la directory di test, compila il codice sorgente e metti il demone in ascolto. Il terminale sembrerà "bloccato", indicando che inotify è in stato di attesa passiva (zero consumo CPU).

```
# 1. Crea la directory vuota (sostituisci "test_dir" a piacimento)
mkdir -p test_dir

# 2. Compila il codice C
gcc  inotirun.c -o inotirun

# 3. Avvia il programma agganciandolo alla directory
./inotirun test_dir
```

## Test A: Comando con opzioni e argomenti
Inietta un file formattato per stampare i dettagli della cartella /tmp:

## Test B: Comando semplice
Inietta un secondo file per stampare il percorso di lavoro attuale:

```

echo -e "/bin/pwd\npwd" > test_dir/comando2.txt
```

## Nel Terminale 2: 

Verifica che la logica di smaltimento del programma abbia funzionato. La directory deve risultare completamente ripulita dai file di trigger.

```
ls -la test_dir
```