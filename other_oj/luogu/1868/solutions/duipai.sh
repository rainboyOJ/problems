#!/bin/bash

for i in {1..100}; do
	printf "\r$i"
	./random.out >in # 数据生成
	./2.out <in >out1
	./baoli.out <in >out2
	diff out1 out2 || exit 1
done
