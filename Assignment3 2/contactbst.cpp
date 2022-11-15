#include<iostream>
#include<fstream>
#include<string>
#include "contactbst.h"
#include "contact.h"
#include "myvector.h"
using namespace std;

//Constructor
Node::Node(string key, MyVector<Contact>* contactVector){
	this->key = key;
	this->contactVector = contactVector;
	left = NULL;
	right = NULL;
}

//Destructor
Node::~Node(){
	delete contactVector;
}

//If the node is internal
bool Node::isInternal(){
	return (left != NULL or right != NULL);
}

//Constructor
ContactBST::ContactBST(){
	root = NULL;
}

//Destructor
ContactBST::~ContactBST(){
	while(root){
		root = del(root, root->getKey());
	}
}

Node* ContactBST::getRoot(){
	return root;
}

//Import CSV and adds data to the BST tree. 
int ContactBST::importCSV(Node* ptr, string path){
	int numberOfImports = 0;
	ifstream myFile;

	myFile.open(path);
	if(myFile.good() == false) return -1;
	while(myFile.good()){

		//variables and getline functions needed to read each line of the CSV file.
		Contact* newContact;
		string fname;
		string lname;
		string email;
		string primaryPhone;
		string city;
		string country;
		string isFav;
		string empty;
		bool isFavBool;

		getline(myFile, fname,',');
		getline(myFile, lname,',');
		getline(myFile, email,',');
		getline(myFile, primaryPhone,',');
		getline(myFile, city,',');
		getline(myFile, country,',');
		getline(myFile, isFav, '\n'); 

		//if name is empty then don't add it to the tree
		if(fname == "") continue;

		//change string to int and see if the contact is a favorite or not.
		if(stoi(isFav) == 1) isFavBool = true;
		else if (stoi(isFav) == 0) isFavBool = false;


		//create new contact, new key and insert into tree.
		newContact = new Contact(fname, lname, email, primaryPhone, city, country, isFavBool);
		string key = fname + lname;
		insert_helper(key, newContact);
		numberOfImports++;
	
	}
	myFile.close();
	return numberOfImports;
}

//export to a CSV file.
int ContactBST::exportCSV(Node* ptr, string path){
	int numberOfExports = 0;

	//open the file, and print to the file in ASC order. Keep track of number of Exports
	ofstream myFile;
	myFile.open(path);
	if(myFile.is_open()){
		printASCForExport(ptr, myFile, &numberOfExports);
		return numberOfExports; 
	}
	//return -1 if the file does not open.
	else{
		return -1;
	}

}

void ContactBST::insert_helper(string key, Contact* data){
	root = add(getRoot(), key, data);
}

Contact* ContactBST::contactUpdate(Node* ptr, int* index){
	//If there are multiple keys we must find the contact that needs to be updated within the vector. 
	if(ptr->getData()->size() > 1){
		bool continueLoop = true;
		string input;
		string empty;
		ptr->getData()->print();

		//loop ensures that no incorrect user inputs are given
		while(continueLoop){
			cout<<"Which would you like to edit: "<<endl;
			cout<<">";
			cin>>input;
			for(int i = 0; i<ptr->getData()->size(); i++){
				if(input == to_string(i+1)){
					continueLoop = false;
					break;
				}
			}
			if(continueLoop) cout<<"Please enter one of the numbers"<<endl;
		}
		cout<<endl;
		getline(cin,empty);
		*index = stoi(input)-1;
		return ptr->getData()->object(stoi(input)-1);
	}
	//if there is only one object in the vector, just return the first object in the vector.
	return ptr->getData()->object(0);
}

