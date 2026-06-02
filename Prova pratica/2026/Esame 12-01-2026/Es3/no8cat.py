import sys

if len(sys.argv) != 3:
    sys.exit()

filein = sys.argv[1]
fileout = sys.argv[2]

fin = open(filein, "r", encoding="utf-8")
testo = fin.read()
fin.close()

testo_modificato = ""
for carattere in testo:
    if ord(carattere) < 128:
        testo_modificato += carattere
    else:
        testo_modificato += "?"

fout = open(fileout, "w", encoding="utf-8")
fout.write(testo_modificato)
fout.close()