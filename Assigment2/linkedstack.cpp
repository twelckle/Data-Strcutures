#include<string>
#include "linkedstack.h"
#include"linkedlist1.h"
#include"fitness.h"

using namespace std;



template <class T> LinkedStack<T>::LinkedStack(){
	S = LinkedList1<T>();
	n = 0;
}


template <class T> bool LinkedStack<T>::empty() const{
	return n == 0;
}

template <class T> int LinkedStack<T>::size() const{
	return n;
}

template <class T> Node<T>* LinkedStack<T>::top() const throw(StackEmpty){
	if(empty()) throw StackEmpty();
	return S.front();
}

template <class T> void LinkedStack<T>::push(T e){
	S.addFront(e);
	n++;
}

template <class T> void LinkedStack<T>::pop() throw(StackEmpty){
	if(empty()) throw StackEmpty();
	S.removeFront();
	n--;
}


template <class T> void LinkedStack<T>::deleteNode(Node<T>* node){
	if(empty()) throw StackEmpty();
	S.removeNode(node);
	n--;
}

template <class T> LinkedList1<T> LinkedStack<T>::getS(){return S;}
template <class T> int LinkedStack<T>::getn(){return n;}


template class LinkedStack<int>;