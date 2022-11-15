 //============================================================================
// Name         : lab12.cpp
// Author       : Theo Welckle
// Version      : 1.0
// Date Created : 20-4-2022
// Date Modified: 20-04-2022 
// Description  : AVL Tree
// Copyright © 2020 Khalid Mengal. All rights reserved.
//============================================================================
#include<iostream>
#include<cstdlib>
#include<iomanip>

using namespace std;

class Node
{
	private:
		int key;
		Node* left;
		Node* right;
	public:
		Node(int key);
		~Node();
		int getKey() { return this->key;}
		friend class AVL;
};

Node::Node(int key)
{
	this->key = key;
	this->left = nullptr;
	this->right = nullptr;
}
Node::~Node()
{
	//cout<<"deleted.."<<this->key<<endl;
	//cout<<"----------------------------------"<<endl;
}
//=============================================================================
class AVL
{
	private:
		Node *root;
	public:
		AVL();									//constructor
		~AVL();									//destructor
		Node* getRoot();						//returns the root of the Tree
		Node* insert(Node* ptr,int key);		//Insert key into tree/subtree with root ptr
		void printInorder(Node* ptr);			//Traverse (inroder) and print the key of a tree/subtree with root ptr
		int height(Node *ptr);				    //Find the height(MaxDepth) of a tree/subtree with root ptr
		Node* findMin(Node *ptr);				//Find and return the Node with minimum key value from a tree/subtree with root ptr
		Node* findMax(Node *ptr);				//Find and return the Node with Max key value from a tree/subtree with root ptr		
		Node* findKey(Node *ptr,int key);		//Find and returns the node with key
		Node* remove(Node *ptr,int key);		//Remove a node with key from the tree/subtree with root
		Node* rotateLeft(Node *z);
		Node* rotateRight(Node *z);
		void printTree();						//Print 2D Tree
	public:	//helper methods
		void insert_helper(int key);			//Helper method for insert method
		void remove_helper(int key);			//Helper method for remove method
	private:
		void printTreeHelper(int *A,bool *B, Node *ptr, int n); //Helper method for PrintTree()
		int balanceFactor(Node *ptr);
		Node* rebalance(Node *ptr);    			// rebalance a node
};

//==========================================================
void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"display            :Display the AVL Tree"<<endl
		<<"insert <key>       :Insert a new node in AVL"<<endl
		<<"remove <key>       :Remove the node from AVL "<<endl
		<<"height             :Find the hieght of the Tree"<<endl
		<<"min                :Find the node with minimum key in AVL"<<endl
		<<"max                :Find the node with maximum key in AVL"<<endl
		<<"find <key>         :Find a node with a given key value in AVL"<<endl
		<<"inorder            :Print the AVL in Inorder"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}
//==========================================================
void demo( AVL &myAVL)
{
	myAVL.insert_helper(10);
	myAVL.insert_helper(9);
	myAVL.insert_helper(8);
	myAVL.insert_helper(5);
	myAVL.insert_helper(6);
	myAVL.insert_helper(4);
	myAVL.insert_helper(11);
	myAVL.insert_helper(12);
	myAVL.printTree();
}
//==========================================================
int main(void)
{
	AVL myAVL;
	listCommands();
	string user_input;
	string command;
	string key;

	while(true)
	{
		cout<<">";
		getline(cin,user_input);

		command = user_input.substr(0,user_input.find(" "));
		key = user_input.substr(user_input.find(" ")+1);
		
		Node* root = myAVL.getRoot();	//get the root of the tree
		cout<<"----------------------------------"<<endl;
		if( user_input =="display")	myAVL.printTree();
		else if( command =="insert" or command=="i")	{ myAVL.insert_helper(stoi(key)); myAVL.printTree();} 
		else if( command =="remove" or command=="r")	{ myAVL.remove_helper(stoi(key)); myAVL.printTree();}
		else if( command =="height")	cout<<"Height = "<<myAVL.height(root)<<endl;
		else if( command =="min")	
		{
			Node* min = myAVL.findMin(root);
			cout<<"Min. key = "<<((min!=nullptr)? to_string(min->getKey()):" does not exist")<<endl;
		}
		else if( command =="max")	
		{
			Node* max = myAVL.findMax(root);
			cout<<"Max. key = "<<((max!=nullptr)? to_string(max->getKey()):" does not exist")<<endl;
		}
		else if( command =="find")	cout<<key<<(myAVL.findKey(root,stoi(key))==nullptr ? " not found":" found")<<endl;
		else if( command =="inorder")	{myAVL.printInorder(root); cout<<endl;}
		else if( command =="exit") break;
		else if( command == "demo") demo(myAVL); 
		else if( command == "help") listCommands();
		else if( command == "exit") break;
		else cout<<"Invalid command !!!"<<endl;
	}
	return 0;
}
//=====================================================================
AVL::AVL()
{
	this->root=nullptr;
}
AVL::~AVL()
{
	//Keep removing the Node with Min (or Max) value util entire tree becomes empty
	while(root)
		root=remove(root,findMin(root)->key);
}
// Return the root of the tree
Node* AVL::getRoot()
{
	return root;
}

