# Esercizio 3 - Pulizia Duplicati tramite SHA-1

Questo script confronta due directory ed elimina i file con contenuto identico, ma solo se la duplicazione avviene "a cavallo" tra le due cartelle.

## 1. Creazione dell'ambiente di test

Esegui questi comandi per creare due directory e una serie di file mirati:

```bash
mkdir -p dir_A/sotto_A
mkdir -p dir_B

# 1. File unico in A (DEVE RIMANERE)
echo "Contenuto Unico A" > dir_A/unicoA.txt

# 2. File unico in B (DEVE RIMANERE)
echo "Contenuto Unico B" > dir_B/unicoB.txt

# 3. File duplicato internamente SOLO in A (DEVONO RIMANERE ENTRAMBI)
echo "Duplicato Interno" > dir_A/dup_int1.txt
echo "Duplicato Interno" > dir_A/sotto_A/dup_int2.txt

# 4. File condiviso tra A e B (DEVONO ESSERE ELIMINATI ENTRAMBI)
echo "Condiviso" > dir_A/condivisoA.txt
echo "Condiviso" > dir_B/condivisoB.txt

# 5. File condiviso presente più volte (DEVONO ESSERE ELIMINATI TUTTI E TRE)
echo "Super Condiviso" > dir_A/superA1.txt
echo "Super Condiviso" > dir_A/sotto_A/superA2.txt
echo "Super Condiviso" > dir_B/superB.txt

```

## 2. Esecuzione del Test
Lancia lo script passando le due directory come parametri:

```
python3 es3_sha1_cleaner.py dir_A dir_B
```

## 3. Output Atteso
Lo script non stampa nulla, ma verificando il contenuto delle cartelle dovresti trovare solo i file legittimi:

```
ls -R dir_A dir_B
```

## pulizia

```
rm -rf dir_A dir_B
```