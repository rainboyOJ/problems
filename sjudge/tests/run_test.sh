#!/bin/env bash
make

cur=`pwd`


# 1. test normal
echo ">>> 1. test normal"
echo 
res=$(../sjudge.out --max-cpu-time 1 \
    --max-real-time 2\
    --max-memory 128\
    --max-stack 512\
    --cwd "$cur"\
    --exe "$cur/normal.out" \
    --input "io_file/normal.in" \
    --output "normal_out" \
    --error normal_err\
    --args normal.out\
    --env foo=bar\
    --log normal_log.txt | cat)

# 是否执行成功
if [[ "$(echo $res | jq .result)" != "0" ]]; then
    echo "res.result not 0!"
    echo $res
    exit 1
fi

if ! /usr/bin/diff ./io_file/normal.out normal_out ;then
    echo "normal.c output file not same!"
    exit 1
fi

