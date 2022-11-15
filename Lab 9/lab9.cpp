 //============================================================================
// Name         : lab9.cpp
// Author       : Theo Welckle
// Version      : 1.0
// Date Created : 03-29-2021
// Date Modified: 03-29-2021
// Description  : BST Tree implementation in C++
// Copyright © 2020 Khalid Mengal. All rights reserved.
//============================================================================
#include<iostream>
#include<sstream>
#include<cstdlib>

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
		friend class BST;
};

Node::Node(int key)
{
	this->key = key;
	this->left = nullptr;
	this->right = nullptr;
}
Node::~Node()
{
	cout<<"deleted.."<<this->key<<endl;
}
//=============================================================================
class BST
{
	private:
		Node *root;
	public:
		BST();									//constructor
		~BST();									//destructor
		Node* getRoot();						//returns the root of the Tree
		int height(Node *ptr);				    //Find the height of a tree/subtree with root ptr
		Node* findMin(Node *ptr);				//Find and return the Node with minimum key value from a tree/subtree with root ptr
		Node* findMax(Node *ptr);				//Find and return the Node with Max key value from a tree/subtree with root ptr		
		Node* findKey(Node *ptr,int key);		//Find and returns the node with key
		Node* insert(Node* ptr,int key);		//Insert key into tree/subtree with root ptr
		Node* remove(Node *ptr,int key);		//Remove a node with key from the tree/subtree with root
		void printInorder(Node* ptr);			//Traverse (inroder) and print the key of a tree/subtree with root ptr
		void printTree();						//Print 2D Tree
	public:	//helper methods
		void insert_helper(int key);				//Helper method for insert method
		void remove_helper(int key);				//Helper method for remove method
	private:
		void printTreeHelper(int *A, bool *B, Node *ptr, int n); //Helper method for PrintTree()
};

//==========================================================
void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"display            :Display the BST Tree"<<endl
		<<"height             :Find the hieght of the Tree"<<endl
		<<"min                :Find the node with minimum key in BST"<<endl
		<<"max                :Find the node with maximum key in BST"<<endl
		<<"find <key>         :Find a node with a given key value in BST"<<endl
		<<"insert <key>       :Insert a new node in BST"<<endl
		<<"remove <key>       :Remove the node from BST "<<endl
		<<"inorder            :Print the BST in Inorder"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}
//==========================================================
void demo( BST &myBST)
{
	myBST.insert_helper(10);
	myBST.insert_helper(5);
	myBST.insert_helper(4);
	myBST.insert_helper(7);
	myBST.insert_helper(13);
	myBST.insert_helper(15);
	myBST.insert_helper(12);
	myBST.insert_helper(14);
	myBST.printTree();
}
//==========================================================
int main(void)
{
	BST myBST;
	listCommands();
	string user_input;
	string command;
	string key;

	while(true)
	{
		cout<<">";
		getline(cin,user_input);

		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,key);
		
		Node* root = myBST.getRoot();	//get the root of the tree
		cout<<"----------------------------------"<<endl;
		if( user_input =="display")	myBST.printTree();
		else if( command =="height")	cout<<"Height = "<<myBST.height(root)<<endl;
		else if( command =="min")	
		{
			Node* min = myBST.findMin(root);
			cout<<"Min. key = "<<((min!=nullptr)? to_string(min->getKey()):" does not exist")<<endl;
		}
		else if( command =="max")	
		{
			Node* max = myBST.findMax(root);
			cout<<"Max. key = "<<((max!=nullptr)? to_string(max->getKey()):" does not exist")<<endl;
		}
		else if( command =="find")	cout<<key<<(myBST.findKey(root,stoi(key))==nullptr ? " not found":" found")<<endl;
		else if( command =="insert" or command=="i")	{ myBST.insert_helper(stoi(key)); myBST.printTree();} 
		else if( command =="remove" or command=="r")	{ myBST.remove_helper(stoi(key)); myBST.printTree();}
		else if( command =="inorder")	{myBST.printInorder(root); cout<<endl;}
		else if( command =="exit") break;
		else if( command == "demo") demo(myBST); 
		else if( command == "help") listCommands();
		else if( command == "exit") break;
		else cout<<"Invalid command !!!"<<endl;

	}

	return 0;
}
//=====================================================================

