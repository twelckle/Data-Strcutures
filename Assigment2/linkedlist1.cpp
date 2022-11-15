#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<sstream>

#include<string>
#include"linkedlist1.h"
#include"linkedstack.h"
#include"admin.h"
#include"member.h"
#include"fitness.h"



string toLower(string name){
	for(int i=0; i<name.length(); i++){
		if(name[i]>='A'&&name[i]<='Z'){
			name[i]=name[i]+32;
		}
	}
	return name;
}

template <class T> Node<T>::Node(){
	elem = T();
}

template <class T> Node<T>* Node<T>::getNext(){
	return next;
}

template <class T> T Node<T>::getElem(){
	return elem;
}


template <class T> LinkedList1<T>::LinkedList1(){
	head = NULL;
}

template <class T> LinkedList1<T>::~LinkedList1(){
	while(!empty()) removeFront();
}
template <class T> bool LinkedList1<T>::empty() const{
	return head == NULL;
}

template <class T> void LinkedList1<T>::removeFront(){
	Node<T>* temp = head;
	head = head->getNext();
	delete temp;

}

template <class T> void LinkedList1<T>::removeNode(Node<T>* e){
	Node<T>* start = head;
	if(start == e) head = e->getNext();
	else{
		while(start->getNext() != e){
			start = start->getNext();
		}
		start->next = e->getNext();
	}
	delete e; 
}

template <class T> Node<T>* LinkedList1<T>::getHead(){
	return head;
}

template <class T> void LinkedList1<T>::addFront(const T& e){
	Node<T>* newNode = new Node<T>;
	newNode->elem = e;
	newNode->next = head;
	head = newNode;
}

template <class T> Node<T>* LinkedList1<T>::front() const{
	return head;
}


template <class T> bool LinkedList1<T>::login(string inputUsername, string inputPassword){
	Node<T>* starterNode = head;
	while(starterNode != NULL){
		if(starterNode->getElem().getpassword() == inputPassword && starterNode->getElem().getuserName() == inputUsername){
			return true;
		}
		starterNode = starterNode->getNext();
	}
	return false;
}

template <class T> int LinkedList1<T>::getId(string inputUsername, string inputPassword){
	Node<T>* starterNode = head;
	while(starterNode != NULL){
		if(starterNode->getElem().getpassword() == inputPassword && starterNode->getElem().getuserName() == inputUsername){
			return starterNode->getElem().getID();
		}
		starterNode = starterNode->getNext();
	}
	return 1;
}

template <class T> void LinkedList1<T>::registerMember(LinkedList1<Member>& memberList){
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

template <class T> void LinkedList1<T>::registerAdmin(){
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

template <class T> void LinkedList1<T>::printAllMembers(LinkedList1<Member>& members){
	Node<Member>* firstNode = members.getHead();
	cout<<"Here are the list of Members"<<endl;
	while(firstNode!=NULL){
		cout<<"Member ID: "<<firstNode->getElem().getID()<<"  First Name: "<<firstNode->getElem().getfirstName()
		    <<"  Last Name: "<<firstNode->getElem().getlastName()<<endl;
		firstNode = firstNode->getNext();
	}
	
}


template <class T> void LinkedList1<T>::addFitnessClass(LinkedList1<FitnessClass>& FitnessClassList){
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

template <class T> void LinkedList1<T>::deleteFitnessClass(LinkedList1<FitnessClass>& FitnessClassList){
	string cID;
	cout<<"Please enter the class ID of the fitness class you would like to delete: ";
	cin>>cID;
	Node<FitnessClass>* deleteNode = FitnessClassList.getHead();
	while(deleteNode!=NULL && deleteNode->getElem().getID() != cID){
		deleteNode = deleteNode->getNext();
	}
	if(deleteNode == NULL) cout<<"There is no class with this ID"<<endl;
	else if(deleteNode == FitnessClassList.getHead()){
		FitnessClassList.removeFront();
		cout<<endl<<"Successfully deleted this class"<<endl;
	}
	else{
		FitnessClassList.removeNode(deleteNode);
		cout<<endl<<"Successfully deleted this class"<<endl;
	}
	
}

template <class T> void LinkedList1<T>::updateClassDetails(LinkedList1<FitnessClass>& FitnessClassList){
	string cID;
	string userInput;
	cout<<"Please enter the class ID of the fitness class you would like to update: ";
	cin>>cID;	

	Node<FitnessClass>* updateNode = FitnessClassList.getHead();
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
				updateNode->getElem().setroomNumber(changeRoom);
				cout<<"Successfully Done!"<<endl;
				break;
			}
			else if(userInput == "2"){
				string changeDate;
				cout<<"What would you like to change the class date to: ";
				cin>>changeDate;
				updateNode->getElem().setclassDate(changeDate);
				cout<<"Successfully Done!"<<endl;
				break;
			}
			else if(userInput == "3"){
				string changeTime;
				cout<<"What would you like to change the class time to: ";
				cin>>changeTime;
				updateNode->getElem().setclassTime(changeTime);
				cout<<"Successfully Done!"<<endl;
				break;
			}
			else if(userInput == "4");
			else cout<<"Invalid Entry"<<endl;

		}
		
		while(userInput != "4");
	}

}

