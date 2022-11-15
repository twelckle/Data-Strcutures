
//=================================================================================
// Name         : DS Assignment#3 
// Author       : 
// Version      : 1.0
// Date Created : 03-20-2022
// Date Modified: 
// Description  : Starter Code for Contact Management System using BST Tree in C++
// Copyright © 2022 Khalid Mengal and Mai Oudah. All rights reserved.
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>

#include "contact.h"
#include "contactbst.h"
#include "myvector.h"

//==========================================================
//list commands
void listCommands()
{
	cout<<"----------------------------------"<<endl;
	cout<<"import <path>      :Import contacts from a CSV file"<<endl
		<<"export <path>      :Export contacts to a CSV file"<<endl
		<<"add                :Add a new contact"<<endl
		<<"edit <key>         :Update a contact's details"<<endl
		<<"del <key>          :Delete a contact"<<endl
		<<"searchFor <key>    :Search for a contact"<<endl
		<<"markfv <key>       :Mark as favourite"<<endl
		<<"umarkfv <key>      :Unmark as favourite"<<endl
		<<"printASC           :Print contacts in ascending order"<<endl
		<<"printDES           :Print contacts in descending order"<<endl
		<<"printfv            :Print all favourite contacts"<<endl
		<<"help               :Display the available commands"<<endl
		<<"exit               :Exit the program"<<endl;
}
//==========================================================
//creates new contact when add is called.
Contact* createNewContact(){

	string fname;
	string lname;
	string email;
	string phoneN;
	string city;
	string country;
	bool favorite;
	string fav;

	cout<<"Please enter the deatails of the contact: "<<endl;
	cout<<"First Name: ";
	cin>>fname;
	cout<<"Last Name: ";
	cin>>lname;
	cout<<"Email: ";
	cin>>email;
	cout<<"Phone#: ";
	cin>>phoneN;
	cout<<"City: ";
	cin>>city;
	cout<<"Country: ";
	cin>>country;
	cout<<"Do you want to add the contact in your favorites (y/n): ";
	cin>>fav;

	//insures that input for fav is binary
	while(fav != "y" and fav != "n"){
		cout<<"Invalid Input"<<endl;
		cout<<"Do you want to add the contact in your favorites (y/n): ";
		cin>>fav;
	}
	if(fav == "y") favorite = true;
	else if(fav == "n") favorite = false;

	//this is the way lastname appears in the example file. This is why I am doing this. 
	lname = " " + lname;

	//creates and returns the new contact.
	Contact* newContact = new Contact(fname, lname, email, phoneN, city, country, favorite);
	cout<<"Successfully added!"<<endl;
	getline(cin,fav);
	return newContact;
}
//==========================================================
int main(void)
{
	//The tree
	ContactBST myContactBST;

	while(true)
	{
		//the next 7 lines of code are from lab 9 of a class called Data Structures at NYUAD taught by Mai Oudah.
		//and TA by Khalid Mengal
		//basically gets the input of the user and uses the information to call the respective functions
		listCommands();
		cout<<">";
		string userInput;
		string command;
		string key;

		getline(cin,userInput);

		stringstream sstr(userInput);
		getline(sstr,command,' ');
		getline(sstr,key);
		//if import is called, calls the importCSV with the key being the path.
		if(command =="import"){
			int number = myContactBST.importCSV(myContactBST.getRoot(), key);
			cout<<number<<" contacts were added!"<<endl;
		}

		//exportCSV is called with key being the path
		else if(command =="export"){
			int number = myContactBST.exportCSV(myContactBST.getRoot(), key);
			cout<<number<<" contact added to file!"<<endl;
		}

		//adds element to the tree
		else if(command =="add"){
			Contact* newContact = createNewContact();
			myContactBST.insert_helper(newContact->getKey(), newContact);
		}

		//calls update function in the BST class.
		else if(command =="edit"){
			myContactBST.update(myContactBST.getRoot(),key);
		}

		//calls remove function in BST class.
		else if(command =="del" or command == "delete"){
			myContactBST.remove_helper(key);
		}

		//searches for element in the tree
		else if(command =="searchFor"){
			Node* searchNode = myContactBST.search(myContactBST.getRoot(),key);
			if(searchNode!=NULL) searchNode->getData()->print();
		}

		//calls markFav function is BST class.
		else if(command =="markfv"){
			myContactBST.markFav(myContactBST.getRoot(),key);
		}

		//calls unmarkFav function is BST class.
		else if(command =="umarkfv"){
			myContactBST.unmarkFav(myContactBST.getRoot(),key);
		}

		//calls printASC function is BST class.
		else if(command =="printASC"){
			if(myContactBST.getRoot()==NULL) cout<<"System is Empty!"<<endl;
			else myContactBST.printASC(myContactBST.getRoot());
		}

		//calls printDES function is BST class.
		else if(command =="printDES"){
			if(myContactBST.getRoot()==NULL) cout<<"System is Empty!"<<endl;
			else myContactBST.printDES(myContactBST.getRoot());
		}

		//calls printFav function is BST class.
		else if(command =="printfv"){

			if(myContactBST.getRoot()==NULL) cout<<"System is Empty!"<<endl;
			else myContactBST.printFav(myContactBST.getRoot());
		}

		//if help, just continues
		else if( command == "help") continue;

		//if exit breaks loop
		else if( command == "exit"){
			break;
		}
		else cout<<"Invalid command !!!"<<endl;
	}

	return 0;
}