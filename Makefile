all : hencode hdecode

hencode: hencode.o heap.o hnode.o
	g++ -o hencode hencode.o heap.o hnode.o

hdecode: hdecode.o hnode.o
	g++ -o hdecode hdecode.o hnode.o

hencode.o: hencode.cc heap.h hnode.h
	g++ -c hencode.cc

hdecode.o: hdecode.cc hnode.h
	g++ -c hdecode.cc

heap.o: heap.cc heap.h hnode.h
	g++ -c heap.cc

hnode.o: hnode.cc hnode.h
	g++ -c hnode.cc
