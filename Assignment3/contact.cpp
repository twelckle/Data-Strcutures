#include<iostream>
#include<fstream>
#include "contact.h"
using namespace std;

//constructor.
Contact::Contact(string fname, string lname, string email, string primaryPhone, string city, string country, bool isFav){
	this->fname = fname;
	this->lname = lname;
	this->email = email;
	this->primaryPhone = primaryPhone;
	this->city = city;
	this->country = country;
	this->isFav = isFav;
}

//setter for favorite. 
void Contact::setFav(bool boolfav){
	isFav = boolfav;
}

// returns key of the object
string Contact::getKey(){
	return (fname + lname);
}

//print function for a Contact object
void Contact::print(){
	cout<<fname<<", ";
	cout<<lname<<", ";
	cout<<email<<", ";
	cout<<primaryPhone<<", ";
	cout<<city<<", ";
	cout<<country<<", ";
	cout<<isFav<<endl;
}

//print to the file the attributes. 
void Contact::printForExport(ofstream& output){
	output<<fname<<","<<lname<<","<<email<<","<<primaryPhone<<","<<city<<","<<country<<","<<isFav<<endl;
}

//getter for Fav
bool Contact::getFav(){
	return isFav;
}

//setter for Fname
void Contact::setFirstName(){
	string input;
	cout<<"What would you like to change the first name to: ";
	cin>>input;
	fname = input;
}

//setter for Lname
void Contact::setLastName(){
	string input;
	cout<<"What would you like to change the last name to: ";
	cin>>input;
	lname = " "+input;
}

//setter for Email
void Contact::setEmail(){
	string input;
	cout<<"What would you like to change the email to: ";
	cin>>input;
	email = input;
}

//setter for phone#
void Contact::setPhone(){
	string input;
	cout<<"What would you like to change the phone number to: ";
	cin>>input;
	primaryPhone = input;
}

//setter for city
void Contact::setCity(){
	string input;
	cout<<"What would you like to change the city to: ";
	cin>>input;
	city = input;
}

//setter for country
void Contact::setCountry(){
	string input;
	cout<<"What would you like to change the country to: ";
	cin>>input;
	country = input;	
}