// avl.cpp
#include <cstdlib>
#include <iostream>

using namespace std;

typedef string T;

struct node //node declaration
{
   T d;
   struct node *l = NULL;
   struct node *r = NULL;
};

class avl
{
   public:
   struct node *root;

   node * insert(node *r, T v)
   {
      // recursively call the insert function – refer to algorithm
      if (r == NULL){
         r = new node;
         r->d = v; 
      }
      else if (v < r->d)
         r->l = insert(r->l, v); 
      else 
         r->r = insert(r->r, v);

      r = balance(r);
      return r;
   }

   node * deleteItem(node *p, T v)
   {
      node *temp;

      if (p == NULL)
         return p;

      if (v < p->d)
         p->l = deleteItem(p->l, v);


      else
      {
         if (v > p->d)
            p->r = deleteItem(p->r, v);

         else
         {
            if (p->l == NULL && p->r == NULL)  // no child
               p = NULL;
            else if (p->l == NULL || p->r == NULL) // one child
            {
               if(p->r != NULL) 
                  temp = p->r;
               else  
                  temp = p->l;
               return temp;
            }
            else     // two child nodes
            {
               temp = getSuccessor(p->l);// use getSuccessor() here
               p->d = temp->d;
               p->l = deleteItem(p->l, temp->d);
            }
         }
      }

      return p;
   } 

   node * getSuccessor(node *p)   // used in delete function
   {
      if(p->r == NULL)
         return p;
      else 
         return getSuccessor(p->r);
   }

   int nodeHeight(node* p) {
      int height;
      if(p == NULL) {
         height = 0;
      }
      else {
         int leftHeight = nodeHeight(p->l);
         int rightHeight = nodeHeight(p->r);
         height = max(leftHeight, rightHeight) + 1;
      }
      return height;
   }

   node* balance(node* p) {
      int bf = balanceFactor(p);
      if (bf < -1) {
         if(balanceFactor(p->l) < 0)
            p = rightRotate(p);
         else
            p = leftRightRotate(p);
      }
      else if (bf > 1) {
         if(balanceFactor(p->r) < 0) 
            p = rightLeftRotate(p);
         else 
            p = leftRotate(p);
      }
      return p;
   }

   int balanceFactor(node* p) {
      int leftHeight = nodeHeight(p->l);
      int rightHeight = nodeHeight(p->r);
      return rightHeight - leftHeight;
   }

   node* leftRotate(node* p) {
      node* temp = p->r;
      p->r = temp->l;
      temp->l = p;
      return temp;
   }

   node* rightRotate(node* p) {
      node* temp = p->l;
      p->l = temp->r;
      temp->r = p;
      return temp;
   }

   node* leftRightRotate(node* p) {
      node* temp = p->l;
      p->l = leftRotate(temp);
      return rightRotate(p);
   }

   node* rightLeftRotate(node* p) {
      node* temp = p->r;
      p->r = rightRotate(temp);
      return leftRotate(p);
   }

   void preorder(node* p) {
      if(p != NULL) {
         cout << p->d << " " << endl;
         preorder(p->l);
         preorder(p->r);
      }
      else return;
   }

   void postorder(node* p) {
      if(p != NULL) {
         postorder(p->l);
         postorder(p->r);
         cout << p->d << " ";
      }
      else return;
      cout << endl;
   }

   void inorder(node* p) {
      if(p != NULL) {
         inorder(p->l);
         cout << p->d << " " << endl;
         inorder(p->r);
      }
      else return;
   }

   void search(node* p, T a) {
      if(p == NULL) {
         cout << "Email not found." << endl;
         return;
      }
      if(p->d == a) {
         cout << p-> d << " is found." << endl;
         return;
      }
      else if(a < root->d)
         return search(root->l, a);
      else
         return search(root->r, a);
   }

   void show(node *p, int lvl)
   {
      int i;
      if (p != NULL)
      {
         if (p == root)
            cout << "Root: " << p->d << endl;
         else
         {
            cout << p->d << endl;
         }
         cout << lvl << "L: ";
         show(p->l, lvl + 1);
         cout << "\n" << lvl << "R: ";
         show(p->r, lvl + 1);
      }
   }

   avl()
   {
      root = NULL;
   }
};
