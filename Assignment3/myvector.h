#ifndef MyVector_H
#define MyVector_H

#include <iostream>
#include<fstream>
#include "contact.h"
using namespace std;

template <class T>
class MyVector
{
	private:
		int capacity;
		int n;
		T** A;

	public:
		MyVector(); //Constructor
		MyVector(T* elem); //Constructor
		~MyVector(); //Destructor
		int size(); //returns size
		bool empty(); //returns if empty
		T* object(int i); //returns pointer to object at index i
		T& operator[](int index); //returns object at index "index"
		void erase(int index); //erases the object in the vector at index "index"
		void insert(T* element); //inserts element into the vector
		void reserve(); //amoritize space for vector
		//4 prints for different uses
		void print(); 
		void printList();
		void printListForExport(ofstream& output);
		void printFav();
};


#endif