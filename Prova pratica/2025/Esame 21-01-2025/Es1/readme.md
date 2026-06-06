# Compilazione
gcc samecont.c -o samecont

# Preparazione ambiente
mkdir -p test_samecont/dir_interna
echo -n "esattamente 20 bytes" > test_samecont/target.txt

# 1. Stessa dimensione, file distinto (DEVE ESSERE TROVATO)
echo -n "un altro di 20 bytes" > test_samecont/dir_interna/valido.txt

# 2. Dimensione diversa (DEVE ESSERE IGNORATO)
echo -n "corto" > test_samecont/corto.txt

# 3. Hard link al target (DEVE ESSERE IGNORATO)
ln test_samecont/target.txt test_samecont/dir_interna/hardlink_target

# Esecuzione
./samecont test_samecont/target.txt test_samecont