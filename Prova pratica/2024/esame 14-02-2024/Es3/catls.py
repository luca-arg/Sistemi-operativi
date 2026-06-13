import os
import sys
import subprocess

def main():
    target_dir = "."
    if len(sys.argv) > 1:
        target_dir = sys.argv[1]

    try:
        entries = os.listdir(target_dir)
    except OSError:
        sys.exit(1)

    catalog = {}

    for entry in entries:
        filepath = os.path.join(target_dir, entry)
        
        try:
            result = subprocess.run(
                ['file', '-b', filepath], 
                capture_output=True, 
                text=True,
                check=True
            )
            file_type = result.stdout.strip()
            
            if file_type not in catalog:
                catalog[file_type] = []
            
            catalog[file_type].append(entry)
            
        except (OSError, subprocess.CalledProcessError):
            continue

    for ftype, files in catalog.items():
        print(f"{ftype}:")
        for f in files:
            print(f"  {f}")

main()