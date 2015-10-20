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
  T *elem;   // a pointer to the first object
  int space; // the index of the first free object
  int last;  // the index of one passed the last object

  int capacity();
  void reallocate();
  inline int freeSpace();
  void swap(int, int);

  bool bubbleDown(int &k);
  void bubbleUp(int k);
  Compare comp;

public:
  Heap();
  ~Heap();

  T &top();
  void pop();
  void insert(T);
#ifdef __PC
  void print();
#endif
  int size();
};

template <class T, class Compare> Heap<T, Compare>::Heap() {
  elem = new T[STD_BUFFER];
  space = 0;
  last = STD_BUFFER;
}

template <class T, class Compare> Heap<T, Compare>::~Heap() { delete[] elem; }

template <class T, class Compare> inline int Heap<T, Compare>::freeSpace() {
  return last - space;
}

template <class T, class Compare> void Heap<T, Compare>::reallocate() {
  int s = size();
  int newSize = s * 2;
  T *newElem = new T[newSize];
  for (int i = 0; i != s; i++) {
    newElem[i] = elem[i];
  }
  delete[] elem;
  elem = newElem;
  space = s;
  last = newSize;
}

template <class T, class Compare> void Heap<T, Compare>::swap(int i, int j) {
  T temp = elem[i];
  elem[i] = elem[j];
  elem[j] = temp;
}

template <class T, class Compare> bool Heap<T, Compare>::bubbleDown(int &k) {
  int lc = k * 2 + 1, rc = lc + 1;
  // it is possible that some of the childs are outside of the allocated space

  bool lb, rb;
  lb = lc < last;
  rb = rc < last;

  if (lb && rb) {
    if (comp(elem[k], elem[lc]) && comp(elem[k], elem[rc])) {
      return true; // no need to bubble down
    }

    if (comp(elem[lc], elem[rc])) // left child is greater
    {
      swap(k, lc);
      k = lc;
      return false;
    } else { // right child is greater
      swap(k, rc);
      k = rc;
      return false;
    }
  } else if (lb) {
    if (comp(elem[lc], elem[k])) // left child is greater
    {
      swap(k, lc);
      k = lc;
      return false;
    } else {
      return true;
    }
  } else {
    return true;
  }
}

template <class T, class Compare> void Heap<T, Compare>::bubbleUp(int index) {
  int parent_index = (index - 1) / 2; 
  if (index == 0 || comp(elem[parent_index], elem[index])) {
    return;
  }
  swap(index, parent_index);
  bubbleUp(parent_index);
  return;
}

template <class T, class Compare> void Heap<T, Compare>::pop() {
  if (space == 0)
    return; // so that if you pop an empty heap the program does not
                 // crash. (but there is undefined behaviour)
  --space;
  elem[0] = elem[space];
  int k = 0;
  bool bubStop = false;
  while (bubStop == false) {
    bubStop = bubbleDown(k);
  }
  return;
}

template <class T, class Compare> void Heap<T, Compare>::insert(T new_key) {
  if (freeSpace() == 0)
    reallocate();
  elem[space] = new_key;
  bubbleUp(space);
  space++;
}

template <class T, class Compare> T &Heap<T, Compare>::top() { return *elem; }

template <class T, class Compare> int Heap<T, Compare>::size() { return space; }

#ifdef __PC
template <class T, class Compare> void Heap<T, Compare>::print() {
  for (int i = 0; i != space; i++)
    std::cout << " " << elem[i];

  std::cout << std::endl;
}
#endif

#endif
