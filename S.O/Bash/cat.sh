#Scrivi cat.sh che usa un here-document per inviare:
#un messaggio contenente le variabili $1 e $2.
# mostra 'cat effettuato a <dest>' alla fine.

cat << END
Hai passato argomento: $1
Cat effettuato a: $2
END
