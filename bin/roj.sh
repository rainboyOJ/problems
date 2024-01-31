#!/bin/bash

# roj.ac.cn oj网站的评测脚本
## 使用
# roj 题号
# 例如 roj 1000
## 过程
## 1.下载数据
## 2.编译程序
## 3.评测

################### 评测函数

# 创建一个评测的函数
# 参数
# $1 评测的程序
# $2 memory
# $3 time
# $4 input file
# $5 output file
sjudge="/usr/bin/sjudge"
judge_run() {
	res=$($sjudge \
		--max-cpu-time $3 \
		--max-real-time $(expr $3 + 1) \
		--max-memory $2 \
		--exe $1 \
		--input $4 \
		--output /tmp/sjudge.out \
		--error err.txt \
		--args ls \
		--args -l \
		--env foo=bar \
		--log log.txt)
	ret=""
	result=$(echo $res | jq .result)
	# echo "result" $result
	case $result in
	1 | 2)
		ret+='TLE'
		;;
	3)
		ret+='MLE'
		;;
	4)
		ret+='RE'
		;;
	5)
		ret+='SE'
		;;
	esac
	# echo "ret" $ret

	if (($result == 0)); then
		if /usr/bin/diff -q -b -B /tmp/sjudge.out $5 >/dev/null; then
			# if /usr/bin/diff -b /tmp/sjudge.out $5 ; then
			ret+="✅"
		else
			ret+="❌"
		fi
	elif (($result > 5)); then
		ret+="Other error: "
		ret+="$result"
	fi

	# add time
	time="$(echo $res | jq .cpu_time)"
	# add memory
	mem_kb="$(echo $res | jq .memory)"
	mem_mb=$(echo "scale=2; $mem_kb / 1024" | bc)
	printf "%3s | time :%4s ms | mem: %7s mb" $ret $time $mem_mb

	#
	# result=$(echo $res | jq .result)
	# if (( resul != 0 ));then
	#     let ret+="FAIL"
	# else
	#     let ret+="SUCC"
	# fi
	#
	# echo $ret
}

# 查找名字含有相同字符串的文件
#
function find_file {
	local find_str
	find_str=$1
	shift 1
	local FZF_OPTIONS="--no-sort --layout=reverse --height 40% --border --margin=0,1"
	local files
	files="$(find . -type f -maxdepth 1 -name "$find_str" -printf "%f\n")"
	if [ -z "$files" ]; then
		echo ""
	else
		echo "$files" | sort -f -i -t '.' -k 1 | fzf $* $FZF_OPTIONS
	fi
}
#########################

## 0. 获取参数
if [[ -z "$1" ]]; then
	echo "please input problem pid ,like 1000"
	exit 1
fi

## 全局变量

pid="$1"   #题号
program="" # 评测程序
roj_url="http://data.roj.ac.cn/"
roj_data_url="${roj_url}${pid}"
data_dir="data"

if [[ -n "$2" ]]; then
	program="$2"
fi

## 1. 编译

### 没有源文件的情况
if [ -z "$program" ]; then
	# program=$(find_file "*.out" "-1") # -1 自动选择一个元素,如果只有一个
	FZF_OPTIONS="--no-sort --layout=reverse --height 40% --border --margin=0,1 -1"
	files="$(find .  -maxdepth 1 -type f \( -name "*.cpp" -o -name "*.out" \) -printf "%f\n")"
	if [ -z "$files" ]; then
		echo "当前没有任何.out或.cpp文件"
		exit 0
	else
		program=$(echo "$files" | sort -f -i -t '.' -k 1 | fzf $FZF_OPTIONS)
	fi
fi

if [[ "$program" == *".cpp" ]];then
	out="${program%.cpp}.out"
	echo $program
	echo $out
	g++ -g -o $out $program
	if [[ $? -ne 0 ]] ;then
		echo "编译失败!!"
		exit 1
	fi
	program=$out
fi

## 2. 下载数据

function download_data {
	wget -O tmp.zip "$roj_data_url"
	unzip -q -d data tmp.zip
	/usr/bin/rm tmp.zip
}

if [[ -d $data_dir ]]; then
	read -r -p "$data_dir 已经存在,是否删除,然后重新下载数据?(y/N)" delete_data_dir
	if [[ $delete_data_dir == "y" ]] || [[ $delete_data_dir == "Y" ]]; then
		rm -rf $data_dir
		download_data
	fi
else
	download_data
fi

in_data=$(find $data_dir -type f -name "*.in" -printf '%f\n')
out_data=$(find $data_dir -type f \( -name "*.out" -o -name "*.ans" \) -printf '%f\n')
oneFileName=$(echo $in_data | cut -d ' ' -f1)
first_num_pos=$(expr index $oneFileName $(grep -oP '\d+' <<<$oneFileName))
#转数组
in_arr=($(echo $in_data | xargs -n 1 | sort -n -k 1.$first_num_pos))
out_arr=($(echo $out_data | xargs -n 1 | sort -n -k 1.$first_num_pos))
count_in=${#in_arr[*]}
count_out=${#out_arr[*]}


## 3. 评测
for ((i = 0; i < $count_in; i++)); do
	input=$data_dir/${in_arr[i]}
	output=$data_dir/${out_arr[i]}
	# judge_run 1.out 128 1 $input $output
	ret=$(judge_run $program 128 1 $input $output)
	printf "%2d %10s %10s -> %s\n" $i ${in_arr[i]} ${out_arr[i]} "$ret"
	# echo -en   "\t"
done
