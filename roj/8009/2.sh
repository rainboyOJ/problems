#!/bin/bash

# 进入data文件夹
# cd data

# 使用for循环列出所有的*.in文件
for file in data/*.in; do
	echo $file
	# ./check.out <$file
	./baoli.out <$file >b1
	./std.out <$file >b2
	diff b1 b2 || exit 0
done
echo "done"
