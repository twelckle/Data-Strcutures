//============================================================================
// Name         : main.cpp
// Author       : Theo Welckle
// Version      : 1.0
// Date Created : March 8
// Date Modified: March 13
// Copyright    : All rights are reserved
// Description  : Fitness Center 2
//============================================================================

#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<sstream>
using namespace std;



//excpetion class for linkedlist Stack.
class StackEmpty:public exception{
	public:
		virtual const char* what() const throw(){
			return("Stack is Empty");
		}

};

template<typename T> class LinkedList1;
class Member;
class FitnessClass;
template<typename T> class LinkedStack;
template<typename T> class Node;


//========================================== ADMIN ================================================================
class Admin{
	private:
		
		int ID;
		string firstName;
		string lastName;
		string userName;
		string password;

	public:
		Admin(int admID, string first, string last, string user, string pass);
		Admin();
		int getID();
		string getfirstName();
		string getlastName();
		string getuserName();
		string getpassword();

};



//========================================== MEMBER ================================================================
class Member{
	private:
		int ID;
		string firstName;
		string lastName;
		string userName;
		string password;
	public:
		Member(int memID, string first, string last, string user, string pass);
		Member();
		int getID();
		string getfirstName();
		string getlastName();
		string getuserName();
		string getpassword();

};

//========================================== FitnessClass ================================================================
class FitnessClass{

	private:
		string className;
		string classDate;
		string classTime;
		int maxCapacity;
		string roomNumber;
		string ID;
		LinkedStack<int>* listOfMembers;


	public:
		FitnessClass(string id, string cname, string cdate, string ctime, int maxCap, string rnumber, LinkedStack<int>* members);
		FitnessClass(string id, string cname, string cdate, string ctime, int maxCap, string rnumber);
		FitnessClass();
		void addToListOfMembers(int e);

		string getclassName();
		string getclassDate();
		string getclassTime();
		int getmaxCapacity();
		string getroomNumber();
		string getID();
		LinkedStack<int>* getlistOfMembers();

	friend class LinkedList1<Admin>;
	friend class LinkedList1<Member>;
};

//========================================== LinkedStack ================================================================
template <typename T>
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

//========================================== NODE ================================================================

template <typename T>
class Node{
	private:
		T elem;
		Node* next;

	public:
		Node();
		Node<T>* getNext();
		T getElem();

	friend class LinkedList1<T>;
	friend class LinkedList1<Admin>;
	friend class LinkedList1<Member>;


};

//========================================== LINKED LIST ================================================================

//Turns string into all lowercase using ASCI values. 
//I used this code in assignment 1 as well. 
string toLower(string name){
	for(int i=0; i<name.length(); i++){
		if(name[i]>='A'&&name[i]<='Z'){
			name[i]=name[i]+32;
		}
	}
	return name;
}

template <typename T>
class LinkedList1{
	private:
		Node<T>* head;
	public:
		LinkedList1();
		~LinkedList1();
		bool empty() const;
		Node<T>* front() const;
		void addFront(const T&);
		void removeFront();
		void removeNode(Node<T>* e);
		bool login(string inputUsername, string inputPassword);
		int getId(string inputUsername, string inputPassword);
		void registerMember(LinkedList1<Member>& memberList);
		void registerAdmin();
		void printAllMembers(LinkedList1<Member>& members);
		void addFitnessClass(LinkedList1<FitnessClass>& FitnessClassList);
		void deleteFitnessClass(LinkedList1<FitnessClass>& FitnessClassList);
		void updateClassDetails(LinkedList1<FitnessClass>& FitnessClassList);
		void changeClassCapacity(LinkedList1<FitnessClass>& FitnessClassList);
		void splitClass(LinkedList1<FitnessClass>& FitnessClassList);
		void viewClassesWithVacancies(LinkedList1<FitnessClass>& FitnessClassList);
		void bookAClass(LinkedList1<FitnessClass>& FitnessClassList, int logedInUserID);
		void viewBookingList(LinkedList1<FitnessClass>& FitnessClassList, int logedInUserID);
		void cancelBooking(LinkedList1<FitnessClass>& FitnessClassList, int logedInUserID);
		void quitProgram(string fileName);
		void quitProgramForFitness(string fileName);

};


//========================================== ADMIN METHODS ================================================================
//Constructor for Admin.
Admin::Admin(int admID, string first, string last, string user, string pass){
	ID = admID;
	firstName = first;
	lastName = last;
	userName = user;
	password = pass;
}

//Constructor to create empty admin object. 
Admin::Admin(){
	ID = 123;
	firstName = "empty";
	lastName = "empty";
	userName = "empty";
	password = "empty";
}

