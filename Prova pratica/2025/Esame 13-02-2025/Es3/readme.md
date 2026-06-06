# Test Esercizio 3 - Ricerca per Dimensione (Python)

Questo test verifica che lo script Python trovi i file con la stessa dimensione del target, scartando correttamente gli hard link.

## 1. Creazione dell'ambiente di test

Esegui questi comandi nel terminale per preparare i file:

```bash
# Crea la cartella principale e una sottocartella
mkdir -p test_env_es3/sottocartella

# 1. Crea il file target (usiamo 'echo -n' per non inserire il carattere di a capo, 
# creando un file di esattamente 20 byte)
echo -n "01234567890123456789" > test_env_es3/target.txt

# 2. Crea un file con la STESSA DIMENSIONE (20 byte) e stesso contenuto (Copia)
cp test_env_es3/target.txt test_env_es3/sottocartella/copia_esatta.txt

# 3. Crea un file con la STESSA DIMENSIONE (20 byte) ma contenuto diverso
echo -n "abcdefghijklmnopqrst" > test_env_es3/stessa_dim_diverso_testo.txt

# 4. Crea un HARD LINK al file target (stessa dimensione, ma STESSO INODE)
ln test_env_es3/target.txt test_env_es3/sottocartella/hardlink_ignorato

# 5. Crea un file con una DIMENSIONE DIVERSA (es. 5 byte)
echo -n "corto" > test_env_es3/file_piccolo.txt





python3 es3.py test_env_es3/target.txt test_env_es3