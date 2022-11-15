#include <iostream>
#include <fstream>
#include "mylist.h"
#include "flighthashtable.h"
using namespace std;

//constructor
template <class T>
MyList<T>::MyList(){
	head = new Node<T>();
	trailer = new Node<T>();
	head->next = trailer;
	trailer->prev = head;
}

//deconstructor
template <class T>
MyList<T>::~MyList(){
	while(!empty()){
		removeFront();
	}
}

//check if empty
template <class T>
bool MyList<T>::empty(){
	return (head->next == trailer);
}


//front node.
template <class T>
Node<T>* MyList<T>::front(){
	return head;
}

//add to front
template <class T>
void MyList<T>::addFront(T* elem){
	Node<T>* newNode = new Node<T>(elem);
	Node<T>* temp = head->next;
	head->next = newNode;
	newNode->next = temp;
	temp->prev = newNode;
	newNode->prev = head;
}

//add to back
template <class T>
void MyList<T>::addBack(T* elem){
	Node<T>* newNode = new Node<T>(elem);
	Node<T>* temp = trailer->prev;
	trailer->prev = newNode;
	newNode->prev = temp;
	temp->next = newNode;
	newNode->next = trailer;

}

//this adds the node in ascneding order based on country of desintiation. This makes sure that all the lists are already sorted.
template<class T>
void MyList<T>::add(T* elem){
	if(head->next == trailer) addFront(elem);
	else{
		Node<T>* newNode = new Node<T>(elem);
		Node<T>* compareNode = head->next;
		//This adds the object in a sorted manner depedning on the country of destintation. 
		while(compareNode != trailer and compareNode->elem->getValue().getCountry_of_destination() < newNode->elem->getValue().getCountry_of_destination()){
			compareNode = compareNode->next;
		}
		//adds to front, back, or in the correct position.
		if(compareNode == head->next) addFront(elem);
		else if(compareNode == trailer->prev) addBack(elem);
		else{
			newNode->next = compareNode; 
			newNode->prev = compareNode->prev;  
			compareNode->prev->next = newNode; 
			compareNode->prev = newNode;
		}
	}
	
}

//prints all elements in the list.
template <class T>
void MyList<T>::print(){
	Node<T>* nextElem = head->next;
	while(nextElem != trailer){
		nextElem->elem->print();
		nextElem = nextElem->next;
	}
}

//Prints all elements in list. This is called for the find feature.
template <class T>
void MyList<T>::printForFind(){
	Node<T>* nextElem = head->next;
	cout<<endl;
	int number = 1;
	while(nextElem != trailer){
		cout<<number<<") ";
		number++;
		nextElem->elem->printForFind();
		cout<<endl;
		nextElem = nextElem->next;
	}
}

//this deletes a node in the list. 
template <class T>
void MyList<T>::remove(Node<T>* deleteNode){
	if(deleteNode == head->next) removeFront();
	else if(deleteNode == trailer->prev) removeBack();
	else{
		Node<T>* nextNode = deleteNode->next;
		Node<T>* prevNode = deleteNode->prev;
		prevNode->next = nextNode;
		nextNode->prev = prevNode;
		delete deleteNode;
	}
}

//removes the front node in the list.
template <class T>
void MyList<T>::removeFront(){

	Node<T>* destroyNode = head->next;
	head->next = destroyNode->next;
	destroyNode->next->prev = head;
	delete destroyNode;
}

//removes the back node in the list.
template <class T>
void MyList<T>::removeBack(){

	Node<T>* destroyNode = trailer->prev;
	trailer->prev = destroyNode->prev;
	destroyNode->prev->next = trailer;
	delete destroyNode;
}

//This is called to figure out which object in the list the user wants to delete. Depedning on their input the correct object is 
//deleted from the list. 
template <class T>
void MyList<T>::removeFromList(){
	bool continueLoop = true;
	string input;
	Node<T>* firstNode = head->next;
	int number = 1;
	while(firstNode != trailer){
		cout<<number<<") ";
		firstNode->elem->print();
		firstNode = firstNode->next;
		number++;
	}
	//this loop figures out which object the user wants to delete. 
	while(continueLoop){
		cout<<"Which would you like to edit: "<<endl;
		cout<<">";
		cin>>input;
		for(int i = 0; i<number; i++){
			if(input == to_string(i+1)){
				continueLoop = false;
				break;
			}
		}
		if(continueLoop) cout<<"Please enter one of the numbers"<<endl;
	}
	//depedning on user input the corresponding object is deleted. 
	Node<T>* deleteNode = head->next;
	for(int i = 0; i<stoi(input)-1;i++){
		deleteNode = deleteNode->next;
	}
	remove(deleteNode);
	cout<<"Successfully Delted!"<<endl;
	string catchValue;
	getline(cin, catchValue);
}


//this prints out the flightticket information is the date matches with the date in the parameter. 
template <class T>
bool MyList<T>::printDate(string date){
	bool printed = false;
	Node<T>* firstNode = head->next;
	while(firstNode != trailer){
		if(firstNode->elem->getDate() == date){
			firstNode->elem->print();
			printed = true;
		}
		firstNode = firstNode->next;
	}
	return printed;
}

//This checks if the parameter data is the same as a flightticket data in the list. 
template <class T>
bool MyList<T>::checkIfSame(Flight_Ticket* data){
	Node<T>* firstNode = head->next;
	while(firstNode != trailer){
		if(firstNode->elem->getValue() == *data) return false;
		firstNode = firstNode->next;
	}
	return true;
}

//This function prints every object in the list to the output file in the parameter. 
template <class T>
int MyList<T>::printToFile(ofstream& output){
	int returnIntValue = 0;
	Node<T>* firstNode = head->next;
	while(firstNode != trailer){
		firstNode->elem->getValue().printToFile(output);
		returnIntValue++;
		firstNode = firstNode->next;
	}
	return returnIntValue;
}

template class MyList<HashNode>;
template class Node<HashNode>;