//getter methods
int Admin::getID() {return ID;}
string Admin::getfirstName() {return firstName;}
string Admin::getlastName() {return lastName;}
string Admin::getuserName() {return userName;}
string Admin::getpassword() {return password;}


//========================================== MEMBER METHODS ================================================================
//Constructor for Member.
Member::Member(int memID, string first, string last, string user, string pass){
	ID = memID;
	firstName = first;
	lastName = last;
	userName = user;
	password = pass;
}

//Constructor to create empty member object
Member::Member(){
	ID = 123;
	firstName = "empty";
	lastName = "empty";
	userName = "empty";
	password = "empty";
}

//getter methods
int Member::getID() {return ID;}
string Member::getfirstName() {return firstName;}
string Member::getlastName() {return lastName;}
string Member::getuserName() {return userName;}
string Member::getpassword() {return password;}


//========================================== FITNESS CLASS METHODS ================================================================
//Constructor for FitnessClass
FitnessClass::FitnessClass(string id, string cname, string cdate, string ctime, int maxCap, string rnumber){

	ID = id;
	className = cname;
	classDate = cdate;
	classTime = ctime;
	maxCapacity = maxCap;
	roomNumber = rnumber;
	listOfMembers = new LinkedStack<int>();

}
//Constructor to create empty FitnessClass object
FitnessClass::FitnessClass(){
	ID = "testing";
	className = "testing";
	classDate = "testing";
	classTime = "testing";
	maxCapacity = 123;
	roomNumber = "testing";
	listOfMembers = new LinkedStack<int>(); 
}

//pushing a new member to the listofmembers stack. 
void FitnessClass::addToListOfMembers(int e){
	listOfMembers->push(e);
}

//getter methods
string FitnessClass::getclassName(){return className;}
string FitnessClass::getclassDate(){return classDate;}
string FitnessClass::getclassTime(){return classTime;}
int FitnessClass::getmaxCapacity(){return maxCapacity;}
string FitnessClass::getroomNumber(){return roomNumber;}
string FitnessClass::getID(){return ID;}
LinkedStack<int>* FitnessClass::getlistOfMembers(){return listOfMembers;}



//========================================== LINKED STACK METHODS ================================================================

//Constructor
template <typename T> LinkedStack<T>::LinkedStack(){
	S = LinkedList1<T>();
	n = 0;
}

//Basic Linked Stack method definitions.

//returns if the stack is empty
template <typename T> bool LinkedStack<T>::empty() const{
	return n == 0;
}

//returns the size of the linked stack
template <typename T> int LinkedStack<T>::size() const{
	return n;
}

//returns the top node of the linked stack
template <typename T> Node<T>* LinkedStack<T>::top() const throw(StackEmpty){
	if(empty()) throw StackEmpty();
	return S.front();
}

//adds node to the top of the linkedstack
template <typename T> void LinkedStack<T>::push(T e){
	S.addFront(e);
	n++;
}

//removes the top node of the linked stack.
template <typename T> void LinkedStack<T>::pop() throw(StackEmpty){
	if(empty()) throw StackEmpty();
	S.removeFront();
	n--;
}

//removes the node at a certain position in the stack.
template <typename T> void LinkedStack<T>::deleteNode(Node<T>* node){
	if(empty()) throw StackEmpty();
	S.removeNode(node);
	n--;
}

//getter methods
template <typename T> LinkedList1<T> LinkedStack<T>::getS(){return S;}
template <typename T> int LinkedStack<T>::getn(){return n;}

//========================================== NODE CLASS METHODS ================================================================

//constuctor
template <typename T> Node<T>::Node(){
	elem = T();
}

//gets next node.
template <typename T> Node<T>* Node<T>::getNext(){
	return next;
}

//gets element
template <typename T> T Node<T>::getElem(){
	return elem;
}

//========================================== LINKED LIST METHODS ================================================================

//Constructor of LinkedList
template <typename T> LinkedList1<T>::LinkedList1(){
	head = NULL;
}

//destructor
template <typename T> LinkedList1<T>::~LinkedList1(){
	while(!empty()) removeFront();
}

//Basic Linked List method definitions.

//returns if the linked list is empty
template <typename T> bool LinkedList1<T>::empty() const{
	return head == NULL;
}

//removes the front node of the linked list.
template <typename T> void LinkedList1<T>::removeFront(){
	Node<T>* temp = head;
	head = head->next;
	delete temp;

}

