#!/bin/bash
javac -encoding UTF-8 -sourcepath . -d . Main.java
for k in {1..10}
do
	echo $k...
	time java -client -Xss8m -Xmx2048m Main < word$k.in > word$k.out
done
