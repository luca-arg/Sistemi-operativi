# Esercizio 2 - Uguaglianza temporale con esclusione dei link (modif=)

Questo progetto contiene la soluzione all'Esercizio 2 della prova pratica. Il programma C `modif=` esplora l'albero delle directory ed elenca i pathname dei file che hanno un tempo di modifica (mtime) identico a quello di un file passato come parametro.

La logica del programma scarta automaticamente i link fisici (hard link) e i link logici (symlink) che puntano al file di riferimento, assicurandosi di stampare solo file genuinamente indipendenti.

## File Inclusi
* `modif=.c`: Il codice sorgente principale richiesto dall'esame.
* `setup.c`: Un programma di utilità scritto in C che utilizza le system call POSIX (`utimensat`, `link`, `symlink`) per generare automaticamente un ambiente di test insidioso (con timestamp falsificati e link).

## 1. Compilazione
Aprire il terminale e compilare entrambi i file sorgente tramite `gcc`:

```bash
# Compila il programma d'esame
gcc modif=.c -o modif=

# Compila il generatore dell'ambiente di test
gcc setup.c -o setup
```


NOTA:

Invece di creare i file a mano, eseguiamo il programma di setup.
Questo programma creerà 4 file nella directory corrente:

1. file_ref.txt: Il nostro file di riferimento.

2. clone_temporale.txt: Un file indipendente ma a cui viene iniettato (tramite utimensat) lo stesso identico timestamp del file di riferimento.

3. hard_link.txt: Un collegamento fisico a file_ref.txt.

4. sym_link.txt: Un collegamento logico a file_ref.txt, il cui orario di modifica viene allineato artificialmente senza seguire il link (usando il flag AT_SYMLINK_NOFOLLOW).


##  2. Esecuzione
```bash
./setup
```
(Puoi verificare la corretta creazione dei file e dei loro timestamp esatti al nanosecondo lanciando il comando stat *.txt).



```bash
./modif= file_ref.txt


Verifica dell'Output:

Il programma analizzerà la cartella. Sfruttando lstat e stat, rileverà che hard_link.txt e sym_link.txt condividono lo stesso i-node o device del file di riferimento, scartandoli per evitare loop o falsi positivi.

Il programma stamperà esclusivamente il file indipendente con la data clonata:

Output atteso a terminale:

./clone_temporale.txt
```