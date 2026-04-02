#5. Scrivi testint.sh che legge due interi e usa il test per:
#confrontare a e b (-gt, -eq, -lt)
#verificare se a è negativo
#usare una negazione: !

read -p "Inserisci il primo intero (a): " a
read -p "Inserisci il secondo intero (b): " b

if [ $a -gt $b ]; then
    echo "$a è maggiore di $b"
elif [ $a -eq $b ]; then
    echo "$a è uguale a $b"
else
    echo "$a è minore di $b"
fi

if [ $a -lt 0 ]; then
    echo "$a è negativo"
fi

if [ ! $a -lt 0 ]; then
    echo "$a non è negativo"
fi