template <class T> void LinkedList1<T>::changeClassCapacity(LinkedList1<FitnessClass>& FitnessClassList){
	int newCapacity;
	string cID;
	cout<<"Please enter the class ID of the fitness class you would like to update: ";
	cin>>cID;	

	Node<FitnessClass>* updateNode = FitnessClassList.getHead();
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
			updateNode->getElem().setmaxCapacity(newCapacity);	
		}
		else updateNode->getElem().setmaxCapacity(newCapacity);
		cout<<endl<<"Successfully updated class capacity!"<<endl;
	}
}

template <class T> void LinkedList1<T>::splitClass(LinkedList1<FitnessClass>& FitnessClassList){
	string cID;
	cout<<"Please enter the class ID of the fitness class you would like to split: ";
	cin>>cID;	

	Node<FitnessClass>* updateNode = FitnessClassList.getHead();
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

		if(updateNode->getElem().getlistOfMembers()->getn()>capacityClass1){
			while(updateNode->getElem().getlistOfMembers()->getn()>capacityClass1){
				int popping = updateNode->getElem().getlistOfMembers()->top()->getElem();
				updateNode->getElem().getlistOfMembers()->pop();
				class2.addToListOfMembers(popping);
			}
		}

		updateNode->getElem().setmaxCapacity(capacityClass1);
		FitnessClassList.addFront(class2);
		cout<<endl<<"Successfully split class"<<endl;

	}
}

template <class T> void LinkedList1<T>::viewClassesWithVacancies(LinkedList1<FitnessClass>& FitnessClassList){
	bool noClasses = true;
	Node<FitnessClass>* firstNode = FitnessClassList.getHead();
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

template <class T> void LinkedList1<T>::bookAClass(LinkedList1<FitnessClass>& FitnessClassList, int logedInUserID){
	string cID;
	cout<<"Please enter the class ID of the fitness class you would like to book: ";
	cin>>cID;	

	Node<FitnessClass>* fitNode = FitnessClassList.getHead();
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

template <class T> void LinkedList1<T>::viewBookingList(LinkedList1<FitnessClass>& FitnessClassList, int logedInUserID){
	cout<<endl;
	bool noClassesBooked = true;
	Node<FitnessClass>* fitNode = FitnessClassList.getHead();
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

template <class T> void LinkedList1<T>::cancelBooking(LinkedList1<FitnessClass>& FitnessClassList, int logedInUserID){
	string cID;
	cout<<"Please enter the class ID of the fitness class you would like to cancel: ";
	cin>>cID;	

	bool inClass = false;
	Node<FitnessClass>* fitNode = FitnessClassList.getHead();
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

template <class T> void LinkedList1<T>::quitProgram(string fileName){
	ofstream fout(fileName);
	while(!empty()){
		Node<T>* printNode = head;
		Node<T>* topID = head;
		while(printNode != NULL){
			if(printNode->getElem().getID() < topID->getElem().getID()){
				topID = printNode;
			}
			printNode = printNode->getNext();
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

template <class T> void LinkedList1<T>::quitProgramForFitness(string fileName){
	ofstream fout(fileName);
	while(!empty()){
		Node<T>* printNode = head;
		Node<T>* topID = head;
		while(printNode != NULL){
			if(stoi(printNode->getElem().getID()) < stoi(topID->getElem().getID())){
				topID = printNode;
			}
			printNode = printNode->getNext();
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

template class LinkedList1<FitnessClass>;
template class LinkedList1<Member>;
template class LinkedList1<Admin>;
