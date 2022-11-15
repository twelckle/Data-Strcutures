#ifndef LINKEDSTACK
#define LINKEDSTACK

#include<string>
#include"linkedlist1.h"
#include"fitness.h"

using namespace std;
template <class T> class LinkedStack;

class StackEmpty:public exception{
	public:
		virtual const char* what() const throw(){
			return("Stack is Empty");
		}

};

template <class T>
class LinkedStack{
	private:
		LinkedList1<T> S;
		int n;
	public:
		LinkedStack();
		bool empty() const; 
		int size() const;
		Node<T>* top() const throw(StackEmpty);
		void push(T e);
		void pop() throw(StackEmpty);
		void deleteNode(Node<T>* node);
		LinkedList1<T> getS();
		int getn();


};

#endif