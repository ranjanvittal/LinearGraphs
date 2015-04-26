# Makefile

all:
	g++ -g tree.cc dynarray.cc treetest.cc -Wno-write-strings -g

clean:
	rm -rf *.o
	rm -rf a.out
