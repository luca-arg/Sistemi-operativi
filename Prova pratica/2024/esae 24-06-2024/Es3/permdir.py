import os
import sys
import stat

def main():
    if len(sys.argv) != 2:
        sys.exit(1)

    target_dir = sys.argv[1]

    if not os.path.isdir(target_dir):
        sys.exit(1)

    target_dir_abs = os.path.realpath(target_dir)

    try:
        entries = os.listdir(target_dir)
    except OSError:
        sys.exit(1)

    for entry in entries:
        filepath = os.path.join(target_dir, entry)
        
        try:
            st = os.lstat(filepath)
        except OSError:
            continue

        if stat.S_ISREG(st.st_mode):
            mode_str = stat.filemode(st.st_mode)
            
            if not os.path.exists(mode_str):
                try:
                    os.mkdir(mode_str, 0o755)
                except OSError:
                    continue
            
            symlink_target = os.path.join(target_dir_abs, entry)# link che punta al file originale
            symlink_name = os.path.join(mode_str, entry)# link che punta al file originale all'interno della directory con i permessi come nome
            
            if not os.path.exists(symlink_name):
                try:
                    os.symlink(symlink_target, symlink_name)# link che punta al file originale all'interno della directory con i permessi come nome
                except OSError:
                    pass

if __name__ == "__main__":
    main()