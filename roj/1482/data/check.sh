#!/bin/bash
g++ check.cc -o check
for k in {1..10}
do
	./check < word$k.in
done
