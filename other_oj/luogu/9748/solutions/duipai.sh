for i in {1..100}; do
	echo $i
	echo $i | ./baoli.out >out1
	echo $i | ./3.out >out2
	diff out1 out2 || exit 0
done