Node* ContactBST::update(Node* ptr, string key){
	//see if the node exist. 
	Node* workingNode = search(ptr, key);
	if(workingNode == NULL) return ptr;
	int index = 0;

	//find the contact pointer that must be updated
	Contact* workingContact = contactUpdate(workingNode, &index);


	//Loop to determine what to update
	string input;
	string empty;
	while(true){
		cout<<"1) First Name"<<endl;
		cout<<"2) Last Name"<<endl;
		cout<<"3) Email"<<endl;
		cout<<"4) Phone Number"<<endl;
		cout<<"5) City"<<endl;
		cout<<"6) Country"<<endl;
		cout<<"What field do you want to edit"<<endl;
		cout<<">";
		cin>>input;
		if(input != "1" and input != "2" and input != "3" and input != "4" and input != "5" and input != "6"){
			cout<<"Invalid Input"<<endl;
		}
		else break;
	}

	//if First name is updated. Create new Contact pointer and add it to the tree. Delete the old contact. 
	if(input == "1"){
		workingContact->setFirstName();
		Contact* newContact = new Contact(*workingContact);
		if(workingNode->getData()->size()>1){
			workingNode->getData()->erase(index);
			add(root,newContact->getKey(), newContact);
		}
		else{
			add(root,newContact->getKey(), newContact);
			remove_helper(key);
		}

	}
	//if Last name is updated. Create new Contact pointer and add it to the tree. Delete the old contact. 
	else if(input == "2"){
		workingContact->setLastName();
		Contact* newContact = new Contact(*workingContact);
		if(workingNode->getData()->size()>1){
			workingNode->getData()->erase(index);
			add(root,newContact->getKey(), newContact);
		}
		else{
			add(root,newContact->getKey(), newContact);
			remove_helper(key);
		}

	}
	//if non key elements are changed, just change the contact. 
	else if(input == "3") workingContact->setEmail();
	else if(input == "4") workingContact->setPhone();
	else if(input == "5") workingContact->setCity();
	else if(input == "6") workingContact->setCountry();
	
	getline(cin,empty);
	cout<<"Succesfully Updated"<<endl;
	return root;
}

Node* ContactBST::add(Node* ptr,string key, Contact* data){
	//if bottom of the tree is found, then insert a new node with the specified key and contact data.
	if(ptr == NULL){
		MyVector<Contact>* newVector = new MyVector<Contact>(data);
		Node* newNode = new Node(key, newVector);
		return newNode;
	}
	//if key is already found in the tree, add contact data to the existing vecotr
	else if(ptr->getKey()==key){
		ptr->getData()->insert(data);
		return ptr;
	}
	//if key is smaller then the current node, then move left on the tree.
	else if(key<ptr->getKey()){
		Node* connection = add(ptr->left, key, data);
		ptr->left = connection;
	}
	//if key is bigger then the current node, then move right on the tree
	else if(key>ptr->getKey()){
		Node* connection = add(ptr->right, key, data);
		ptr->right = connection;
	}

	return ptr;
}

//minimum value on the tree.
Node* ContactBST::findMin(Node* ptr){
	if(ptr->left == NULL) return ptr;
	else return findMin(ptr->left);
}

//loop that ensures what contact is being updated in the vector, then updates that contact. 
bool ContactBST::checkInput(Node* ptr){
	//determines if there is more then one contact object in the vector. 
	if(ptr->getData()->size() > 1){
		bool continueLoop = true;
		string input;
		string empty;
		//prints out all the possible objects in the vecotr
		ptr->getData()->print();
		//loop to determine which object to delete
		while(continueLoop){
			cout<<"Which would you like to delete: "<<endl;
			cout<<">";
			cin>>input;
			for(int i = 0; i<ptr->getData()->size(); i++){
				if(input == to_string(i+1)){
					continueLoop = false;
					break;
				}
			}
			if(continueLoop) cout<<"Please enter one of the numbers"<<endl;
		}
		getline(cin, empty);
		//erase that object 
		ptr->getData()->erase(stoi(input)-1);
		return true;
	}
	return false;
}

Node* ContactBST::del(Node* ptr,string key){
	//check if bottom of the tree is reached.
	if(ptr == NULL) cout<<"This contact does not exist in the system"<<endl;

	//if key is greater. Check the right side of tree
	else if(key>ptr->getKey()){
		Node* connection = del(ptr->right, key);
		ptr->right = connection;
	}

	//if key is smaller check the left side of tree.
	else if(key<ptr->getKey()){
		Node* connection = del(ptr->left, key);
		ptr->left = connection;
	}
	//key is found
	else{
		//if leaf delete and return null
		if(ptr->left == NULL && ptr->right == NULL){
			if(checkInput(ptr)) return ptr;
			else{
				delete ptr;
				return NULL;
			}
		}
		//if only left node then return the left node and delete the node with the key
		else if(ptr->right == NULL){
			if(checkInput(ptr)) return ptr;
			else{
				Node* returnNode = ptr->left;
				delete ptr;
				return returnNode;
			}
		}
		//if only right node then return the right node and delete the node with the key
		else if(ptr->left == NULL){
			if(checkInput(ptr)) return ptr;
			else{
				Node* returnNode = ptr->right;
				delete ptr;
				return returnNode;
			}
		}
		//if node is an internal node. Find the minimum of the right side of the subtree. Swap values and delete the the swapped value.
		else{
			if(checkInput(ptr)) return ptr;	
			else{
				Node* replaceNode = findMin(ptr->right);
				MyVector<Contact>* temp = replaceNode->getData();
				replaceNode->setData(ptr->getData());
				ptr->setData(temp);

				Node* connection = del(ptr->right, replaceNode->getKey());
				ptr->right = connection;
			}
		}

	}
	return ptr;
}

