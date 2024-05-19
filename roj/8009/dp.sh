#!/bin/bash

for i in {1..100}; do
	printf "\r$i"
	./data.out >in # 数据生成
	./baoli.out <in >out1
	./std.out <in >out2
	diff out1 out2 || exit 1
done
