#define STD_BUFFER 10
#include <iostream>

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
  void print();
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

  return temp;
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

template<typename T>
void Heap<T>::print()
{
  for(int i = 0; i!= space; i++)
    std::cout << " " << elem[i];

  std::cout << std::endl;
}


using namespace std;
int main()
{
  Heap<int> h;
  h.insert(7);
  h.insert(6);
  h.insert(8);
  h.insert(8);
  h.insert(6);
  h.insert(1);
  h.insert(0);
  h.insert(0);
  h.insert(27);
  h.insert(59);
  h.insert(-20);
  h.insert(30);
  h.insert(10);

  h.print();

  char k;
  bool stop = false;
  while (stop == false)
  {
    
    cout << "please type an input" << endl;
    cin>>k;
    switch(k){
        case 'i':
        {
        //insert new element
         cout << "type the number you want to insert" << endl;
         int ne;
         cin>>ne;
         h.insert(ne);
         h.print();
         break; /* optional */
        }
        case 'p':
        {
         // pop
         int p = h.pop();
         cout << "poped: " << p << endl;
         h.print();
         break; /* optional */
        }
        case 't':
        {
         // pop
         int p = h.top();
         cout << "top is: " << p << endl;
         h.print();
         break; /* optional */
        }
        case 'q':
        case 'e':
        {
         // pop
         stop = true;
         break;
        }
        default: /* Optional */
           cout << "input not valid enter 'p' to pop, 'i' to insert and 'e' to exit" << endl;
    }
    cin.clear();
    cin.ignore(100);
  }
  return 0;
}
