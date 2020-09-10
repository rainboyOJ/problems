g++ mk.cpp -o mk -g
g++ tree.cpp -o tree -g
for /L %%i in (0,1,9) do (
	mk %%i
	tree
	cp tree.in tree%%i.in
	cp tree.out tree%%i.out
)