void ContactBST::remove_helper(string key){
	root = del(root, key);
}


Node* ContactBST::search(Node* ptr,string key){
	//if null node is not found. if found return ptr. 
	//if key is bigger check right side of tree. if key is smaller check left side of tree
	if(ptr == NULL) cout<<"This contact does not exist"<<endl;
	else if(ptr->getKey() == key) return ptr;
	else if(key>ptr->getKey()) return search(ptr->right, key);
	else if(key<ptr->getKey()) return search(ptr->left, key);
	return NULL;
}


bool ContactBST::markFav(Node* ptr, string key){
	//see if node exists
	Node* favoriteNode = search(ptr, key);
	if(favoriteNode != NULL){
		string input;
		string empty;
		//see if the vector of objects is greater then 1. determine the index of the object in the vector the user wants to mark as favorite
		if(favoriteNode->getData()->size() > 1){
			bool continueLoop = true;
			favoriteNode->getData()->print();
			//loop ensures that there are no bad inputs by user.
			while(continueLoop){
				cout<<">";
				cin>>input;
				for(int i = 0; i<favoriteNode->getData()->size(); i++){
					if(input == to_string(i+1)){
						continueLoop = false;
						break;
					}
				}
				if(continueLoop) cout<<"Please enter one of the numbers"<<endl;
			}
			getline(cin,empty);
		}
		else input = "1";
		//change the contact favorite value to true.
		favoriteNode->getData()->object(stoi(input)-1)->setFav(true);
		cout<<"Succesfully marked as favorite"<<endl;
		return true;
	}
	else return false;
}

bool ContactBST::unmarkFav(Node* ptr, string key){
	//see if node exists
	Node* favoriteNode = search(ptr, key);
	if(favoriteNode != NULL){
		string input;
		string empty;
		//see if the vector of objects is greater then 1. determine the index of the object in the vector the user wants to unmark as favorite
		if(favoriteNode->getData()->size() > 1){
			bool continueLoop = true;
			favoriteNode->getData()->print();
			//loop ensures that there are no bad inputs by user.
			while(continueLoop){
				cout<<">";
				cin>>input;
				for(int i = 0; i<favoriteNode->getData()->size(); i++){
					if(input == to_string(i+1)){
						continueLoop = false;
						break;
					}
				}
				if(continueLoop) cout<<"Please enter one of the numbers"<<endl;
			}
			getline(cin,empty);
		}
		else input = "1";
		//change the contact favorite value to true.
		favoriteNode->getData()->object(stoi(input)-1)->setFav(false);
		cout<<"Succesfully marked as not a favorite"<<endl;
		return true;
	}
	else return false;
}

//This is inorder traversal that prints out the objects in ASC order.
void ContactBST::printASC(Node* ptr){

	if(ptr->isInternal() && ptr->left != NULL) printASC(ptr->left);
	ptr->getData()->printList();
	if(ptr->isInternal() && ptr->right != NULL) printASC(ptr->right);
}

//This is inorder traversal that prints out the objects in ASC order into the file name specified in the parameters.
void ContactBST::printASCForExport(Node* ptr, ofstream& output, int* exportNumber){
	if(ptr->isInternal() && ptr->left != NULL) printASCForExport(ptr->left, output, exportNumber);
	ptr->getData()->printListForExport(output);
	*exportNumber = *(exportNumber)+1;
	if(ptr->isInternal() && ptr->right != NULL) printASCForExport(ptr->right, output, exportNumber);
}

//This is inorder traversal that prints out the objects in DSC order.
void ContactBST::printDES(Node* ptr){
	if(ptr->isInternal() && ptr->right != NULL) printDES(ptr->right);
	ptr->getData()->printList();
	if(ptr->isInternal() && ptr->left != NULL) printDES(ptr->left);
}

//This is inorder traversal that prints out the objects in ASC order that are Favorites.
void ContactBST::printFav(Node* ptr){

	if(ptr->isInternal() && ptr->left != NULL) printFav(ptr->left);
	ptr->getData()->printFav();
	if(ptr->isInternal() && ptr->right != NULL) printFav(ptr->right);
}
