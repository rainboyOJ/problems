#!/bin/bash
g++ -g -std=c++20 -o data.out data.cpp
g++ -g -std=c++20 -o std.out std.cpp
mkdir -p data
./data.out 5 1 10 >data/p1.in
./data.out 6 -20 20 >data/p2.in
./data.out 7 -100 100 >data/p3.in
./data.out 8 -500 500 >data/p4.in
./data.out 100 -500 500 >data/p5.in
./data.out 1000 -5000 5000 >data/p6.in
./data.out 10000 -5000 5000 >data/p7.in
./data.out 100000 -5000 5000 >data/p8.in
./data.out 100000 -50000 50000 >data/p9.in
./data.out 100000 -50000 50000 >data/p10.in

for i in {1..10}; do
	echo $i
	./std.out <data/p$i.in >data/p$i.out
done
/usr/bin/rm -rf data.out
/usr/bin/rm -rf std.out
