#!/bin/bash
if [ ! -f /tmp/flag_es2 ]; then
  echo "-> Tentativo 1: CRASH immediato!"
  touch /tmp/flag_es2
  exit 1
else
  echo "-> Tentativo 2: Funziona!"
  rm /tmp/flag_es2
  exit 0
fi
