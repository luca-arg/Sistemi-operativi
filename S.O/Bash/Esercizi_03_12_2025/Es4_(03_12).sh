#!/bin/bash
# Cancella i file di backup di emacs, previo consenso
for file in $(ls *~) # elenca i file di backupe
do
 echo -n "Sei sicuro di voler rimuovere $file ?"
 read reply
 if [ $reply = "Y" -o $reply = "y" ]; then
 rm -f $file # rimuove il file
echo File $file removed
 fi
done