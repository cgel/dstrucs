#ifndef __HEAP_H
#define __HEAP_H
#define STD_BUFFER 10

template <class T> struct Greater {
  bool operator()(const T &lhs, const T &rhs) { return lhs > rhs; }
};

template <class T> struct Smaller {
  bool operator()(const T &lhs, const T &rhs) { return lhs < rhs; }
};

// compare(parent,child) is allways true
template <class T, class Compare = Greater<T> > class Heap {
private:
  typedef T *iterator;
  T *buff;   // a pointer to the first object
  int _empty; // the index of the first free object
  int _last;  // the index of one passed the last object

  int capacity();
  void reallocate();
  inline int freeSpace();
  void swap(int, int);

  void bubbleDown(int k);
  void bubbleUp(int k);
  Compare comp;

public:
  Heap();
  ~Heap();

  T &top();
  void pop();
  void insert(T);
  int size();
#ifdef __PC
  void print();
#endif
};

template <class T, class Compare> Heap<T, Compare>::Heap() {
  buff = new T[STD_BUFFER];
  _empty = 0;
  _last = STD_BUFFER;
}

template <class T, class Compare> Heap<T, Compare>::~Heap() { delete[] buff; }

template <class T, class Compare> inline int Heap<T, Compare>::freeSpace() {
  return _last - _empty;
}

template <class T, class Compare> void Heap<T, Compare>::reallocate() {
  int s = size();
  int newSize = s * 2;
  T *newBuff = new T[newSize];
  for (int i = 0; i != s; i++) {
    newBuff[i] = buff[i];
  }
  delete[] buff;
  buff = newBuff;
  _empty = s;
  _last = newSize;
}

template <class T, class Compare> void Heap<T, Compare>::swap(int i, int j) {
  T temp = buff[i];
  buff[i] = buff[j];
  buff[j] = temp;
}

template <class T, class Compare> void Heap<T, Compare>::bubbleDown(int index) {
  int left_child = index * 2 + 1, right_child = left_child + 1;
  // it is possible that some of the child indexes are constructed or outside the buffer range 
  bool bubble_left = left_child < _empty;
  bool bubble_right = right_child < _empty;
  if (bubble_left && bubble_right) {
    if (comp(buff[left_child], buff[right_child])) // left child is greater
    {
      swap(index, left_child);
      bubbleDown(left_child);
    } else if (comp(buff[right_child], buff[left_child])){ // left child is greater
      swap(index, right_child);
      bubbleDown(right_child);
    }
  } else if (bubble_left) {
    if (comp(buff[left_child], buff[index])) // left child is greater
    {
      swap(index, left_child);
      bubbleDown(left_child);
    }
  }
  return;
}

template <class T, class Compare> void Heap<T, Compare>::bubbleUp(int index) {
  int parent_index = (index - 1) / 2; 
  if (index == 0 || comp(buff[parent_index], buff[index])) {
    return;
  }
  swap(index, parent_index);
  bubbleUp(parent_index);
  return;
}

template <class T, class Compare> void Heap<T, Compare>::pop() {
  if (_empty != 0) {
    --_empty;
    buff[0] = buff[_empty];
    bubbleDown(0);
  }
  return;
}

template <class T, class Compare> void Heap<T, Compare>::insert(T new_key) {
  if (freeSpace() == 0) {
    reallocate(); 
  }
  buff[_empty] = new_key;
  bubbleUp(_empty);
  _empty++;
}

template <class T, class Compare> T &Heap<T, Compare>::top() { return *buff; }

template <class T, class Compare> int Heap<T, Compare>::size() { return _empty; }

#ifdef __PC
template <class T, class Compare> void Heap<T, Compare>::print() {
  for (int i = 0; i != _empty; i++)
    std::cout << " " << buff[i];

  std::cout << std::endl;
}
#endif

#endif
