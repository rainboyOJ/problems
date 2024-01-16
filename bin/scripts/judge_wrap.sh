# need source
#

sh_dir="$(dirname "$(readlink -f "$0")")"
echo $sh_dir
sjudge=$(readlink -f "$sh_dir/../sjudge/sjudge.out")
echo $sjudge

# 创建一个评测的函数
# 参数
# $1 评测的程序
# $2 memory
# $3 time
# $4 input file
# $5 output file
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
