#!/bin/env bash
sh_dir="$(dirname "$(readlink -f "$0")")"
pid=$(echo "$1" | cut -d " " -f1)
path="$sh_dir/../problems/$pid/content.md"
# echo $path
if command -v mdcat > /dev/null;then
    mdcat $path
elif command -v bat > /dev/null;then
    bat --color=always $path
elif command -v cat> /dev/null;then
    cat $path
else
    echo "please install cat or bat or mdcat command"
fi
