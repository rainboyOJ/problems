#!/bin/env bash
#
#拷贝对应id的数据到当前上当

sh_dir="$(dirname "$(readlink -f "$0")")"
problem_dir=$(readlink -f "$sh_dir/../problems")
printf "$problem_dir"

if [[ -z "$1" ]];then
    printf "usage : copy_data.sh [id]\n"
fi

cp -r "$problem_dir/$1/data" .