//given a node. Loops through the LinkedList to find the node before the given node. Deletes the node given. Rearranges the next values.
template <typename T> void LinkedList1<T>::removeNode(Node<T>* e){
	Node<T>* start = head;
	if(start == e) head = e->next;
	else{
		while(start->next != e){
			start = start->next;
		}
		start->next = e->next;
	}
	delete e; 
}


//adds a node at the fornt of the linked list.
template <typename T> void LinkedList1<T>::addFront(const T& e){
	Node<T>* newNode = new Node<T>;
	newNode->elem = e;
	newNode->next = head;
	head = newNode;
}

//retuns the head node of the linked list
template <typename T> Node<T>* LinkedList1<T>::front() const{
	return head;
}

//Given input of username and passowrd, loops entire Linkedlist to see if there is a node->elem with the same username and password.
template <typename T> bool LinkedList1<T>::login(string inputUsername, string inputPassword){
	Node<T>* starterNode = head;
	while(starterNode != NULL){
		if(starterNode->getElem().getpassword() == inputPassword && starterNode->getElem().getuserName() == inputUsername){
			return true;
		}
		starterNode = starterNode->next;
	}
	return false;
}

//Given input of username and passowrd, loops entire Linkedlist to see if there is a node->elem with the same username and password, returns the ID.
template <typename T> int LinkedList1<T>::getId(string inputUsername, string inputPassword){
	Node<T>* starterNode = head;
	while(starterNode != NULL){
		if(starterNode->getElem().getpassword() == inputPassword && starterNode->getElem().getuserName() == inputUsername){
			return starterNode->getElem().getID();
		}
		starterNode = starterNode->next;
	}
	return 1;
}

//Given list of Memeber. Asks user for first and last name. Creates needed information with random 4 digit values.
//Creates new Member object and adds to the front of the memberList LinkedList.
template <typename T> void LinkedList1<T>::registerMember(LinkedList1<Member>& memberList){
	string userFirstname;
	string userLastname;
	string username;
	string password;
	int id = rand()%9000 + 1000; //Creates random 4 digit ID.


	cout<<"Please enter the first name of the new Member: "<<endl;
	cin>>userFirstname;
	cout<<"Please enter the last name of the new Member: "<<endl;
	cin>>userLastname;

	username = toLower(userFirstname) + to_string(id);
	password = toLower(userLastname) + to_string(rand()%9000 + 1000);

	cout<<endl<<"userName: "<<username<<"  password: "<<password<<endl;

	Member addingMember = Member(id, userFirstname, userLastname, username, password);
	memberList.addFront(addingMember);

	cout<<endl<<"Successfully created"<<endl;

}

//Asks user for first and last name. Creates needed information with random 4 digit values.
//Creates new Admin object and adds to the front of the adminList LinkedList.
template <typename T> void LinkedList1<T>::registerAdmin(){
	string userFirstname;
	string userLastname;
	string username;
	string password;
	int id = rand()%9000 + 1000; //Creates random 4 digit ID.


	cout<<"Please enter the first name of the new admin: "<<endl;
	cin>>userFirstname;
	cout<<"Please enter the last name of the new admin: "<<endl;
	cin>>userLastname;

	username = toLower(userFirstname) + to_string(id);
	password = toLower(userLastname) + to_string(rand()%9000 + 1000);

	cout<<endl<<"userName: "<<username<<"  password: "<<password<<endl;

	Admin addingMember = Admin(id, userFirstname, userLastname, username, password);
	addFront(addingMember);

	cout<<endl<<"Successfully created"<<endl;

}

//Loops the entire members LinkedList and prints all the relevent information.
template <typename T> void LinkedList1<T>::printAllMembers(LinkedList1<Member>& members){
	Node<Member>* firstNode = members.front();
	cout<<"Here are the list of Members"<<endl;
	while(firstNode!=NULL){
		cout<<"Member ID: "<<firstNode->getElem().getID()<<"  First Name: "<<firstNode->getElem().getfirstName()
		    <<"  Last Name: "<<firstNode->getElem().getlastName()<<endl;
		firstNode = firstNode->getNext();
	}
	
}

//Asks user for all information needed to create a FintessClass object.  Creates new FitnessClass object, adds to the FitnessClass linked list. 
template <typename T> void LinkedList1<T>::addFitnessClass(LinkedList1<FitnessClass>& FitnessClassList){
	string cID, cName, cDate, cTime, rNumber;
	int maxcap = 10;
	cout<<"Please enter the class ID of the new fitness class: ";
	cin>>cID;
	cout<<"Please enter the class name of the new fitness class: ";
	cin>>cName;
	cout<<"Please enter the class date of the new fitness class: ";
	cin>>cDate;
	cout<<"Please enter the class time of the new fitness class: ";
	cin>>cTime;
	cout<<"Please enter the class room number of the new fitness class: ";
	cin>>rNumber;
	cout<<"Please enter the maximum capactiy of the new fitness class: ";
	cin>>maxcap;

	FitnessClass newFit = FitnessClass(cID, cName, cDate, cTime, maxcap, rNumber);
	FitnessClassList.addFront(newFit);
	cout<<endl<<"Successfully created new class"<<endl;
}

