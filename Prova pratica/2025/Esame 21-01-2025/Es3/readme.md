# Esercizio 3 - Ordinamento per Profondità e Nome (Python)

Questo script estrae tutti i file di un sottoalbero e li stampa ordinandoli prima dal più profondo al più superficiale, e poi alfabeticamente a parità di livello.

## 1. Creazione dell'ambiente di test

Copia e incolla questi comandi nel terminale per generare una struttura di directory su tre livelli:

```bash
# Crea le directory (Livello 1, Livello 2 e Livello 3)
mkdir -p test_ordinamento/livello2_b/livello3
mkdir -p test_ordinamento/livello2_a

# Crea file nel LIVELLO 3 (I più profondi, appariranno per primi)
touch test_ordinamento/livello2_b/livello3/file_profondo.txt

# Crea file nel LIVELLO 2 (Appariranno per secondi. Devono essere ordinati alfabeticamente)
touch test_ordinamento/livello2_b/z_file.txt
touch test_ordinamento/livello2_b/a_file.txt
touch test_ordinamento/livello2_a/m_file.txt

# Crea file nel LIVELLO 1 (Radice. Appariranno per ultimi. Devono essere ordinati alfabeticamente)
touch test_ordinamento/zebra.txt
touch test_ordinamento/albero.txt
```


## esecuzione
```
python3 esercizio3.py test_ordinamento
```
## output
```
test_ordinamento/livello2_b/livello3/file_profondo.txt
test_ordinamento/livello2_b/a_file.txt
test_ordinamento/livello2_a/m_file.txt
test_ordinamento/livello2_b/z_file.txt
test_ordinamento/albero.txt
test_ordinamento/zebra.txt
```