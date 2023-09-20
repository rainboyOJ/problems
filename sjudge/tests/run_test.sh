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
echo "OK"


# 2. test args
echo ">>> 2. test args"
echo 
res=$(../sjudge.out --max-cpu-time 1 \
    --max-real-time 2\
    --max-memory 128\
    --max-stack 512\
    --cwd "$cur"\
    --exe "$cur/args.out" \
    --output "args_out" \
    --error args_err\
    --args args.out \
    --args test \
    --args hehe \
    --args 000 \
    --env foo=bar\
    --log args_log.txt | cat)
# 是否执行成功
if [[ "$(echo $res | jq .result)" != "0" ]]; then
    echo "res.result not 0!"
    echo $res
    exit 1
fi

if ! /usr/bin/diff ./io_file/args.out args_out ;then
    echo "args.c output file not same!"
    exit 1
fi

echo "OK"

echo ">>> 3. test env"
echo "TODO"

echo ">>> 4. test real time"
echo "TODO"

echo ">>> 5. test cpu time"
res=$(../sjudge.out --max-cpu-time 1 \
    --max-real-time 2\
    --max-memory 80\
    --max-stack 512\
    --cwd "$cur"\
    --exe "$cur/while1.out" \
    --output "while1_out" \
    --error while1_err\
    --args while1.out \
    --log while1_log.txt | cat)
# 是否执行成功
if [[ "$(echo $res | jq .result)" != "1" ]]; then
    echo "res.result should is 1!"
    echo $res
    exit 1
fi

if [[ "$(echo $res | jq .signal)" != "9" ]]; then
    echo "error"
    echo $res
    exit 1
fi
echo "OK"

echo ">>> 6. test memory1"
res=$(../sjudge.out --max-cpu-time 1 \
    --max-real-time 2\
    --max-memory 80\
    --max-stack 512\
    --cwd "$cur"\
    --exe "$cur/memory1.out" \
    --output "memory1_out" \
    --error memory1_err\
    --args memory1.out \
    --log memory1_log.txt | cat)
# 是否执行成功
if [[ "$(echo $res | jq .result)" != "3" ]]; then
    echo "res.result not 3,MEMORY_LIMIT_ERROR!"
    echo $res
    exit 1
fi

if (( $(echo $res | jq .memory) < 80*1024 )); then
    echo "res.memory not greater 80mb !"
    echo $res
    exit 1
fi

echo "OK"

echo ">>> 7. test memory2"
res=$(../sjudge.out --max-cpu-time 1 \
    --max-real-time 2\
    --max-memory 64\
    --max-stack 512\
    --cwd "$cur"\
    --exe "$cur/memory2.out" \
    --output "memory2_out" \
    --error memory2_err\
    --args memory2.out \
    --log memory2_log.txt | cat)
# 是否执行成功
if [[ "$(echo $res | jq .exit_code)" != "1" ]]; then
    echo "res.exit_code should 1!"
    exit 1
fi

if [[ "$(echo $res | jq .result)" != "5" ]]; then
    echo "res.result should 5!"
    exit 1
fi

if (( $(echo $res | jq .memory) >= 12*1024 )); then
    echo "error memory size!"
    echo $res
    exit 1
fi


echo "OK"

echo ">>> 8. test memory3"
res=$(../sjudge.out --max-cpu-time 1 \
    --max-real-time 2\
    --max-memory 512\
    --max-stack 512\
    --cwd "$cur"\
    --exe "$cur/memory3.out" \
    --output "memory3_out" \
    --error memory3_err\
    --args memory3.out \
    --log memory3_log.txt | cat)
# 是否执行成功

if [[ "$(echo $res | jq .result)" != "0" ]]; then
    echo "res.result should 0!"
    exit 1
fi

if !(( $(echo $res | jq .memory) >= 102400000 * 4 / 1024 )); then
    echo "error memory size!"
    echo $res
    exit 1
fi

echo "OK"

echo ">>> 9. test memory4"
echo "TODO"

echo ">>> 10. test re1"
res=$(../sjudge.out --max-cpu-time 1 \
    --max-real-time 2\
    --max-memory 512\
    --max-stack 512\
    --cwd "$cur"\
    --exe "$cur/re1.out" \
    --output "re1_out" \
    --error re1_err\
    --args re1.out \
    --log re1_log.txt | cat)

if [[ "$(echo $res | jq .exit_code)" != "25" ]]; then
    echo "res.exit_code should 25!"
    echo $res
    exit 1
fi

echo "OK"


echo ">>> 11. test re2"
res=$(../sjudge.out --max-cpu-time 1 \
    --max-real-time 2 \
    --max-memory 512 \
    --max-stack 512 \
    --cwd "$cur" \
    --exe "$cur/re2.out" \
    --output "re2_out" \
    --error re2_err \
    --args re2.out \
    --log re2_log.txt | cat)

if [[ "$(echo $res | jq .signal)" != "11" ]]; then
    echo "res.signal should 11!"
    echo $res
    exit 1
fi

echo "OK"
