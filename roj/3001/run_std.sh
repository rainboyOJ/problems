#!/bin/bash

for i in {1..5}; do
	./std.out <data/mul$i.in >data/mul$i.out
done
