import sys
import os

def sort_files_by_depth(search_dir):
    if not os.path.isdir(search_dir):
        return

    files_data = []

    for root, _, files in os.walk(search_dir):
        depth = os.path.abspath(root).count(os.sep)
        for name in files:
            filepath = os.path.join(root, name)
            files_data.append((depth, name, filepath))

    files_data.sort(key=lambda x: (-x[0], x[1]))

    for data in files_data:
        print(data[2])

if len(sys.argv) != 2:
    sys.exit(1)

sort_files_by_depth(sys.argv[1])