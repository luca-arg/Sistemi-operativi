import os
import sys

def main():
    uid = os.getuid()
    processes = {}

    try:
        entries = os.listdir('/proc')
    except OSError:
        sys.exit(1)

    for entry in entries:
        if not entry.isdigit():
            continue

        proc_dir = os.path.join('/proc', entry)
        
        try:
            st = os.stat(proc_dir)
            if st.st_uid != uid:
                continue

            exe_path = os.readlink(os.path.join(proc_dir, 'exe'))
            
            if exe_path not in processes:
                processes[exe_path] = []
            
            processes[exe_path].append(entry)
            
        except OSError:
            continue

    for exe, pids in processes.items():
        print(f"{exe} {' '.join(pids)}")

main()