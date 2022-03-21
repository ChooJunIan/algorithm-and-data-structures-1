#include <cstdlib>
#include <iostream>

using namespace std;

struct node 
{
   string d;
   struct node *l = NULL;
   struct node *r = NULL;
};

class avl
{
   public:
   struct node *root; 

   // Insert a new node into the AVL tree
   node * insert(node *p, string v) {
      if (p == NULL){
         p = new node;
         p->d = v; 
      }
      else if (v < p->d)
         p->l = insert(p->l, v); 
      else 
         p->r = insert(p->r, v);

      p = balance(p);
      return p;
   }

   // get the height of a node
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

   // determines the balance that has to be done on a node after calculating the balance factor
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

   // calculate the height of a node's subtrees to obtain the balance factor
   int balanceFactor(node* p) {
      int leftHeight = nodeHeight(p->l);
      int rightHeight = nodeHeight(p->r);
      return rightHeight - leftHeight;
   }

   // conducts left rotation on a node
   node* leftRotate(node* p) {
      node* temp = p->r;
      p->r = temp->l;
      temp->l = p;
      return temp;
   }

   // conducts a right rotation on a node
   node* rightRotate(node* p) {
      node* temp = p->l;
      p->l = temp->r;
      temp->r = p;
      return temp;
   }

   // conducts a left rotation, followed by a right notation on a node
   node* leftRightRotate(node* p) {
      node* temp = p->l;
      p->l = leftRotate(temp);
      return rightRotate(p);
   }

   // conducts a right rotation, followed by a left notation on a node
   node* rightLeftRotate(node* p) {
      node* temp = p->r;
      p->r = rightRotate(temp);
      return leftRotate(p);
   }

   // creates a preorder traversal of all the nodes. Root is output first, followed 
   // by the left node the right node next (root -> left -> right).
   void preorder(node* p) {
      if(p != NULL) {
         cout << p->d << " " << endl;
         preorder(p->l);
         preorder(p->r);
      }
      else return;
   }

   // creates a postorder traversal of all the nodes. The left node is output first,
   // followed by the right node and lastly the root node (left -> right -> root).
   void postorder(node* p) {
      if(p != NULL) {
         postorder(p->l);
         postorder(p->r);
         cout << p->d << " ";
      }
      else return;
      cout << endl;
   }

   // creates an inorder traversal of all the nodes. The left node is output first, 
   // followed by the root node and lastly the right node (left -> root -> right).
   // The output is sorted
   void inorder(node* p) {
      if(p != NULL) {
         inorder(p->l);
         cout << p->d << " " << endl;
         inorder(p->r);
      }
      else return;
   }

   // searches for a node in the AVL tree
   void search(node* p, string a) {
      if(p == NULL) {
         cout << "Email not found." << endl;
         return;
      }
      if(p->d == a) {
         cout << p-> d << " is found." << endl;
         return;
      }
      else if(a < p->d)
         return search(p->l, a);
      else
         return search(p->r, a);
   }

   avl()
   {
      root = NULL;
   }
};