//Given the ID of a FitnessClass, loops entire FitnessClass linkedlist and checks if given ID matches ID in linkedlst.
//If there is a match, that node is removed from the linkedlist.
template <typename T> void LinkedList1<T>::deleteFitnessClass(LinkedList1<FitnessClass>& FitnessClassList){
	string cID;
	cout<<"Please enter the class ID of the fitness class you would like to delete: ";
	cin>>cID;
	Node<FitnessClass>* deleteNode = FitnessClassList.front();
	while(deleteNode!=NULL && deleteNode->getElem().getID() != cID){
		deleteNode = deleteNode->getNext();
	}
	if(deleteNode == NULL) cout<<"There is no class with this ID"<<endl;
	else if(deleteNode == FitnessClassList.front()){
		FitnessClassList.removeFront();
		cout<<endl<<"Successfully deleted this class"<<endl;
	}
	else{
		FitnessClassList.removeNode(deleteNode);
		cout<<endl<<"Successfully deleted this class"<<endl;
	}
	
}

//Given the ID of a FitnessClass, loops entire FitnessClass linkedlist and checks if given ID matches ID in linkedlst.
//If there is a match, user is asked for what detail they would like to update.
//given their response, the corresponding element in the FitnessClass is updated.
template <typename T> void LinkedList1<T>::updateClassDetails(LinkedList1<FitnessClass>& FitnessClassList){
	string cID;
	string userInput;
	cout<<"Please enter the class ID of the fitness class you would like to update: ";
	cin>>cID;	

	Node<FitnessClass>* updateNode = FitnessClassList.front();
	while(updateNode!=NULL && updateNode->getElem().getID() != cID){
		updateNode = updateNode->getNext();
	}
	if(updateNode == NULL) cout<<"Do not recognize this class ID"<<endl;
	else {

		cout<<"What Class detail would you like to update: "<<endl;
		cout<<"1) Class room"<<endl;
		cout<<"2) Class date"<<endl;
		cout<<"3) Class time"<<endl;
		cout<<"4) Go back"<<endl;

		do{
			cin>>userInput;
			if(userInput == "1"){
				string changeRoom;
				cout<<"What would you like to change the class room number to: ";
				cin>>changeRoom;
				updateNode->elem.roomNumber = changeRoom;
				cout<<"Successfully Done!"<<endl;
				break;
			}
			else if(userInput == "2"){
				string changeDate;
				cout<<"What would you like to change the class date to: ";
				cin>>changeDate;
				updateNode->elem.classDate = changeDate;
				cout<<"Successfully Done!"<<endl;
				break;
			}
			else if(userInput == "3"){
				string changeTime;
				cout<<"What would you like to change the class time to: ";
				cin>>changeTime;
				updateNode->elem.classTime = changeTime;
				cout<<"Successfully Done!"<<endl;
				break;
			}
			else if(userInput == "4");
			else cout<<"Invalid Entry"<<endl;

		}
		
		while(userInput != "4");
	}

}

//Given the ID of a FitnessClass, loops entire FitnessClass linkedlist and checks if given ID matches ID in linkedlst.
//If there is a match, user is asked for what they would like to change the capacity to (limits to their ability to adjust).
//if the newcapactiy is less then the current number of members in the class, the last members to join are poped from the linkedStack.
//else the new capacity is updated to the new user defiend capacity.
template <typename T> void LinkedList1<T>::changeClassCapacity(LinkedList1<FitnessClass>& FitnessClassList){
	int newCapacity;
	string cID;
	cout<<"Please enter the class ID of the fitness class you would like to update: ";
	cin>>cID;	

	Node<FitnessClass>* updateNode = FitnessClassList.front();
	while(updateNode!=NULL && updateNode->getElem().getID() != cID){
		updateNode = updateNode->getNext();
	}
	if(updateNode == NULL) cout<<"Do not recognize this class ID"<<endl;
	else {
		cout<<"What would you like to change the capactiy of this class to: ";
		cin>>newCapacity;
		if(newCapacity>15) newCapacity = 15;
		else if(newCapacity<5) newCapacity = 5;
		if(newCapacity-1<updateNode->getElem().getlistOfMembers()->getn()){
			while(newCapacity-1<updateNode->getElem().getlistOfMembers()->getn()){
				updateNode->getElem().getlistOfMembers()->pop();
			}
			updateNode->elem.maxCapacity = newCapacity;	
		}
		else updateNode->elem.maxCapacity = newCapacity;
		cout<<endl<<"Successfully updated class capacity!"<<endl;
	}
}

