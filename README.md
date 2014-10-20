Huffman-Encoder-Decoder
=======================

This is a Huffman encoder and decoder, written in C++. It was created for my Data Structures course (CS 111) in the Fall of 2012.
The program uses a Huffman tree to encode text, and then traverses the tree to decode it. 

To run the program, first issue the 'make' command. To encode a file, type './hencode [filename]' in the command line. The file will
be replaced with a new version with the extension '.huf'. To decode the file, type './decode [filename.huf]' in the command line.
The file should appear in the directory under its initial name, and contain exactly the same content as before. 
