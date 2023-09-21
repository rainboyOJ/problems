#!/bin/env bash
# preview_pid
sh_dir="$(dirname "$(readlink -f "$0")")"
# cat $sh_dir/../all_problme_info.txt | fzf --layout reverse --preview='source $sh_dir/preview_pid.sh;bash -c "preview_pid {}"'
cat $sh_dir/../all_problme_info.txt | fzf --layout reverse --preview='preview_pid.sh {}'
