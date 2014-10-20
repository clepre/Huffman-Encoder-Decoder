// heap.cc
// Chris Lepre
// December 10, 2012

#include "heap.h"

size_t parent(size_t k)
{
  // Return the index of the parent in the heap
  return (k - 1)/2;
}

size_t leftChild(size_t k)
{
  // Return the index of the left child in the heap
  return 2*k + 1;
}

size_t rightChild(size_t k)
{
  // Return the index of the right child in the heap
  return 2*k + 2;
}

void swap(Hnodep & a, Hnodep & b)
{
  // Swap the values of two node pointers
  Hnodep temp = a;
  a = b;
  b = temp;
}

Heap::Heap() 
{
  // Construct an initially empty heap
  MAX = 256;
  data = new Hnodep[MAX];
  size = 0;
} 

Heap::~Heap()
{
  // Deconstruct the heap
  delete [] data;
}

void Heap::_reheap_up(size_t current)
{
  // After adding an element to the end of the heap, move it to its
  // proper location
  while (current != 0 and isLessThan(data[current], data[parent(current)])) {
    swap(data[current], data[parent(current)]);
    current = parent(current);
  }
}

void Heap::_reheap_down(size_t current)
{
  // After removing the indicated element of the heap and replacing it 
  // with the last element, move the newly placed element to its proper 
  // location
  if (leftChild(current) >= size)
    return;
  size_t child = leftChild(current);
  if (rightChild(current) < size and isLessThan(data[rightChild(current)], 
						data[child]))
    child = rightChild(current);
  if (isLessThan(data[child], data[current])) {
    swap(data[current], data[child]);
    _reheap_down(child);
  }
}

void Heap::add(const Hnodep & item) 
{
  // Add an element to the heap
  data[size] = item;
  _reheap_up(size);
  size++;
}

Hnodep Heap::remove()
{
  // Remove and return the first element of the heap
  Hnodep answer = data[0];
  data[0] = data[size - 1];
  size--;
  _reheap_down(0);
  return answer;
}

size_t Heap::length()
{
  // Return the length (size) of the heap
  return size;
}
