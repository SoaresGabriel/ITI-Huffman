CC = g++
CFLAGS = -c -O3 -std=c++11

all: huffman.o
	$(CC) -o huffman huffman.o HuffmanReader.o HuffmanWriter.o Node.o HuffmanTree.o
	rm -f *.o

huffman.o: main.cpp HuffmanReader.o HuffmanWriter.o Node.o HuffmanTree.o  
	$(CC) $(CFLAGS) main.cpp -o huffman.o 
	
Node.o: Node.h Node.cpp 
	$(CC) $(CFLAGS) Node.cpp -o Node.o
	
HuffmanTree.o: HuffmanTree.h HuffmanTree.cpp 
	$(CC) $(CFLAGS) HuffmanTree.cpp -o HuffmanTree.o
	
HuffmanReader.o: HuffmanReader.h HuffmanReader.cpp 
	$(CC) $(CFLAGS) HuffmanReader.cpp -o HuffmanReader.o

HuffmanWriter.o: HuffmanWriter.h HuffmanWriter.cpp 
	$(CC) $(CFLAGS) HuffmanWriter.cpp -o HuffmanWriter.o

clean:
	rm -f *.o huffman
