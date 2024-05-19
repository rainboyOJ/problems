#!/bin/bash

# 使用for循环列出所有的*.in文件
for file in data/*.in; do
	./std.out <$file >out
	output_file="${file/.in/.out}"
	# if diff out $output_file -b then;
	if diff -b -q out $output_file; then
		echo "Test case $file passed!"
	else
		echo "Test case $file failed!"
	fi
done
