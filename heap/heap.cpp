#define STD_BUFFER 20

template<class T>
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

  public:
  Heap();
  ~Heap();

  T& top();
  T pop();
  void insert(T);
  int size();
};

template<class T>
inline int Heap<T>::freeSpace()
{
    return last - space;
}

template<class T>
Heap<T>::Heap()
{
    elem = new T[STD_BUFFER];
    space = 0;
    last = STD_BUFFER;
}

template<class T>
Heap<T>::~Heap()
{
    delete[] elem;
}

template<class T>
void Heap<T>::reallocate()
{
    int s = size();
    int newSize = s*2;
    T* newElem = new T[newSize];
    for(int i = 0; i != s; i++)
    {
        newElem[i] = elem[i];
    }
    delete[] elem;
    elem = newElem;
    space = s;
    last = newSize; 
}


template<typename T>
void Heap<T>::swap(int i, int j)
{
    T temp = elem[i];
    elem[i] = elem[j];
    elem[j] = elem[i];
}

template<typename T>
bool Heap<T>::bubbleDown(int& k)
{
  int lc = k*2 +1, rc = k*2 +2;
  if(elem[k] > elem[lc] || elem[k] > elem[rc]) return true;
  if(elem[lc] > elem[rc]){ swap(k, lc); k = lc;} // left child is greater 
  else { swap(k, rc); k = rc;}// right child is greater
}

template<typename T>
bool Heap<T>::bubbleUp(int& k)
{
  int ik = (k-1)/2; // parent index
  if(ik == 0 || elem[ik] > elem[k]) return true;
  else { swap(k, ik); k = ik;}// parent is smaller 
}


template<typename T>
T Heap<T>::pop()
{
  T temp = *elem;
  elem[0] = elem[space];
  int k = 0;
  bool bubStop = false;
  while( bubStop == false)
  {
      bubStop = bubbleDown(k);
  }

}

template<class T>
void Heap<T>::insert(T key)
{
    if( freeSpace() == 0) reallocate();

    elem[space] = key;
    space ++;

    int k = space;
    bool bEnd = false;
    while( bEnd == true)
    {
        bEnd = bubbleUp(k);
    }
}

template<typename T>
T& Heap<T>::top()
{
    return *elem;
}

template<typename T>
int Heap<T>::size()
{
    return space; 
}


int main()
{
  return 0;
}
