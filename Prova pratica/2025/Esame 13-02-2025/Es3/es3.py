#!/usr/bin/env python3
import sys
import os

def check_size_and_links(target_path, search_dir):
    if not os.path.exists(target_path) or not os.path.isdir(search_dir):
        return
    try:
      t_stat = os.stat(target_path)
    except OSError:
        return

    t_size = t_stat.st_size
    t_ino = t_stat.st_ino
    t_dev = t_stat.st_dev

    for root, dirs, files in os.walk(search_dir):
        for name in files:
            filepath = os.path.join(root, name)
            
            f_stat = os.stat(filepath)
                
            if f_stat.st_size == t_size:
                if not (f_stat.st_ino == t_ino and f_stat.st_dev == t_dev):
                    print(filepath)


if len(sys.argv) != 3:
        sys.exit(1)
    
check_size_and_links(sys.argv[1], sys.argv[2])