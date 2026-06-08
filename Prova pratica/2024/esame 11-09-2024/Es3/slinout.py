import sys
import os

def slinout(base_dir):
    base_dir_abs = os.path.abspath(base_dir)
    interni = []
    esterni = []

    for root, dirs, files in os.walk(base_dir):
        root_abs = os.path.abspath(root)
        for name in files + dirs:
            filepath = os.path.join(root, name)

            if os.path.islink(filepath):
                target_abs = os.path.realpath(filepath)
                
                if os.path.commonpath([base_dir_abs, target_abs]) == base_dir_abs:
                    interni.append(filepath)
                else:
                    esterni.append(filepath)

    print("--- Link Interni ---")
    for link in interni:
        print(link)

    print("\n--- Link Esterni ---")
    for link in esterni:
        print(link)



if len(sys.argv) > 1:
    start_dir = sys.argv[1]
else:
    start_dir = os.getcwd()

slinout(start_dir)