// hnode.h
// Chris Lepre
// December 10, 2012

#include <cstdlib>

struct Hnode {
  char data;
  size_t count;
  Hnode *left, *right;
  Hnode(char data, size_t count, Hnode *left, Hnode *right);
};

typedef Hnode * Hnodep;
bool isLessThan(const Hnodep & p1, const Hnodep & p2);
