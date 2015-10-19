#include <iostream>
#include "heap.h" 

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
