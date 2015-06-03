#define STD_BUFFER 10
#include <iostream>
#include <ostream>


template<class T>
struct Greater{
  //bool operator<(const Less& rhs) { return 
  bool operator()(const T& lhs, const T& rhs)
  {
    return lhs > rhs;
  }
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

template<class T, class Compare>
Heap<T, Compare>::Heap()
{
  elem = new T[STD_BUFFER];
  space = 0;
  last = STD_BUFFER;
}

template<class T, class Compare>
Heap<T, Compare>::~Heap()
{
  delete[] elem;
}

template<class T, class Compare>
inline int Heap<T, Compare>::freeSpace()
{
  return last - space;
}

template<class T, class Compare>
void Heap<T, Compare>::reallocate()
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


template<class T, class Compare>
void Heap<T, Compare>::swap(int i, int j)
{
  T temp = elem[i];
  elem[i] = elem[j];
  elem[j] = temp;
}

template<class T, class Compare>
bool Heap<T, Compare>::bubbleDown(int& k)
{
  int lc = k*2 +1, rc = lc +1;
  // it is possible that some of the childs are outside of the allocated space
  
  bool lb, rb;
  lb = lc < last;
  rb = rc < last;

  if(lb && rb)
  {
    if(comp(elem[k], elem[lc]) && comp(elem[k], elem[rc]))
    {
      return true; // no need to bubble down
    }

    if(comp(elem[lc], elem[rc])) // left child is greater 
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
    if(comp(elem[lc], elem[k])) // left child is greater 
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

template<class T, class Compare>
bool Heap<T, Compare>::bubbleUp(int& k)
{
  int ik = (k-1)/2; // parent index
  if(k == 0 || comp(elem[ik], elem[k]))
  {
    return true;
  }
  else { // parent is smaller 
   swap(k, ik);
   k = ik;
   return false;
  }
}


template<class T, class Compare>
T Heap<T, Compare>::pop()
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

template<class T, class Compare>
void Heap<T, Compare>::insert(T key)
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

template<class T, class Compare>
T& Heap<T, Compare>::top()
{
  return *elem;
}

template<class T, class Compare>
int Heap<T, Compare>::size()
{
  return space; 
}

template<class T, class Compare>
void Heap<T, Compare>::print()
{
  for(int i = 0; i!= space; i++)
    std::cout << " " << elem[i];

  std::cout << std::endl;
}

using namespace std;

struct Person {
  Person() {}
  Person(const char* n, const int a): name(n), age(a) {}
  const char* name;
  int age;

  friend ostream& operator<< (ostream&, Person&);

  friend bool operator>(const Person& rhs, const Person& lhs);

};

ostream& operator<< (ostream &out, Person &per)
{
    out << "(" << per.name << ", " << per.age << ")";
    return out;
}

bool operator>(const Person& lhs, const Person& rhs)
{
  return lhs.age > rhs.age;
}

struct PersonPCompare{
  //bool operator<(const Less& rhs) { return 
  bool operator()(const Person* lhs, const Person* rhs)
  {
    return lhs->age < rhs->age;
  }
};

struct PersonCompare{
  //bool operator<(const Less& rhs) { return 
  bool operator()(const Person& lhs, const Person& rhs)
  {
    return lhs.age < rhs.age;
  }
};


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

  Person p1 ("carles", 17), p2 ("Joan", 23), p3 ("Pepitu", 32), p4 ("Anna", 13);
  Heap<Person, PersonCompare> hp;
  hp.insert(p1);
  hp.insert(p2);
  hp.insert(p3);
  hp.insert(p4);

  Person* pp1 = &p1;
  Person* pp2 = &p2;
  Person* pp3 = &p3;
  Person* pp4 = &p4;
  hp.print();

  Heap<Person*, PersonPCompare> hpp;
  hpp.insert(pp1);
  hpp.insert(pp2);
  hpp.insert(pp3);
  hpp.insert(pp4);

  hpp.print();


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
