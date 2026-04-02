#4. Scrivi checkfile.sh che:
#usa cmp file /dev/null
#redirige l'output in /dev/null
#stampa se il file è vuoto
#visualizza l'exit status

cmp file /dev/null > /dev/null 2>&1 #con cmp confronto il file con /dev/null, se sono uguali (cioè se il file è vuoto) cmp restituisce 0, altrimenti restituisce un numero diverso da 0. Redirigo l'output standard e l'output di errore in /dev/null per evitare che cmp stampi qualcosa a schermo. va messo "2>&1" per redirigere anche l'output di errore (stderr) in /dev/null, altrimenti se il file non esiste cmp restituirebbe un messaggio di errore che verrebbe stampato a schermo, e noi vogliamo evitare questo.
if [ $? -eq 0 ]; then
    echo "Il file è vuoto"
else
    echo "Il file non è vuoto"
fi