BST::BST()
{
	this->root=nullptr;
}
BST::~BST()
{
	//Keep removing the root of the tree untill it becomes empty
	while(root)
		root=remove(root,root->key);
}
//Helper method for insert method
void BST::insert_helper(int key)
{	
	root = insert(root,key);
}
//=================================================
//Helper method for remove 
void BST::remove_helper(int key)
{
	root = del(root, key);
}
//==================================================================
//  This method prints a Binary Tree in 2D format
//  Created by Saurabh Ray 
//  Copyright © 2020 Saurabh Ray. All rights reserved.

void BST::printTree(){
   char *space = (char *) "  ";
   int d = height(this->getRoot());
   int n = (1<<(d+1))- 1; // n = 2^(d+1)-1

   int *A = new int[n];
   bool *B = new bool[n];
   for(int i=0; i<n; ++i) 
   	  B[i]=false;

   printTreeHelper(A,B,root,n);

   cout<<"\nTree:"<<endl;
   for(int t=(n+1)/2; t>0; t=t/2){
        for(int j=0; j<n; j++){
            if( ((j+1)%t == 0) && B[j]){
                cout<<A[j];
                B[j] = false;
            }
            else{
                cout<<space;
            }
        }
        cout<<endl;
   }
   cout<<endl;
   delete [] A;
   delete [] B;
}

void BST::printTreeHelper(int *A,bool *B, Node *ptr, int n){
    if(ptr!=nullptr){
        int mid = (n-1)/2;
        A[mid] = ptr->key;
        B[mid] = true;
        printTreeHelper(A,B,ptr->left,mid);
        printTreeHelper(A+(mid+1),B+(mid+1), ptr->right, mid);
    }
}

//returns the root
Node* BST::getRoot(){
	return root;
}


int BST::height(Node* ptr){

	//For when the tree is empty
	if(ptr == NULL) return 0;

	//if the node is a leaf node return 0.
	else if(ptr->left == NULL && ptr->right == NULL){
		return 0;
	}
	//return the max of the height of the left of the root or the right of the root.
	return 1+max(height(ptr->left),height(ptr->right));

}


Node* BST::findMin(Node *ptr){
	//if pointer is not the most left handed node, recursively call findMin with ptr->left, otherwise return the node.
	if(ptr->left == NULL){
		return ptr;
	}
	else{
		return findMin(ptr->left);
	}
}

Node* BST::findMax(Node *ptr){
	//if pointer is not the most right handed node, recursively call findMax with ptr->right, otherwise return the node.
	if(ptr->right == NULL){
		return ptr;
	}
	else{
		return findMax(ptr->right);
	}
}

Node* BST::findKey(Node *ptr, int key){
	//if the bottom of the tree if reached without finding the key, return null.
	if(ptr == NULL){
		return NULL;
	}
	//if the node found is equal to the key return the node.
	if(ptr->key == key){
		return ptr;
	}
	//if key is greater then the key of the pointer, recursively call the finKey method using the right hand side of the ptr Node.
	else if(key > ptr->key){
		return findKey(ptr->right, key);
	}
	//if key is smaller then the key of the pointer, recursively call the finKey method using the left hand side of the ptr Node.
	else {
		return findKey(ptr->left, key);
	}

}	

Node* BST::insert(Node* ptr,int key){
	//if ptr is NULL
	if(ptr == NULL){
		Node* newNode = new Node(key);
		return newNode;
	}
	//If a node is reached with the same key value, return messege.
	else if(ptr->key == key){
		cout<<"You can not have duplicate keys."<<endl;
	}
	//if key is greater then the node key, recursively call the insert method with the right side of the node. Redefine the edges.
	else if(key > ptr->key){
		Node* connection = insert(ptr->right, key);
		ptr->right = connection;
	}
	//if key is smaller then the node key, recursively call the insert method with the left side of the node. Redefine the edges.
	else if(key < ptr->key){
		Node* connection = insert(ptr->left, key);
		ptr->left = connection;
	}

	return ptr;

}

Node* BST::remove(Node *ptr, int key){

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
	return ptr;

}

void BST::printInorder(Node* ptr){
	//unless pointer->left is null, printInOrder the left node. 
	if(ptr->left != NULL) printInorder(ptr->left);
	//print the node key
	cout<<ptr->key<< " ";
	//unless pointer->right is null, printInOrder the right node. 
	if(ptr->right != NULL) printInorder(ptr->right);
}


