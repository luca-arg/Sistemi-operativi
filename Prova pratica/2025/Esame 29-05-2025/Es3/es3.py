#!/usr/bin/env python3
import sys
import os

def find_hard_links(target, directory):
    target_ino = os.stat(target).st_ino
    target_dev = os.stat(target).st_dev
    
    for entry in os.listdir(directory):
        filepath = os.path.join(directory, entry)
        
        if not os.path.islink(filepath):
            if os.stat(filepath).st_ino == target_ino and os.stat(filepath).st_dev == target_dev:
                print(filepath)

def find_symlinks(target, directory):
    real_target = os.path.realpath(target)
    
    for entry in os.listdir(directory):
        filepath = os.path.join(directory, entry)
        
        if os.path.islink(filepath):
            if os.path.realpath(filepath) == real_target:
                print(filepath)

def main():
    if len(sys.argv) != 3:
        sys.exit(1)

    prog_name = os.path.basename(sys.argv[0])
    target = sys.argv[1]
    directory = sys.argv[2]

    if prog_name == "cklink":
        find_hard_links(target, directory)
    elif prog_name in "cksymlink":
        find_symlinks(target, directory)

main()