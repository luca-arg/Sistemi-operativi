import os
import sys

def main():
    target_dir = "..."
    
    try:
        if not os.path.exists(target_dir):
            os.mkdir(target_dir, 0o700)
    except OSError:
        sys.exit(1)

    try:
        entries = os.listdir('.')
    except OSError:
        sys.exit(1)

    for entry in entries:
        if entry in ('.', '..', target_dir):
            continue

        if os.path.islink(entry) or not os.path.isfile(entry):
            continue

        target_path = os.path.join(target_dir, entry)
        tmp_link = f"{entry}.tmp"
        symlink_target = os.path.join(target_dir, entry)

        try:
            os.link(entry, target_path)
        except OSError:
            continue

        try:
            os.symlink(symlink_target, tmp_link)
        except OSError:
            os.unlink(target_path)
            continue

        try:
            os.replace(tmp_link, entry)
        except OSError:
            os.unlink(target_path)
            if os.path.exists(tmp_link):
                os.unlink(tmp_link)

main()