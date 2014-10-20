// hdecode.cc
// Chris Lepre
// November 30, 2012

#include "hnode.h"
#include <iostream>
#include <cassert>
#include <cstdlib>
#include <fstream>

using namespace std;

void createTree(Hnode * & tree, ifstream & fin, char c)
{
  // Creates the tree according to the input stream intructions

  // Read a character
  fin.get(c);

  // If character is an 'I', create an internal node
  if (c == 'I') {
    tree = new Hnode(0, 0, NULL, NULL);
    createTree(tree->left, fin, c);
    createTree(tree->right, fin, c);
    return;
  }

  // If character is an 'L', create a leaf whose data is the next character
  if (c == 'L') {
    fin.get(c);
    tree = new Hnode(c, 0, NULL, NULL); 
    return;
  }
}
    
Hnode * readTree(ifstream & fin)
{
  // Returns a tree created from the input stream instructions
  Hnode *tree = NULL;
  char c;
  createTree(tree, fin, c); // Call helper function to create the tree
  return tree;
}

size_t exp(size_t num, size_t power)
{
  // Computes the power of the indicated number to the indicated exponent
  if (power == 0)
    return 1;
  size_t answer = num;
  for (size_t i = 0; i < power - 1; i++)
    answer *= num;
  return answer;
}

string uchar2bitstring(unsigned char c)
{
  // Takes an unsigned character and returns its equivalent bitstring
  string bit = "";
  for (size_t i = 8; i > 0; i--) {
    if (exp(2, i - 1) <= c) {
      bit += "1";
      c -= exp(2, i - 1);
    }
    else {
      bit += "0";
    }
  }
  return bit;
}

void rliot(Hnode *tree, size_t depth)
{
  // Prints out the tree
  if (!tree) return;
  rliot(tree->right, depth + 1);
  for (size_t i = 0; i < depth; i++)
    cout << "  ";
  if (tree->data) cout << tree->data;
  else cout << '*';
  cout << endl;
  rliot(tree->left, depth + 1);
}

void readMore(ifstream & fin, string & bitstring)
{
  // Reads another character and converts it to a bitstring
  char c;
  fin.get(c);
  bitstring = uchar2bitstring(c);
}

char findDatShit(string & bitstring, Hnode * tree, ifstream & fin)
{
  // Returns the first char found in the tree given a bitstring
  if (tree->left == NULL)
    return tree->data;
  if (bitstring.size() == 0) // In case we run out of bitstring 
    readMore(fin, bitstring);
  char next = bitstring[0];
  bitstring = bitstring.substr(1);
  return findDatShit(bitstring, next=='0'?tree->left:tree->right, fin);
} 

void usage()
{
  // Explains how the program is to be run
  cout << "USAGE: hencode FILENAME" << endl;
  exit(1);
}

int main(int argc, char **argv)
{
  if (argc != 2) // Exactly 2 arguments are needed
    usage();
  string fname = argv[1]; // File name will be the second argument
  ifstream code(fname.c_str());
  size_t numChars; // Will store the number of encoded characters
  code >> numChars;
  Hnode * tree = readTree(code);
  string outfile = fname.substr(0, fname.size() - 4);
  ofstream decoded(outfile.c_str());
  string bitstring;

  // For every character of the original input, use the bitstring to
  // find a character from the tree. If the bitstring is empty,
  // read more encoded input
  for (size_t i = 0; i < numChars; i++) {
    if (bitstring == "")
      readMore(code, bitstring);
    decoded << findDatShit(bitstring, tree, code);   
  }
  code.close();
  remove(fname.c_str());
  return 0;
}
