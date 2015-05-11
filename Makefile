# Makefile

all:
	g++ -g tree.cc dynarray.cc treetest.cc -Wno-write-strings -g

bench: clean
	g++ -std=c++11 -o bench tree.cc dynarray.cc testbench/random.c testbench/graph.cpp testbench/graphMat.cpp testbench/main.cpp -Wno-write-strings

clean:
	rm -rf bench
	rm -rf a.out