//Print recursively the tree/subtree rooted at ptr Inorder fromat
void AVL::printInorder(Node *ptr)
{
	if(ptr!=nullptr)
	{
		printInorder(ptr->left);
		cout<<ptr->key<<" ";
		printInorder(ptr->right);
	}
}
//Find the Height (MaxDepth) of the tree/subtree rooted at ptr
int AVL::height(Node* ptr)
{
	if(ptr==nullptr) return -1;
	return max(height(ptr->left),height(ptr->right))+1;
}
// Find recursively (or iteratively ) the key with minimum in the tree/subtree rooted at ptr
Node* AVL::findMin(Node *ptr)
{

	if(ptr==nullptr) 		return nullptr; //if Tree is empty
	else if(ptr->left)		//recursive approach to find the node with minimum key in the tree
		return findMin(ptr->left);
	else								//if reached to the left most node
		return ptr;
}
// Find recursively (or iteratively ) the key with Maximum in the tree/subtree rooted at ptr
Node* AVL::findMax(Node *ptr)
{

	if(ptr==nullptr) 		return nullptr; //if Tree is empty
	else if(ptr->right)		//recursive approach to find the node with Maximum key in the tree
		return findMax(ptr->right);
	else								//if reached to the right most node
		return ptr;
}
// Find recursively the node with key value in the tree/subtree rooted at ptr
Node* AVL::findKey(Node *ptr,int key)
{
	if(ptr==nullptr) 			return nullptr;
	else if(key == ptr->key) 	return ptr;
	else if(key < ptr->key) 	return findKey(ptr->left,key);
	else						return findKey(ptr->right,key);
}
// Calculate and returns the Balance Factor of a Node
int AVL::balanceFactor(Node *ptr)
{
	//height of left minus height of right.
	return height(ptr->left) - height(ptr->right);
}
//Helper method for insert method
void AVL::insert_helper(int key)
{	
	root=insert(root,key);
}
//Insert recursively the key in the tree/subtree rooted at ptr
Node* AVL::insert(Node *ptr, int key)
{
	//............................
	// Write the code of insert method from your solution for the lab9 BST
	//if null create new node and return it
	if(ptr == NULL){
		Node* newNode = new Node(key);
		return newNode;
	}
	//no duplicate keys
	else if(ptr->key == key){
		cout<<"Can not have duplicate Keys";
		return ptr;
	}
	//key is bigger check the right side of tree. Redefine the connection between nodes
	else if(key>ptr->key){
		Node* connection = insert(ptr->right, key);
		ptr->right = connection;
	}
	//key is smaller, check the left side of tree. Redefine the connection between nodes.
	else if(key<ptr->key){
		Node* connection = insert(ptr->left, key);
		ptr->left = connection; 
	}

	//............................
	ptr = rebalance(ptr);
	return ptr;
}
//==========================================
// Rotate a node to its right
Node* AVL::rotateRight(Node *z)
{  
	//take the left node and make it the root. Adjust the connecting nodes accordingly.
	Node* newRoot = z->left;
	Node* newRootRight = newRoot->right;
	newRoot->right = z;
	z->left = newRootRight;
	return newRoot;
	//todo
}  
//==========================================
// Rotate a node to its left  
Node* AVL::rotateLeft(Node *z)
{  
	//take the right node and make it the root. Adjust the connecting nodes accordingly. 
	Node* newRoot = z->right;
	Node* newRootLeft = newRoot->left;
	newRoot->left = z;
	z->right = newRootLeft;
	return newRoot;
	//todo
}
//============================================
// Rebalane a node (ptr)
Node* AVL::rebalance(Node *ptr)
{
	int balanced = balanceFactor(ptr);
	// case 0: Already balanced
	if(balanced>=-1 and balanced <=1){
		return ptr;
	}
	else if(balanced <= -2){
		//Right Right Heavey
		if(balanceFactor(ptr->right)<=-1){
			ptr = rotateLeft(ptr);
		}
		//right left heavy
		else{
			ptr->right = rotateRight(ptr->right);
			ptr = rotateLeft(ptr);

		}
	}
	else if(balanced >= 2){
		//left left heavy
		if(balanceFactor(ptr->left)>= 1){
			ptr = rotateRight(ptr);
		}
		//left right heavy
		else{
			ptr->left = rotateLeft(ptr->left);
			ptr = rotateRight(ptr);
		}
	}
	return ptr;
}
//=================================================
//Helper method for remove 
void AVL::remove_helper(int key)
{
	if(findKey(root,key)==nullptr)
		cout<<"Key not found..."<<endl;
	else	
		root = remove(root, key);
}
//Remove recursively the node with key value from the tree/subtree rooted at ptr
Node* AVL::remove(Node *ptr,int key)
{
	//.............
	// Please write the code of the remove method from your solution of the Lab9 (BST Here)
	//I directly Copied this code from my Lab9 BST solution. I hope this is okay. 
		//if bottom of the tree is reached, then the key/node does not exist.
	if(ptr == NULL) cout<<"This key is not found in the tree"<<endl;

	//traverse the tree trying to find the key, while also redefining the edges of the tree. 
	else if(key>ptr->key){
		Node* connection = remove(ptr->right, key);
		ptr->right = connection;
	}
	else if(key<ptr->key){
		Node* connection = remove(ptr->left, key);
		ptr->left = connection;
	} 
	//if key is found.
	else{
		Node* workingNode = ptr;

		//Case 1. Leaf Node, just delete Node and return NULL.
		if(workingNode->left == NULL && workingNode->right == NULL){
			delete workingNode;
			return NULL;
		}
		//Case 2. If the right side of the node is NULL, but the left side has an edge.
		//delete node and return the left node.
		else if(workingNode->right == NULL){
			Node* temp = workingNode->left;
			delete workingNode;
			return temp;
		}
		//Case 3. If the left side of the node is NULL, but the right side has an edge.
		//delete node and return the right node.
		else if(workingNode->left == NULL){
			Node* temp = workingNode->right;
			delete workingNode;
			return temp;
		}
		//Case 4. If the node is an internal node with both a right and a left side.
		//Find the minimum key value for the right side of that node. Swap the key values with that node.
		//Remove the node with the key. 
		else{
			Node* minNode = findMin(workingNode->right);

			int temp = minNode->key;
			minNode->key = workingNode->key;
			workingNode->key = temp;
			
			Node* connection = remove(workingNode->right, minNode->key);
			workingNode->right = connection;
		}
	}
	//............
	ptr=rebalance(ptr);
	return ptr;
}
//==================================================================
//  This method prints a Binary Tree in 2D format
//  Created by Saurabh Ray 
//  Copyright © 2020 Saurabh Ray. All rights reserved.

void AVL::printTree(){
   cout<<"Tree :"<<endl;
   char *space = (char*)("  ");
   int d = height(this->getRoot());
   int n = (1<<(d+1))- 1; // n = 2^(d+1)-1

   int *A = new int[n];
   bool *B = new bool[n];
   for(int i=0; i<n; ++i) B[i]=false;

   printTreeHelper(A,B,root,n);


   //cout<<"\nTree:"<<endl;
   for(int t=(n+1)/2; t>0; t=t/2){
        for(int j=0; j<n; j++){
            if( ((j+1)%t == 0) && B[j]){
                cout<<setw(3)<<A[j];
                B[j] = false;
            }
            else{
                cout<<setw(3)<<space;
            }
        }
        cout<<endl;
   }
   cout<<endl;
   delete [] A;
   delete [] B;
}

void AVL::printTreeHelper(int *A, bool *B, Node *ptr, int n){
    if(ptr!=nullptr){
        int mid = (n-1)/2;
        A[mid] = ptr->key;
        B[mid] = true;
        printTreeHelper(A,B,ptr->left,mid);
        printTreeHelper(A+(mid+1),B+(mid+1), ptr->right, mid);
    }
}