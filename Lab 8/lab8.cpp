
//============================================================================
// Name         : lab8.cpp
// Author       : 
// Version      : 1.0
// Date Created : 
// Date Modified: 
// Copyright    : All rights are reserved
// Description  : Custom iterator for Doubly Linked List class
//============================================================================
#include<iostream>
#include<iomanip>
#include<algorithm>


using namespace std;

template <typename T>
class Node
{
	private:
		T elem; //data element 
		Node* next; //Link (pointer) to the next Node
		Node* prev; //Link (pointer) to the previous Node
		template <typename T2> friend class DoublyLinkedList;
		
	public:
		Node(): next(NULL), prev(NULL)
		{}
		Node(T elem) : elem(elem),next(NULL), prev(NULL)
		{}
};
//==============================================================
template <typename T> 
class DoublyLinkedList
{
	private:
		Node<T>* head; 	// pointer to the head of List
		Node<T>* tail; 	// pointer to the tail of List
	public:
		DoublyLinkedList (); // empty list constructor
		~DoublyLinkedList (); // destructor to clean up all nodes
		bool empty() const; // is list empty?
		const T& front() const; // get the value (element) from front Node<T> of list
		const T& back() const;  // get the value (element) from last Node<T> of the List 
		void addBefore(Node<T> *ptr, const T& elem);	 //add a new node before ptr
		void addFront(const T& elem); // add a new node to the front of list
		void addBack(const T & elem); //add a new node to the back of the list
		void removeFront(); // remove front node from list
		void removeBack();  // remove last node from list
		void reverseList();	// reverse the list
		bool isPalindrome(); //check if the List is Palindrome or not
		void display() const;	// display all element of the list
		//Iterator
		class iterator;   //Forwarding declarion of iterator class
		iterator begin()  
		{
			return iterator(head->next);
		}
		iterator end()
		{
			return iterator(tail);
		}

		class iterator
		{
			private:
				Node<T>* ptr;

			public:
				using iterator_category = bidirectional_iterator_tag;
				using value_type = Node<T>;
				using pointer = Node<T>*;
				using reference = Node<T>&; 
				using difference_type = ptrdiff_t;
			public:
				iterator(Node<T>* ptr){
					this->ptr = ptr;
				}
				T operator*(){
					return ptr->elem;
				}

				iterator& operator++(){
					ptr = ptr->next;
					return *this;
				}


				iterator& operator--(){
					ptr = ptr->prev;
					return *this;
				}

				bool operator==(const iterator& other) const{

					return this->ptr->elem == other.ptr->elem;
					
				}

				bool operator!=(const iterator& other) const{

					return this->ptr->elem != other.ptr->elem;

				}

				
		};
};
//===========================================================
int main()
{
	DoublyLinkedList<int> myList;

	for(int i=1; i<=10; i++)
		myList.addBack(i*10);
	
	DoublyLinkedList<int>::iterator it = myList.begin();
	while(it != myList.end())
	{
		cout<<*it<<"->";
		++it;
	}

	cout<<endl;

	for(auto it:myList)
		cout<<it<<"->";
	cout<<endl; 

	it=myList.begin();
	advance(it,3);
	--it;


	int array[10];
	copy(myList.begin(),myList.end(),array);

	for(int i=0; i<10; i++)
		cout<<array[i]<<" ";

	cout<<endl;

	return 0;
}
//===========================================================
template <typename T>
DoublyLinkedList<T>::DoublyLinkedList ()
{
	this->head = new Node<T>();
	this->tail = new Node<T>();
	this->head->next = tail;
	this->tail->prev = head;
}
//============================================================
template <typename T>
DoublyLinkedList<T>::~DoublyLinkedList () // destructor to clean up all nodes
{
	while(!empty())
		removeFront();
}
//============================================================
template <typename T>
bool DoublyLinkedList<T>::empty() const // is list empty?
{
	return this->head->next == tail;
}
//============================================================
template <typename T>
const T& DoublyLinkedList<T>::front() const // get front element
{
	if(!empty())
		return this->head->next->elem;
	else
		throw runtime_error("List is Empty");
}
//============================================================
template <typename T>
const T& DoublyLinkedList<T>::back() const // get front element
{
	if(!empty())
		return this->tail->prev->elem;
	else
		throw runtime_error("List is Empty");
}
//============================================================
template <typename T>
void DoublyLinkedList<T>::addBefore(Node<T> *ptr, const T& elem)
{
	Node<T> *tmp = new Node<T>(elem);
	tmp->next = ptr;
	tmp->prev = ptr->prev;
	ptr->prev->next = tmp;
	ptr->prev=tmp;
}
//============================================================
template <typename T>
void DoublyLinkedList<T>::addFront(const T& elem) // add to front of list
{
	addBefore(this->head->next, elem);
}
//============================================================
template <typename T>
void DoublyLinkedList<T>::addBack(const T& elem) // add to Back of the list
{
	addBefore(this->tail, elem);
}
//============================================================
template <typename T>
void DoublyLinkedList<T>::removeFront() // remove front item from list
{
	if(!empty())
	{
		Node<T> *tmp = this->head->next;
		this->head->next = tmp->next;
		tmp->next->prev = head;
		delete tmp;
	}
}
//============================================================
template <typename T>
void DoublyLinkedList<T>::removeBack() // remove last item from list
{
	if(!empty())
	{
		Node<T> *tmp = this->tail->prev;
		this->tail->prev = tmp->prev;
		tmp->prev->next = tail;
		delete tmp;
	}
}
//============================================================
template <typename T>
void DoublyLinkedList<T>::display() const
{
	Node<T> *curr=head;
	while(curr!=NULL)
	{
		cout<<"+------";
		curr=curr->next;
	}
	cout<<"+"<<endl<<"|";
	curr=head;
	while(curr!=NULL)
	{
		if (curr == head)		cout<<" Head |";
		else if(curr == tail)	cout<<" Tail |";
		else 					cout<<setw(5)<<curr->elem<<" |";
	
		curr=curr->next;
	}
	curr=head;
	cout<<endl;
	while(curr!=NULL)
	{
		cout<<"+------";
		curr=curr->next;
	}
	cout<<"+"<<endl;
}