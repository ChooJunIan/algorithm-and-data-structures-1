#include <iostream>
#include <fstream>
#include <chrono>

#include "avl.cpp"

using namespace std;

int main() {

   //declaration of all the variables to be used in the main program
   avl tree;
   string* listOfEmails;
   string* searchFound = new string[10];
   string* searchNotFound = new string[10];
   bool choice = false;
   int menu, size;
   string path, pathFound, pathNotFound;
   ifstream inFile;

   // the main menu to select the sets of data to be inserted into the AVL tree
   do {
      cout <<"SELECT THE SET TO BE INSERTED INTO THE AVL TREE: "<<endl;
      cout <<"1. SetA (100 Items)"<<endl;
      cout <<"2. SetB (100000 Items)"<<endl;
      cout <<"3. SetC (500000 Items)"<<endl;
      cin>> menu;
      
      if(menu == 1) {
         size = 100;
         listOfEmails = new string [size];
         path = "SetA.txt";
         pathFound = "SetA_10ToBeFound.txt";
         pathNotFound = "AllSets_10NotToBeFound.txt";
      }
      else if(menu == 2) {
         size = 100000;
         listOfEmails = new string [size];
         path = "SetB.txt";
         pathFound = "SetB_10ToBeFound.txt";
         pathNotFound = "AllSets_10NotToBeFound.txt";
      }
      else if(menu == 3) {
         size = 500000;
         listOfEmails = new string [size];
         path = "SetC.txt";
         pathFound = "SetC_10ToBeFound.txt";
         pathNotFound = "AllSets_10NotToBeFound.txt";
      }
      else {
         cout<<"PLEASE SELECT THE STATED OPTIONS"<<endl;
         cout<<endl;
         choice = true;
      }
   } while(choice == true);


   //input file to array of strings (list of emails, emails to be found, emails not to be found)
   inFile.open(path);
   if(inFile.is_open()) {
      int num = 0;
      while(inFile) {
         inFile >> listOfEmails[num];
         num++;
      }
      inFile.close();
   }

   inFile.open(pathFound);
   if(inFile.is_open()) {
      int num = 0;
      while(inFile) {
         inFile >> searchFound[num];
         num++;
      }
      inFile.close();
   }

   inFile.open(pathNotFound);
   if(inFile.is_open()) {
      int num = 0;
      while(inFile) {
         inFile >> searchNotFound[num];
         num++;
      }
      inFile.close();
   }

   cout << endl;

   // Insert data into AVL Tree
   cout << "INSERTING DATA INTO AVL TREE ..... PLEASE WAIT PATIENTLY" << endl;
   cout << endl;

   // Start time to count insertion of data into AVL TREE
   auto timeStart = chrono::system_clock::now();

   // Inserting data into the AVL tree
   for(int i = 0; i < size; i++) {
      tree.root = tree.insert(tree.root, listOfEmails[i]);
   }

   // End time to count insertion of data into AVL TREE
   auto timeEnd = chrono::system_clock::now();

   //Duration of Insertion Time
   chrono::duration<double> timeDuration = timeEnd - timeStart;
   cout << "Insert duration: " << timeDuration.count() << "s\n" << endl;

   // For option one only. To print the data sets in preorder, postorder and inorder traversal
   if(path.compare("SetA.txt") == 0) {
      cout << "PREORDER TRAVERSAL:" << endl;
      tree.preorder(tree.root);
      cout << endl;
      cout << "POSTORDER TRAVERSAL" << endl;
      tree.postorder(tree.root);
      cout << endl;
      cout << "INORDER TRAVERSAL" << endl;
      tree.inorder(tree.root);
      cout << endl;
   }

   // search data in the binary tree
   cout << "SEARCHING DATA IN AVL TREE..." << endl;
   cout << endl;

   auto searchFStart = chrono::system_clock::now();

   // found search data
   for(int i = 0; i < 10; i++) {
      tree.search(tree.root, searchFound[i]);
      cout << endl;
   }

   auto searchFEnd = chrono::system_clock::now();
   chrono::duration<double> searchFDuration = searchFEnd - searchFStart;
   cout << "Search duration for emails found: " << searchFDuration.count() << "s\n" << endl;

   auto searchNFStart = chrono::system_clock::now();

   // not found search data
   for(int i = 0; i < 10; i++) {
      tree.search(tree.root, searchNotFound[i]);
      cout << endl;
   }

   auto searchNFEnd = chrono::system_clock::now();
   chrono::duration<double> searchNFDuration = searchNFEnd - searchNFStart;
   cout << "Search duration for emails not found: " << searchNFDuration.count() << "s\n" << endl;
      
   return 0;
}
