import sys
import os
import subprocess

if len(sys.argv) != 3:
    sys.exit(1)

f = sys.argv[1]
d = sys.argv[2]
abs_f = os.path.abspath(f)

for root, dirs, files in os.walk(d):
    for name in files:
        path = os.path.join(root, name)
        
        if os.path.abspath(path) == abs_f:
            continue
            
        if os.path.isfile(path):
            res = subprocess.run(["cmp", "-s", f, path])# passi il file da confrontare e il file da confrontare con cmp -s, che restituisce 0 se i file sono uguali
            if res.returncode == 0:# se i file sono uguali, cmp restituisce 0
                try:
                    os.remove(path)
                except OSError:
                    pass

