//============================================================================
// Name         : lab4.cpp
// Author       : Theo Welckle
// Version      : 1.0
// Date Created : Feb 15	
// Date Modified: Feb 18
// Copyright    : All rights are reserved
// Description  : Doubly LinkedList implementation in C++
//============================================================================
#include<iostream>
#include<string>
#include<sstream>
#include<iomanip>
#include<exception>
using namespace std;

class Node
{
	private:
		string elem; //data element (type string in this case)
		Node* next; //Link (pointer) to the next Node
		Node* prev; //Link (pointer) to the previous Node
		friend class DoublyLinkedList;
		
	public:
		Node(): next(NULL), prev(NULL)
		{}
		Node(string elem) : elem(elem), next(NULL), prev(NULL)
		{}
};
//==============================================================
class DoublyLinkedList
{
	private:
		Node* head; 	// pointer to the head of List
		Node* tail; 	// pointer to the tail of List
	public:
		DoublyLinkedList (); // empty list constructor
		~DoublyLinkedList (); // destructor to clean up all nodes
		bool empty() const; // is list empty?
		const string& front() const; // get the value (element) from front Node of list
		const string& back() const;  // get the value (element) from last Node of the List 
		void addBefore(Node *ptr, const string& elem);	 //add a new node before ptr
		void addFront(const string& elem); // add a new node to the front of list
		void addBack(const string & elem); //add a new node to the back of the list
		void removeFront(); // remove front node from list
		void removeBack();  // remove last node from list
		void reverseList();	// reverse the list
		bool isPalindrome(); //check if the List is Palindrome or not
		void display() const;	// display all element of the list
};
//===================================
void listCommands()
{
	cout<<"List of available Commands:"<<endl
		<<"display            : Display the Doubly Linkled List"<<endl
		<<"front              : Display the first element of the List"<<endl
		<<"back               : Display the last element of the List"<<endl
		<<"addFront <elem>    : Add a new Node at the begining of the List"<<endl
		<<"addBack  <elem>    : Add a new Node at the end of the List"<<endl
		<<"removeFront        : Remove the first Node of the Linked List"<<endl
		<<"removeBack         : Remove the last  Node of the Linked List"<<endl	
		<<"isempty            : Check if the List is empty?"<<endl
		<<"reverse            : Reverse the Linked List"<<endl
		<<"isPalindrome       : Check if the List is Palindrome or not?"<<endl
		<<"help               : Display the list of available commands"<<endl
		<<"exit               : Exit the Program"<<endl;
}
//===================================
int main()
{
	DoublyLinkedList myList;
	listCommands();
	string user_input;
	string command;
	string parameter;

	do
	{
		cout<<">";
		getline(cin,user_input);

		// parse userinput into command and parameter(s)
		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,parameter);
		
		try
		{
			if(command=="display") 				myList.display();
			else if(command=="front")			cout<<"Front = "<<myList.front()<<endl;
			else if(command=="back")			cout<<"Back = "<<myList.back()<<endl;
			else if(command=="addFront")		myList.addFront(parameter),myList.display();
			else if(command=="addBack")		 	myList.addBack(parameter),myList.display();
			else if(command=="removeFront")		myList.removeFront(),myList.display();
			else if(command=="removeBack")		myList.removeBack(),myList.display();
			else if(command=="isempty")			cout<<"List is "<<(myList.empty()? "Empty":"Not Empty")<<endl;
			else if(command=="reverse")			myList.reverseList(),myList.display();
			else if(command=="isPalindrome")	cout<<"List is "<<(myList.isPalindrome()? "Palindrome":"Not Palindrome")<<endl;
			else if(command == "help")			listCommands();
			else if(command == "exit")			break;
			else 								cout<<"Invalid Commad !!"<<endl;
		}
		catch(exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}

	}while(command!="exit" and command!="quit");

	return EXIT_SUCCESS;
}
//============================================================
DoublyLinkedList::DoublyLinkedList ()
{
	head = new Node();
	tail = new Node();

	head->next = tail;
	tail->prev = head;

}
//============================================================
DoublyLinkedList::~DoublyLinkedList () // destructor to clean up all nodes
{
	while(!empty()){
		removeFront();
	}
	delete head;
	delete tail;

}
//============================================================
bool DoublyLinkedList::empty() const // is list empty?
{
	return (head->next == tail); //return if head is not pointed at tail. 
}
//============================================================
const string& DoublyLinkedList::front() const // get front element
{
	return head->next->elem; //return value of the node head is pointed towards.
}
//============================================================
const string& DoublyLinkedList::back() const // get front element
{
	return tail->prev->elem; //return the value of the node tail is pointed towards.
}
//============================================================
void DoublyLinkedList::addBefore(Node *ptr, const string& elem)
{
	//1New node.
	Node* newNode = new Node(elem); //create instertion node. 
	newNode->next = ptr; //assign next to the node it is being inserted before
	newNode->prev = ptr->prev; //assign prev pointer of newNode to the prev pointer of the node its being inserted before. 

	//At this point no links between node ptr and its respective pointers have been manipulated.
	
	ptr->prev->next = newNode; //change the next pointer of newNode->prev (which is equal to ptr->prev) to newNode. 
	ptr->prev = newNode; //change node ptr prev to newNode
}
//============================================================
void DoublyLinkedList::addFront(const string& elem) // add to front of list
{
	//Create new Node and change the pointers(next, prev) of head and the pointers of node head->next
	Node* newNode = new Node(elem);
	Node* temp = head->next;
	head->next = newNode;
	newNode->next = temp;
	temp->prev = newNode;
	newNode->prev = head;

}
//============================================================
void DoublyLinkedList::addBack(const string& elem) // add to Back of the list
{
	//Create new Node and change the pointers(next, prev) of tail and the pointers of node tail->prev
	Node* newNode = new Node(elem);
	Node* temp = tail->prev;
	tail->prev = newNode;
	newNode->prev = temp;
	temp->next = newNode;
	newNode->next = tail;

}
//============================================================
void DoublyLinkedList::removeFront() // remove front item from list
{	
	//removing the front node, changing the next and prev of both head and the node destroyNode was pointing at.
	Node* destroyNode = head->next;
	head->next = destroyNode->next;
	destroyNode->next->prev = head;
	delete destroyNode;
}
//============================================================
void DoublyLinkedList::removeBack() // remove last item from list
{
	//removing the back node, changing the next and prev of both tail and the node destroyNode was pointing at.
	Node* destroyNode = tail->prev;
	tail->prev = destroyNode->prev;
	destroyNode->prev->next = tail;
	delete destroyNode;
}
//============================================================
void DoublyLinkedList::display() const
{
	Node *curr=head;
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
//============================================================
void DoublyLinkedList::reverseList()
{
	
	//After changing the pointers. I want to switch the original head and tail. 
	Node* initialHead = head; 
	Node* initialTail = tail;

	Node* workingNode = head;

	//For every Node object switch prev = next and next = prev.
	while(workingNode != NULL){ 
		Node* temp = workingNode->next;
		workingNode->next = workingNode->prev;
		workingNode->prev = temp;
		workingNode = workingNode->prev;
	}

	//switch head and tail.
	head = initialTail;
	tail = initialHead;

	
	
}
//============================================================
bool DoublyLinkedList::isPalindrome()
{
	Node* front = head;
	Node* back = tail;

	//loop from one side of the linked list to the other comparing values.
	//if objects are the same or front and back have passed each other this means the DLL is a palindrome 
	while(front != tail && front->prev != back->prev)
		if(head->next->elem == tail->prev->elem){
			front = front->next;
			back = back->prev;
		}
		else{
			return false;
		}

	return true;
}
