// hnode.cc
// Chris Lepre
// December 10, 2012

#include "hnode.h"

Hnode::Hnode(char data, size_t count, Hnode *left, Hnode *right) :
  data(data), count(count), left(left), right(right) {}

bool isLessThan(const Hnodep & p1, const Hnodep & p2) 
{
  return p1->count < p2->count;
}