//Given the ID of a FitnessClass, loops entire FitnessClass linkedlist and checks if given ID matches ID in linkedlst.
//if there is a match, user is asked to input new capacities for each class. Then user is asked for relevent inforamation about 
//the new class other then the classname. New FitnessClass is created.
template <typename T> void LinkedList1<T>::splitClass(LinkedList1<FitnessClass>& FitnessClassList){
	string cID;
	cout<<"Please enter the class ID of the fitness class you would like to split: ";
	cin>>cID;	

	Node<FitnessClass>* updateNode = FitnessClassList.front();
	while(updateNode!=NULL && updateNode->getElem().getID() != cID){
		updateNode = updateNode->getNext();
	}
	if(updateNode == NULL) cout<<"Do not recognize this class ID"<<endl;
	else{
		int capacityClass1 = 10;
		int capacityClass2 = 10;
		cout<<"What capacity would you like to have for class 1: ";
		cin>>capacityClass1;
		cout<<"What capacity would you like to have for class 2: ";
		cin>>capacityClass2;

		string newID;
		string newTime;
		string newDate;
		string newRoom;

		cout<<"What is the newID for the class: ";
		cin>>newID;
		cout<<"What time will this class be held: ";
		cin>>newTime;
		cout<<"What date will this class be held: ";
		cin>>newDate;
		cout<<"What room will this class be held: ";
		cin>>newRoom;

		FitnessClass class2 = FitnessClass(newID, updateNode->getElem().getclassName(), newDate, newTime, capacityClass2, newRoom);

		//if the existing FitnessClass has too many members for the newCapacity, then the last members to join are popped off the existing
		//class and are added to the new class.
		if(updateNode->getElem().getlistOfMembers()->getn()>capacityClass1){
			while(updateNode->getElem().getlistOfMembers()->getn()>capacityClass1){
				int popping = updateNode->getElem().getlistOfMembers()->top()->getElem();
				updateNode->getElem().getlistOfMembers()->pop();
				class2.addToListOfMembers(popping);
			}
		}
		cout<<"HERE"<<capacityClass1<<endl;
		updateNode->elem.maxCapacity = capacityClass1;
		FitnessClassList.addFront(class2);
		cout<<endl<<"Successfully split class"<<endl;

	}
}

//Loops the entire fitnessclass checking to see if the n value of the linkedStack is less then maxCapacity. If so relevant information
//about the FitnessClass is printed.
template <typename T> void LinkedList1<T>::viewClassesWithVacancies(LinkedList1<FitnessClass>& FitnessClassList){
	bool noClasses = true;
	Node<FitnessClass>* firstNode = FitnessClassList.front();
	cout<<"Here are the classes that are currently open:"<<endl<<endl;
	while(firstNode!=NULL){
		if(firstNode->getElem().getmaxCapacity()-1>firstNode->getElem().getlistOfMembers()->getn()){
			cout<<"Class Id: "<<firstNode->getElem().getID()<<endl;
			cout<<"Class Name: "<<firstNode->getElem().getclassName()<<endl;
			cout<<"Class Date: "<<firstNode->getElem().getclassDate()<<endl;
			cout<<"Class Time: "<<firstNode->getElem().getclassTime()<<endl;
			cout<<"Room Number: "<<firstNode->getElem().getroomNumber()<<endl<<endl;
			noClasses = false;
		}

		firstNode = firstNode->getNext();
	}
	if(noClasses) cout<<endl<<"All classes are booked"<<endl;
}

//Given the ID of a FitnessClass, loops entire FitnessClass linkedlist and checks if given ID matches ID in linkedlst.
//if there is a match, the capacity of the class is checked. If the class is not full, then member is added to the list of members.
template <typename T> void LinkedList1<T>::bookAClass(LinkedList1<FitnessClass>& FitnessClassList, int logedInUserID){
	string cID;
	cout<<"Please enter the class ID of the fitness class you would like to book: ";
	cin>>cID;	

	Node<FitnessClass>* fitNode = FitnessClassList.front();
	while(fitNode!=NULL && fitNode->getElem().getID() != cID){
		fitNode = fitNode->getNext();
	}
	if(fitNode == NULL) cout<<endl<<"Do not recognize this class ID"<<endl;
	else if(fitNode->getElem().getmaxCapacity()-1>fitNode->getElem().getlistOfMembers()->getn()){
		fitNode->getElem().addToListOfMembers(logedInUserID);
		cout<<endl<<"Successfully booked!"<<endl;

	}
	else cout<<endl<<"This class is full"<<endl;
}

