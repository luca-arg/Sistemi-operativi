import os
import sys

testo_da_aggiungere = "Esame di Sistemi Operativi\nModifica automatica dello script"

for filename in os.listdir('.'):
    if not os.path.isfile(filename):
        continue
    if filename == os.path.basename(sys.argv[0]):
        continue

    if filename.endswith('.c'):
        with open(filename, 'r') as f:
            content = f.read()
        with open(filename, 'w') as f:
            f.write(f"/*\n{testo_da_aggiungere}\n*/\n{content}")

    elif filename.endswith('.py'):
        with open(filename, 'r') as f:
            content = f.read()
        with open(filename, 'w') as f:
            f.write(f"'''\n{testo_da_aggiungere}\n'''\n{content}")


    elif filename.endswith('.sh'):
        with open(filename, 'r') as f:
            lines = f.readlines()
        
        # 1. Costruiamo il commento passo passo con un ciclo for standard
        testo_commentato = ""
        righe_testo = testo_da_aggiungere.split('\n') 
        
        for riga in righe_testo:
            testo_commentato += "# " + riga + "\n"
            
        testo_commentato += "\n" # Un ultimo invio per staccarlo dal codice
        
        # 2. Controllo dello shebang e inserimento
        if len(lines) > 0 and lines[0].startswith('#!'):
            if not lines[0].endswith('\n'):
                lines[0] += '\n' 
            lines.insert(1, testo_commentato)    
        else:
            lines.insert(0, testo_commentato)
            
        # 3. Scrittura su file
        with open(filename, 'w') as f:
            f.writelines(lines)