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
  elem[j] = temp;
}

template<typename T>
bool Heap<T>::bubbleDown(int& k)
{
  int lc = k*2 +1, rc = lc +1;
  // it is possible that some of the childs are outside of the allocated space
  
  bool lb, rb;
  lb = lc < last;
  rb = rc < last;

  if(lb && rb)
  {
    if(elem[k] > elem[lc] && elem[k] > elem[rc])
    {
      return true; // no need to bubble down
    }

    if(elem[lc] > elem[rc]) // left child is greater 
    {
      swap(k, lc);
      k = lc;
      return false;
    } else { // right child is greater
      swap(k, rc);
      k = rc;
      return false;
    }
  }
  else if(lb) {
    if(elem[lc] > elem[k]) // left child is greater 
    {
      swap(k, lc);
      k = lc;
      return false;
    }
    else {
      return true;
    }
  }
  else {
    return true;
  }
}

template<typename T>
bool Heap<T>::bubbleUp(int& k)
{
  int ik = (k-1)/2; // parent index
  if(k == 0 || elem[ik] > elem[k])
  {
    return true;
  }
  else { // parent is smaller 
   swap(k, ik);
   k = ik;
   return false;
  }
}


template<typename T>
T Heap<T>::pop()
{
  T temp = *elem;

  if (space == 0) return temp; // so that if you pop an empty heap the program does not crash. (but there is undefined behaviour)
  --space;
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
  int k = space;

  space ++;
  bool bubStop = false;
  while( bubStop == false)
  {
    bubStop = bubbleUp(k);
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
    cin.ignore(100, '\n');
  }
  return 0;
}
