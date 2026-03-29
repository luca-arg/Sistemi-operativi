#4. Scrivi checkfile.sh che:
#usa cmp file /dev/null
#redirige l'output in /dev/null
#stampa se il file è vuoto
#visualizza l'exit status

cmp file /dev/null > /dev/null 2>&1 
if [ $? -eq 0 ]; then
    echo "Il file è vuoto"
else
    echo "Il file non è vuoto"
fi