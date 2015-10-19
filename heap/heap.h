#ifndef __HEAP_H
#define __HEAP_H
#define STD_BUFFER 10

template<class T>
struct Greater{
  bool operator()(const T& lhs, const T& rhs);
};

template<class T, class Compare = Greater<T> >
class Heap {
  typedef T* iterator;
  private:
  T* elem; // a pointer to the first object
  int space; //the index of the first free object
  int last;  // the index of one passed the last object
  
  int capacity();
  void reallocate();
  inline int freeSpace();
  void swap(int, int);

  bool bubbleDown(int&k);
  bool bubbleUp(int&k);
  Compare comp;

  public:
  Heap();
  ~Heap();

  T& top();
  T pop();
  void insert(T);
  void print();
  int size();
};

#endif
