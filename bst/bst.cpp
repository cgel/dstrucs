#include <stddef.h>
#include <iostream>


template <class T>
class Tree
{
    // Internal class which stores only Node related information.
    struct TreeNode
    {
        T& key;
        TreeNode* parent;
        TreeNode* left;
        TreeNode* right;

        TreeNode(T& _key, TreeNode* _parent):key(_key),parent(_parent), left(NULL),right(NULL) {}

        ~TreeNode()
        {
          delete left; 
          delete right; 
        }
    };

    TreeNode* nodeFind(const T&) const;
    TreeNode* root;

public:
    Tree();
    ~Tree();

    void insert(T&);
    T& pop();
    T& max() const;
    T& min() const;
    T* find(const T&) const;
    bool erase(const T& k);
};


template <class T>
Tree<T>::Tree():root(NULL)
{

}


template <class T>
Tree<T>::~Tree()
{
    delete root;
}


template <class T>
bool Tree<T>::erase(const T& key)
{
  TreeNode* n = nodeFind(key);
  short int c = nChilds(n);
  
  // if this node has 1+ childs
  if(n->right || n->left)
  {

  }
  else { // no childs

  }
}

template <class T>
void Tree<T>::insert(T& key)
{
  TreeNode* temp;
  TreeNode* parent;

  if (root==NULL)
  {
    root = new TreeNode(key, NULL); //NULL parent
    return;
  }

  temp = root;
  while(1)
  {
    parent = temp;
    if (temp->key < key)
    {
      if(temp->right == NULL)
      {
        temp->right = new TreeNode(key, parent);
        return;        
      }
      else temp = temp->right;
    }
    else
    {
      if(temp->left == NULL)
      {
        temp->left = new TreeNode(key, parent);
        return;        
      }
      else temp = temp->left;
    }
  }
}

template <class T>
typename Tree<T>::TreeNode* Tree<T>::nodeFind(const T& key) const
{
  TreeNode* temp;
  temp = root;

again:
  if (temp->key == key) return temp;
  else
  {
    if (temp->key < key)
    {
      if (temp->right == NULL) return NULL;
      temp = temp->right;
    }
    else
    {
      if (temp->left == NULL) return NULL;
      temp = temp->left;
    }
  }
  goto again;
}


template <class T>
T* Tree<T>::find(const T& key) const
{
  TreeNode* n = nodeFind(key);
  if (n != NULL) return &n->key;
  else return NULL;
}

template <class T>
T& Tree<T>::max() const
{
  TreeNode* temp = root;
again:
  if(temp->right == NULL) return temp->key;
  temp = temp->right; 
  goto again;
}

template <class T>
T& Tree<T>::min() const
{
  TreeNode* temp = root;

again:
  if(temp->left == NULL) return temp->key;
  temp = temp->left; 
  goto again;
}


int main()
{
  int a = 2, b = -1, c = 3, d = 5, e = -7;
  Tree<int> t; 
  t.insert(a);
  t.insert(b);
  t.insert(c);
  t.insert(d);
  t.insert(e);

  std::cout << "is there a 3 in the tree? (yes) "<< (t.find(3)!=NULL?"yes":"no") << std::endl;
  std::cout << "is there a -10 in the tree? (no) "<< (t.find(-10)!=NULL?"yes":"no") << std::endl;

  std::cout << "max? (5) " << t.max() << std::endl;
  std::cout << "min? (-7) " << t.min() << std::endl;
  return 0;
}
