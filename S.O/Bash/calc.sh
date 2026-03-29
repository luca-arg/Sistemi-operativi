#3. Scrivi calc.sh che calcola somma, differenza e prodotto di $1 e $2 usando
#expr. Aggiungi anche il confronto A > B.

echo "Somma: $(expr $1 + $2)"
echo "Differenza: $(expr $1 - $2)"
echo "Prodotto: $(expr $1 \* $2)"   
if [ $(expr $1 \> $2) -eq 1 ]; then
    echo "$1 è maggiore di $2"
else
    echo "$1 non è maggiore di $2"
fi
