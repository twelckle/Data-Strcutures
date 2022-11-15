#include <iostream>
#include "myvector.h"
#include "contact.h"
using namespace std;

//Constructor
template <class T>
MyVector<T>::MyVector(){
	capacity = 1;
	n = 0;
	A = new T*[1];
}

//Another Constructor
template <class T>
MyVector<T>::MyVector(T* elem){
	capacity = 1;
	n = 1;
	A = new T*[1];
	A[0] = elem;
}

//Destructor
template <class T>
MyVector<T>::~MyVector(){
	for(int i = 0; i<n; i++){
		delete A[i];
	}
	delete[] A;
}

//returns size of vector
template <class T>
int MyVector<T>::size(){
	return n;
}

//returns if vector is empty
template <class T>
bool MyVector<T>::empty(){
	return n == 0;
}

//gives the contact object in index i.
template <class T>
T& MyVector<T>::operator[](int index){
	return *(A[index]);
}

//returns pointer to the contact obejct in index i
template <class T>
T* MyVector<T>::object(int i){
	return A[i];
}

//erases contact object at index "index" then moves all other indexs up so there are no gaps in the vector.
template <class T>
void MyVector<T>::erase(int index){
	delete A[index];
	for(int i=index; i<n; i++){
		A[i] = A[i+1];
	}
	n--;
}

//inserts contact element into the vector.
template <class T>
void MyVector<T>::insert(T* element){
	if(n >= capacity) reserve();
	A[n] = element;
	n++;
}

//if vector runs out of space, this function amoritizes the space and expands the vector by 2. O(n) average time.
template <class T>
void MyVector<T>::reserve(){
	T** newArray = new T*[capacity*2];
	
	for(int i=0; i<capacity; i++){
		newArray[i] = A[i];
	}
 
	delete[] A;
	A = newArray;
	capacity *= 2;

}

//goes through each contact element in the vector and call the print function. This is for edit and delete. 
template <class T>
void MyVector<T>::print(){
	for(int i = 0; i<n; i++){
		cout<<i+1<<") ";
		A[i]->print();
	}
}

//This Prints the list withough the number. Need this for the printASC, printDSC.
template <class T>
void MyVector<T>::printList(){
	for(int i = 0; i<n; i++){
		A[i]->print();
	}
}

//Need a special print function for printing to the file. 
template<class T>
void MyVector<T>::printListForExport(ofstream& output){
		for(int i = 0; i<n; i++){
		A[i]->printForExport(output);
	}
}

//checks to see if the element in the vector is a favorite. If it is then it is printed. 
template <class T>
void MyVector<T>::printFav(){
	for(int i = 0; i<n; i++){
		if(A[i]->getFav() == true){
			A[i]->print();
		}
	}
}


template class MyVector<Contact>;