//loops entire FitnessClass linked list, then loops entire linkedStack of members in each fitnessClass checking to see if the
//given user is in the class. If true, then the relevant information about the class is printed.
template <typename T> void LinkedList1<T>::viewBookingList(LinkedList1<FitnessClass>& FitnessClassList, int logedInUserID){
	cout<<endl;
	bool noClassesBooked = true;
	Node<FitnessClass>* fitNode = FitnessClassList.front();
	while(fitNode!=NULL){
		if(fitNode->getElem().getlistOfMembers()->empty()) break;
		else{
			Node<int>* member = fitNode->getElem().getlistOfMembers()->top();
			while(member!=NULL){
				if(member->getElem() == logedInUserID){
					cout<<"Class Name: "<<fitNode->getElem().getclassName()<<endl;
					cout<<"Class Date: "<<fitNode->getElem().getclassDate()<<endl;
					cout<<"Class Time: "<<fitNode->getElem().getclassTime()<<endl;
					cout<<"Room Number: "<<fitNode->getElem().getroomNumber()<<endl<<endl;
					noClassesBooked = false;
				}
				member = member->getNext();
			}
			fitNode = fitNode->getNext();
		}
	}
	if(noClassesBooked) cout<<endl<<"You do not have any classes booked at this time"<<endl<<endl;
}

//Given the ID of a FitnessClass, loops entire FitnessClass linkedlist and checks if given ID matches ID in linkedlst.
//If there is a match, the FitnessClass listOfMembers is looped through checking if givenUser is registed in Class.
//If they are registered, their ID is removed from the listOfMembers. 
template <typename T> void LinkedList1<T>::cancelBooking(LinkedList1<FitnessClass>& FitnessClassList, int logedInUserID){
	string cID;
	cout<<"Please enter the class ID of the fitness class you would like to cancel: ";
	cin>>cID;	

	bool inClass = false;
	Node<FitnessClass>* fitNode = FitnessClassList.front();
	while(fitNode!=NULL && fitNode->getElem().getID() != cID){
		fitNode = fitNode->getNext();
	}
	if(fitNode == NULL) cout<<endl<<"Do not recognize this class ID"<<endl;
	else{
		Node<int>* member = fitNode->getElem().getlistOfMembers()->top();
		while(member!=NULL){
			if(member->getElem() == logedInUserID){
				inClass = true;
				fitNode->getElem().getlistOfMembers()->deleteNode(member);
				cout<<endl<<"Successfully canceled booking"<<endl;
				break;
			}
			member = member->getNext();

		}
		if(!inClass) cout<<endl<<"You are not registed for this class"<<endl;

	}
}

//Given file name, the file is opened. while the linkedList is not empty, two Node pointers are created. One ensures the entire 
//Linkedlist is looped through, the other determines which ID is the smallest. 
//If the current topID is greater then the Node being iterated over, the topID node is updated.
//The object of the topID pointer is then printed to the filename. then topID is removed from the linkedList.
template <typename T> void LinkedList1<T>::quitProgram(string fileName){
	ofstream fout(fileName);
	while(!empty()){
		Node<T>* printNode = head;
		Node<T>* topID = head;
		while(printNode != NULL){
			if(printNode->getElem().getID() < topID->getElem().getID()){
				topID = printNode;
			}
			printNode = printNode->next;
		}
		if(fout){
			fout<<topID->getElem().getID()<<","<<topID->getElem().getfirstName()<<","<<topID->getElem().getlastName()
				<<","<<topID->getElem().getuserName()<<","<<topID->getElem().getpassword()<<endl;
		}
		else{
			perror("");
		}
		removeNode(topID);
	}
}

