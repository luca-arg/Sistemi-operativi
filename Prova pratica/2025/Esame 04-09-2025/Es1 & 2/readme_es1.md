# README - Esercizio 1 (sha1index) ma anche il 2 (basta mettere test_dir2)

Questo programma in C analizza una directory (quella corrente se non viene passato alcun parametro, oppure quella specificata come argomento) e crea una sottodirectory nascosta denominata `.sha1index`. Per ogni file regolare trovato, genera un link simbolico all'interno di `.sha1index` che ha come nome l'hash SHA1 del file e che punta al file originale.

## Compilazione

Per compilare il codice sorgente, apri il terminale e utilizza `gcc`:

```bash
gcc sha1index.c -o sha1index 
```

## Compilazione

```bash
./sha1index test_dir
```


## Verifica output
Per verificare che il programma abbia svolto il suo lavoro, ispeziona il contenuto della cartella nascosta .sha1index generata all'interno della directory target.

```bash
ls -la test_dir/.sha1index/
```

Puoi verificare che i link simbolici funzionino correttamente stampando il loro contenuto tramite il comando cat:

```bash
# Sostituisci <hash> con uno dei nomi generati dal comando precedente
cat test_dir/.sha1index/hash
```