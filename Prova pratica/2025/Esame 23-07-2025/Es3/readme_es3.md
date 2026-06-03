# README - Esercizio 3 (dremcont)

Questo script cerca e distrugge tutti i cloni di un file specifico all'interno di una directory (e delle sue sottocartelle), confrontandone il contenuto.

## Preparazione dell'Ambiente di Test

Creiamo un file originale, una cartella di test e inseriamo al suo interno dei file clonati e dei file diversi.

```bash
# Crea il file originale da usare come riferimento
echo "Questo e' il contenuto da cercare" > file_originale.txt

# Crea la directory di test e una sottocartella
mkdir -p test_dir/sottocartella

# Crea i cloni (stesso contenuto)
cp file_originale.txt test_dir/clone_1.txt
cp file_originale.txt test_dir/sottocartella/clone_2.txt

# Crea file con contenuto diverso (non devono essere cancellati)
echo "Contenuto diverso" > test_dir/file_salvo.txt
```

## Esecuzione
Avvia lo script passando prima il file originale e poi la directory in cui cercare.
```
chmod +x dremcont.sh
./dremcont.sh file_originale.txt test_dir

python3 dremcont.py file_originale.txt test_dir
```

## Verifica dei Risultati
Controlla il contenuto della cartella di test:

```
ls -R test_dir
```