//Given file name, the file is opened. while the linkedList is not empty, two Node pointers are created. One ensures the entire 
//Linkedlist is looped through, the other determines which ID is the smallest. 
//If the current topID is greater then the Node being iterated over, the topID node is updated.
//The object of the topID pointer is then printed to the filename. then topID is removed from the linkedList.
//Needs a new method because FitnessClass has different variables and there needs to be a loop to print all the memberID of the members
//in the listOfMembers LinkedStack.
template <typename T> void LinkedList1<T>::quitProgramForFitness(string fileName){
	ofstream fout(fileName);
	while(!empty()){
		Node<T>* printNode = head;
		Node<T>* topID = head;
		while(printNode != NULL){
			if(stoi(printNode->getElem().getID()) < stoi(topID->getElem().getID())){
				topID = printNode;
			}
			printNode = printNode->next;
		}
		if(fout){
			fout<<topID->getElem().getID()<<","<<topID->getElem().getclassName()<<","<<topID->getElem().getclassDate()
				<<","<<topID->getElem().getclassTime()<<","<<topID->getElem().getmaxCapacity()<<","<<topID->getElem().getroomNumber()<<",[";
			LinkedStack<int>* membersNode = topID->getElem().getlistOfMembers();
			while(!membersNode->empty()){
				fout<<membersNode->top()->getElem();
				membersNode->pop();
				if(!membersNode->empty()) fout<<",";
			}
			fout<<"]"<<endl;
		}
		else{
			perror("");
		}
		removeNode(topID);
	}
}


//========================================== START MAIN FILE ================================================================

//Global Variables
LinkedList1<Member> MemberList;
LinkedList1<Admin> AdminList;
LinkedList1<FitnessClass> FitnessClassList;
int logedInUserID;


//Takes data from files, and implements them into cooresponding LinkedList. 
void inputData(){

	//==============================READ MEMBERS TEXT FILE ===============================================================

	ifstream fin("Members.txt");

	int ID; string firstname, lastname, username, password, tempID;
	string line;
	
	//reads in the line and assigns them to given variables.
	while(getline(fin,line)){
		stringstream ss(line);
		getline(ss,tempID,',');
		getline(ss,lastname,',');
		getline(ss,firstname,',');
		getline(ss,username,',');
		getline(ss,password,',');
		ID = stoi(tempID);

		Member temp = Member(ID, firstname, lastname, username, password);
		MemberList.addFront(temp);
	}

	fin.close();

	//==============================READ ADMINS TEXT FILE ===============================================================

	ifstream fin1("Admins.txt");

	//reads in the line and assigns them to given variables.
	while(getline(fin1,line)){
		stringstream ss(line);
		getline(ss,tempID,',');
		getline(ss,lastname,',');
		getline(ss,firstname,',');
		getline(ss,username,',');
		getline(ss,password,',');
		ID = stoi(tempID);

		Admin temp = Admin(ID, firstname, lastname, username, password);
		AdminList.addFront(temp);
	}

	fin1.close();

	//==============================READ FITENESSCLASSES TEXT FILE ===============================================================

	ifstream fin2("FitnessClasses.txt");

	string fitID, cname, cdate, ctime, tempMaxCap, rnumber, arrayOfMembers;
	int maxCap;

	//reads in the line and assigns them to given variables.
	while(getline(fin2,line)){
		stringstream ss(line);
		getline(ss,fitID,',');
		getline(ss,cname,',');
		getline(ss,cdate,',');
		getline(ss,ctime,',');
		getline(ss,tempMaxCap,',');
		getline(ss,rnumber,',');
		getline(ss,arrayOfMembers,']');
		maxCap = stoi(tempMaxCap);


		arrayOfMembers = arrayOfMembers.substr(1,arrayOfMembers.length()-1);
		bool lengthGreaterThanZero = false;
		FitnessClass temp = FitnessClass(fitID, cname, cdate, ctime, maxCap, rnumber);
		string tempNumber;
		int number;
		int i=0;

		//for the length of the string value, split the string at a comma. change string into integer, and ad to LinkedList Stack of members.
		while(arrayOfMembers.length()>i){
			lengthGreaterThanZero = true;
			if(arrayOfMembers[i]==','){
				number = stoi(tempNumber);
				temp.addToListOfMembers(number);
				tempNumber = "";
			}
			else{
				tempNumber += arrayOfMembers[i];
			}
			i++;
		}
		if(lengthGreaterThanZero){
			number = stoi(tempNumber);
			temp.addToListOfMembers(number);
		}
		FitnessClassList.addFront(temp);

	}

}

