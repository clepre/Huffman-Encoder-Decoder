// heap.h
// Chris Lepre
// December 10, 2012

#include "hnode.h"

class Heap {
 public:
  Heap();
  ~Heap();
  void add(const Hnodep & item);
  Hnodep remove();
  size_t length();

 private:
  void _reheap_up(size_t current);
  void _reheap_down(size_t current);
  size_t MAX;
  Hnodep *data;
  size_t size;
};
