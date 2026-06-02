import sys
import os

def scan(path, depth, max_d, res):
    if max_d is not None and depth > max_d:
        return
    try:
        for item in os.listdir(path):
            p = os.path.join(path, item)
            try:
                ino = os.lstat(p).st_ino
                dp = p[2:] if p.startswith("./") else p # Remove the leading "./" for cleaner output

                res.append((ino, dp))
                if os.path.isdir(p) and not os.path.islink(p):
                    scan(p, depth + 1, max_d, res)
            except OSError:
                continue
    except OSError:
        pass

max_d = 2
if len(sys.argv) > 2 or int(sys.argv[1]) > 2:
    print("Usage: inotab [max_depth=2]")
    sys.exit(1)
if len(sys.argv) == 2:
    try:
        max_d = int(sys.argv[1])
    except ValueError:
        pass

res = []
scan(".", 0, max_d, res)
res.sort(key=lambda x: x[0])

for i, p in res:
    print(f"{i} {p}")