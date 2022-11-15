#include<string>
#include<iostream>
#include<cstdlib>

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


template <typename T> LinkedList1<T>::LinkedList1(){
	head = NULL;
}

template <typename T> LinkedList1<T>::~LinkedList1(){
	while(!empty()) removeFront();
}
template <typename T> bool LinkedList1<T>::empty() const{
	return head == NULL;
}

template <typename T> void LinkedList1<T>::removeFront(){
	Node<T>* temp = head;
	head = head->next;
	delete temp;

}

template <typename T> void LinkedList1<T>::addFront(const T& e){
	Node<T>* newNode = new Node<T>;
	newNode->elem = e;
	newNode->next = head;
	head = newNode;
}

template <typename T> T LinkedList1<T>::front(){
	return head->elem;
}


template <typename T> bool LinkedList1<T>::login(string inputUsername, string inputPassword){
	Node<T>* starterNode = head;
	while(starterNode != NULL){
		if(starterNode->elem.password == inputPassword && starterNode->elem.userName == inputUsername){
			return true;
		}
		starterNode = starterNode->next;
	}
	return false;
}

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

	cout<<"First name: "<<userFirstname<<"Last Name: "<<userLastname<<endl;
	cout<<"userName: "<<username<<"  password: "<<password<<endl;

	Member addingMember = Member(id, userFirstname, userLastname, username, password);
	memberList.addFront(addingMember);


}

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

	cout<<"First name: "<<userFirstname<<"Last Name: "<<userLastname<<endl;
	cout<<"userName: "<<username<<"  password: "<<password<<endl;

	Admin addingMember = Admin(id, userFirstname, userLastname, username, password);
	this->addFront(addingMember);

}

template <typename T> void LinkedList1<T>::printAllMembers(const LinkedList1<Member>& members){
	Node<Member>* firstNode = members.head;
	cout<<"Here are the list of Members"<<endl;
	while(firstNode!=NULL){
		cout<<"Member ID: "<<firstNode->elem.memberID<<"  First Name: "<<firstNode->elem.firstName<<"  Last Name: "<<firstNode->elem.lastName<<endl;
		firstNode = firstNode->next;
	}
	
}

template <typename T> void LinkedList1<T>::printFitnessClassDetails(){
	Node<FitnessClass>* firstNode = this->head;
	cout<<"Here is the FitnessClass details:"<<endl;
	while(firstNode != NULL)
	{
		cout<<"Class ID: " <<firstNode->elem.fitID<<endl;
		cout<<"Class Name: "<<firstNode->elem.classID<<endl;
		cout<<"Class date: "<<firstNode->elem.classDate<<endl;
		cout<<"Class time: "<<firstNode->elem.classTime<<endl;
		cout<"Maximum cpacity: "<<firstNode->elem.maxCapacity<<endl;
		cout<<"Room number: "<<firstNode->elem.roomNumber<<endl;
		cout<<"List of Members ID: [";
		Node<FitnessClass>* secondNode = firstNode->elem.listOfMembers->head;
		while(secondNode!=NULL){
			cout<<secondNode->elem<<endl;
			secondNode = secondNode->next;
		}
		cout<<"]";
		firstNode = firstNode->next;
	}
	
}
