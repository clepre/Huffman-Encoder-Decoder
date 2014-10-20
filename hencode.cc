// hencode.cc
// Chris Lepre
// November 16, 2012

#include "heap.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>

using namespace std;

size_t Counts[256]; // The number of occurrences of each character
string Codes[256]; // The location in the tree of each character

void usage()
{
  // Explains how the program is to be run
  cout << "USAGE: hencode FILENAME" << endl;
  exit(1);
}

void init()
{
  // Initialize the Codes and Counts arrays for all 255 characters
  for (size_t i = 0; i < 256; i++) {
    Counts[i] = 0;
    Codes[i] = "";
  }
}

void rliot(Hnode *tree, size_t depth)
{
  // Output the tree from right to left
  // *'s indicate internal nodes
  if (!tree) return;
  rliot(tree->right, depth + 1);
  for (size_t i = 0; i < depth; i++)
    cout << "  ";
  if (tree->data) cout << tree->data;
  else cout << '*';
  cout << endl;
  rliot(tree->left, depth + 1);
}

void prependAll(char digit, Hnode * tree)
{
  // Prepends a digit (0 or 1) to the code of every leaf in the tree
  if (not tree->left)
    Codes[(unsigned char)tree->data] = digit + \
      Codes[(unsigned char)tree->data];
  else {
    prependAll(digit, tree->left);
    prependAll(digit, tree->right);
  }
}

void writeTree(Hnode * tree, ostream & ostr)
{
  // Encodes the tree, with I's indicating internal nodes and L's preceding 
  // leaves. 
  assert(tree); // Tree must not be NULL
  if (not tree->left)
    ostr << 'L' << tree->data;
  else {
    ostr << 'I';
    writeTree(tree->left, ostr);
    writeTree(tree->right, ostr);
  }
}

unsigned char bitstring2uchar(string s)
{
  // Takes a bitstring of length 8 and returns the equivalent 
  // unsigned character
  assert(s.length() == 8);
  unsigned char num = 0;
  int i = 0;
  unsigned char val;
  for (i = 0, val = 128 ; i < 8 ; i++, val /= 2)
    num += (s[i] - '0') * val;
  return num;
}

int main(int argc, char **argv)
{
  if (argc != 2) // Exactly 2 arguments are needed
    usage();
  string fname = argv[1]; // File name will be the second argument
  if (fname == "hencode.cc") 
    usage();
  ifstream file(fname.c_str()); // Create the input stream
  char c;
  size_t numChars = 0; // Initialize total numnber of input characters
  
  // Initialize the Codes and Counts arrays
  init(); 

  // Update the Counts arrays using the input stream,  
  // keep track of the total number of characters
  while (1) {
    file.get(c);
    if (not file)
      break;
    Counts[(unsigned char)c]++;
    numChars++;
  }
  file.close(); // Close the input stream
  
  // Create a heap and populate it with Hnodes of count greater than 0
  Heap minHeap = Heap();
  for (size_t i = 0; i < 256; i++)
    if (Counts[i])
      minHeap.add(new Hnode((char)i, Counts[i], NULL, NULL));
  
  // Construct the tree from the leaves up to the root using
  // the min heap
  while (minHeap.length() > 1) {
    Hnode *left = minHeap.remove(); // smallest
    prependAll('0', left);
    Hnode *right = minHeap.remove(); // second smallest
    prependAll('1', right);
    minHeap.add(new Hnode(0, left->count + right->count, left, right));
  }
  Hnode * tree = minHeap.remove(); // Pointer to the whole tree

  // Add the number of characters to the output stream
  string outfile = fname + ".huf";
  ofstream code(outfile.c_str());
  code << numChars;

  // Add the encoded tree to the output stream 
  writeTree(tree, code);

  // Encode the bitstrings of the file input
  file.open(fname.c_str());
  string bitstring = "";
  while (1) {
    file.get(c);
    if (not file)
      break;
    bitstring += Codes[(unsigned char)c];
    while (bitstring.length() >= 8) {
      code << bitstring2uchar(bitstring.substr(0, 8)); 
      bitstring = bitstring.substr(8);
    }
  }

  // If there are still characters remaining in the bitstring,
  // (but less than 8), we must fill the remaining spaces with a '0' to 
  // have a bitstring of length 8
  if (bitstring.length() > 0) {
    while (bitstring.length() < 8)
      bitstring += '0';
    code << bitstring2uchar(bitstring);
  }
  file.close(); // Close the input stream
  remove(fname.c_str()); // Remove the original file
  return 0;
}


