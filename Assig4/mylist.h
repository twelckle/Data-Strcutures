#ifndef MY_LIST_H
#define MY_LIST_H

#include<iostream>
#include "flighthashtable.h"
using namespace std;

template <typename T>
class MyList;

template <class T>
class Node{
	private:
		Node* next;
		Node* prev;
		T* elem;
	public:
		Node(T* elem){
			next = NULL;
			prev = NULL;
			this->elem = elem;
		}
		Node(){
			next = NULL;
			prev = NULL;
		}
	friend class MyList<T>;
};

template <class T>
class MyList
{
	private:
		Node<T>* head;
		Node<T>* trailer;
	public:
		MyList(); //constructor
		~MyList(); //deconstructor
		bool empty(); //if empty
		Node<T>* front(); //returns front node
		void addFront(T* elem); //adds to the front of list
		void addBack(T* elem); //adds to back of list
		void add(T* elem); //adds element to the list
		void print(); //prints all elements in the list.
		void printForFind(); //prints all elements in a certain format
		void remove(Node<T>* deleteNode); //removes element from list
		void removeFront(); //removes front element from list
		void removeBack(); //removes back element from list
		void removeFromList(); //decides what element to delete from list. Requires USER input.
		bool printDate(string date); //checks to see if user input date matches dates in the list. Prints if true. 
		bool checkIfSame(Flight_Ticket* data); //checks if the parameter Flight_ticket exists in teh list. 
		int printToFile(ofstream& output); //calls the print to export file for each element in the list. 
};

#endif
