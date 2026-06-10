import sys
import os
import hashlib

def get_sha1(filepath):
    h = hashlib.sha1()
    try:
        with open(filepath, 'rb') as f:
            while chunk := f.read(8192):
                h.update(chunk)
    except OSError:
        return None
    return h.hexdigest()


def scan_directory(base_dir):
    hash_map = {}
    for root, _, files in os.walk(base_dir):
        for name in files:
            filepath = os.path.join(root, name)
            if os.path.isfile(filepath) and not os.path.islink(filepath):
                file_hash = get_sha1(filepath)
                if file_hash:
                    if file_hash not in hash_map:
                        hash_map[file_hash] = []
                    hash_map[file_hash].append(filepath)
    return hash_map



if len(sys.argv) != 3:
    sys.exit(1)

dir1 = sys.argv[1]
dir2 = sys.argv[2]

if not os.path.isdir(dir1) or not os.path.isdir(dir2):
    sys.exit(1)

map1 = scan_directory(dir1)
map2 = scan_directory(dir2)

common_hashes = set(map1.keys()).intersection(set(map2.keys()))

for h in common_hashes:
    for filepath in map1[h]:
        try:
            os.remove(filepath)
        except OSError:
            pass
            
    for filepath in map2[h]:
        try:
            os.remove(filepath)
        except OSError:
            pass