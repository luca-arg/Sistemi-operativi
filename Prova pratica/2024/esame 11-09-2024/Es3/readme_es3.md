# Esercizio 3 - slinout (Classificatore di Symlink)

Questo script Python cerca tutti i link simbolici in una cartella e li classifica come interni o esterni, gestendo correttamente percorsi assoluti e relativi.

## 1. Creazione dell'ambiente di test

Useremo la cartella `/tmp` come "esterno" dell'albero per fare i test. Esegui questi comandi nel terminale:

```bash
# Crea una cartella esterna e un file esterno
mkdir -p /tmp/cartella_esterna
touch /tmp/cartella_esterna/file_fuori.txt

# Crea l'albero di test principale
mkdir -p test_slinout/sottocartella
touch test_slinout/file_dentro.txt

# 1. Crea LINK INTERNO relativo (punta a un file nella stessa cartella)
ln -s file_dentro.txt test_slinout/link_interno_relativo

# 2. Crea LINK INTERNO relativo a directory
ln -s sottocartella test_slinout/link_interno_dir

# 3. Crea LINK ESTERNO relativo (risale l'albero con i .. fino a /tmp)
# Attenzione: i percorsi relativi dipendono da dove lanci il comando.
# Supponendo che la tua current working directory sia la home:
ln -s ../../../../tmp/cartella_esterna test_slinout/link_esterno_relativo

# 4. Crea LINK ESTERNO assoluto (punta direttamente a /tmp)
ln -s /tmp/cartella_esterna/file_fuori.txt test_slinout/link_esterno_assoluto
```

## 2. Esecuzione del Test
Lancia il programma passando come argomento la cartella radice:

```
python3 slinout.py test_slinout
```

Inoltre, testa anche il funzionamento senza parametri (che per consegna deve controllare la directory corrente):

```
cd test_slinout
python3 ../slinout.py
cd ..
```

## 3. Output Atteso
```
--- Link Interni ---
test_slinout/link_interno_relativo
test_slinout/link_interno_dir

--- Link Esterni ---
test_slinout/link_esterno_relativo
test_slinout/link_esterno_assoluto
```