int login(){

	//Asks for userinput of Type. Verifys if input is either Admin or Member
	string userType;
	while(true){
		bool breakLoop = false;
		do{
			cout<<"Please enter the category of your account before logging in: [admin/member] "<<endl;
			cin>>userType;

		}
		while(userType!="Admin"&&userType!="admin"&&userType!="Member"&&userType!="member");
		break;

	}

	//Asks user for username and passowrd. If userType is admin, admin.login() is called, otherwise member.login() is called.
	//Then the respective getId() method is called to get the ID of the member logging in.
	while(true){
		string userInputUsername;
		string userInputPassword;
		cout<<"What is your username: ";
		cin>>userInputUsername;
		cout<<"What is your password: ";
		cin>>userInputPassword;

		if(userType == "Admin"|| userType == "admin"){
			if(AdminList.login(userInputUsername,userInputPassword)){
				logedInUserID = AdminList.getId(userInputUsername,userInputPassword);
				return 1;
			}
		}
		else{
			if(MemberList.login(userInputUsername, userInputPassword)){
				logedInUserID = MemberList.getId(userInputUsername,userInputPassword);
				return 2;
			}
		}

		cout<<"Do not recognize this password or username. Please try again"<<endl;

	}

}

//Print values for Admin Commands.
void listAdminCommands(){

	cout<<endl<<endl;
	cout<<"1) Register a new Admin"<<endl;
	cout<<"2) Register a new member"<<endl;
	cout<<"3) View list of Members"<<endl;
	cout<<"4) Add a fitness class"<<endl;
	cout<<"5) Delete a fitness class"<<endl;
	cout<<"6) Update the details of a fitness class"<<endl;
	cout<<"7) Update the capactiy of a fitness class"<<endl;
	cout<<"8) Split a fitness class into two classes"<<endl;
	cout<<"9) Display the classes with Vacancies"<<endl;
	cout<<"10) Log out"<<endl;
	cout<<"11) Quit program"<<endl<<endl;
	cout<<"Enter the number of the required action: [1-11]: ";

}

//print values for Member commands.
void listMemberCommands(){
	cout<<endl<<endl;
	cout<<"1) Book a class"<<endl;
	cout<<"2) Display the classes with Vacancies"<<endl;
	cout<<"3) View current bookings"<<endl;
	cout<<"4) Cancel booking"<<endl;
	cout<<"5) Log out"<<endl;
	cout<<"6) Quit program"<<endl<<endl;
	cout<<"Enter the number of the required action: [1-6]: ";

}

//Asks the user for an integer value. Calls the corresponding methods.
bool adminControls(){

	string userInput;
	
	do{
		listAdminCommands();
		cin>>userInput;
		if(userInput == "1") AdminList.registerAdmin();
		else if(userInput == "2") AdminList.registerMember(MemberList);
		else if(userInput == "3") AdminList.printAllMembers(MemberList);
		else if(userInput == "4") AdminList.addFitnessClass(FitnessClassList);
		else if(userInput == "5") AdminList.deleteFitnessClass(FitnessClassList);
		else if(userInput == "6") AdminList.updateClassDetails(FitnessClassList);
		else if(userInput == "7") AdminList.changeClassCapacity(FitnessClassList);
		else if(userInput == "8") AdminList.splitClass(FitnessClassList);
		else if(userInput == "9") AdminList.viewClassesWithVacancies(FitnessClassList);
		else if(userInput == "10"){
			cout<<endl<<"Logging out"<<endl<<endl;
			return true;
		}
		else if(userInput == "11");
		else cout<<"Invalid Entry"<<endl;

	}
	
	while(userInput != "11");

	return false;


}

//Asks the user for an integer value. Calls the corresponding methods.
bool memberControls(){
	string userInput;
	do{
		listMemberCommands();
		cin>>userInput;
		if(userInput == "1") MemberList.bookAClass(FitnessClassList, logedInUserID);
		else if(userInput == "2") MemberList.viewClassesWithVacancies(FitnessClassList);
		else if(userInput == "3") MemberList.viewBookingList(FitnessClassList, logedInUserID);
		else if(userInput == "4") MemberList.cancelBooking(FitnessClassList, logedInUserID);
		else if(userInput == "5"){
			cout<<endl<<"Logging out"<<endl<<endl;
			return true;
		}
		else if(userInput == "6");
		else cout<<"Invalid Entry"<<endl;
	}

	while(userInput != "6");

	return false;
}


int main(){
	inputData();
	int userType;
	bool continueUsing = true;

	//Loops until user quits system.
	while(continueUsing){
		//login method is called. 
		userType = login();
		cout<<"You have logged in successfully!"<<endl;
		if(userType == 1){
			cout<<"Welcome Back Admin"<<endl;
			continueUsing = adminControls();
		}
		else{
			cout<<"Welcome Back Member"<<endl;
			continueUsing = memberControls();
		}
	}

	//quitsProgram to print to txt files. 
	AdminList.quitProgram("Admins.txt");
	MemberList.quitProgram("Members.txt");
	FitnessClassList.quitProgramForFitness("FitnessClasses.txt");

	cout<<endl<<"Thank you for using the Fitness System"<<endl;
	return 0;
};