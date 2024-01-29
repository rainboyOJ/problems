#!/bin/env bash

# TODO 这个id 默认是 roj里，其它的可以写成 luogu/1027
echo "usage: judge.sh roj-problme-id [1.out]"
sh_dir="$(dirname "$(readlink -f "$0")")"
problem_dir=$(readlink -f "$sh_dir/../roj")
source "$sh_dir/scripts/judge_wrap.sh"
# echo $sh_dir
# echo $problem_dir

program=${2:-1.out}
if [[ -z "$1" ]]; then
	echo "please input problem id,like 1000"
	exit 1
fi
pid=$1

# 2.检查路径是否存在
data_dir="$problem_dir/$pid/data"
echo "data_dir: " $data_dir
# 3.得到数据列表
# 3.1 检查数据目录是否存在
in_data=$(find $data_dir -type f -name "*.in" -printf '%f\n')
out_data=$(find $data_dir -type f -name "*.out" -printf '%f\n')

#echo $in_data
# echo $( echo $in_data | xargs -n 1 | sort -n)

oneFileName=$(echo $in_data | cut -d ' ' -f1)
first_num_pos=$(expr index $oneFileName $(grep -oP '\d+' <<<$oneFileName))
echo $a
echo $first_num_pos

# 输出对应的信息

printf "评测程序: %s\n" $program
printf "题目编号: %s\n" $pid

#
#转数组
in_arr=($(echo $in_data | xargs -n 1 | sort -n -k 1.$first_num_pos))
out_arr=($(echo $out_data | xargs -n 1 | sort -n -k 1.$first_num_pos))
count_in=${#in_arr[*]}
count_out=${#out_arr[*]}
printf "size of input: %3d , output %3d \n\n" $count_in $count_out

for ((i = 0; i < $count_in; i++)); do
	input=$problem_dir/$pid/data/${in_arr[i]}
	output=$problem_dir/$pid/data/${out_arr[i]}
	# judge_run 1.out 128 1 $input $output
	ret=$(judge_run $program 128 1 $input $output)
	printf "%2d %10s %10s -> %s\n" $i ${in_arr[i]} ${out_arr[i]} "$ret"
	# echo -en   "\t"
done
#echo $out_data
