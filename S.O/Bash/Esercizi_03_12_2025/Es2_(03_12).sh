#!/bin/bash
# stampa utenti che consumano piu’ spazio su HD
case "$1" in #se nessun argomento passato ne prende 50 di default
"") lines=50
;; #se argomento non numerico mostra messaggio di errore
*[!0-9]*) echo "Usage: `basename $0` usersnum";
exit 1
;; #se argomento numerico lo assegna a lines
 *) lines=$1
;; #fine del case 
esac
du -s /tmp/* | sort -gr | head -$lines  #comando che mostra gli utenti che consumano piu’ spazio su HD