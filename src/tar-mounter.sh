#!/bin/sh

[ $(whereis zenity) = "zenity:" ] && echo "$(basename $0): please install zenity" >&2 && exit 4
[ $# -ne 1 ] && echo "Usage: $(basename $0) <archive>" >&2 && exit 1

dir=$(zenity --file-selection --directory)
if [ $? -ne 0 ] || [ -z "$dir" ]; then exit 2; fi

log=$(fuse_tar "$1" "$dir")
[ $? -ne 0 ] && zenity --error --text="$log" && exit 3

xdg-open "$dir"

