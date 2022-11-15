#include <iostream>
#include "flightticket.h"
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

//Constructor
Flight_Ticket::Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date){
	this->companyName = companyName;
	this->flightNumber = flightNumber;
	this->country_of_origin = country_of_origin;
	this->country_of_destination = country_of_destination;
	this->stopOver = stopOver;
	this->price = price;
	this->time_of_departure = time_of_departure;
	this->time_of_arrival = time_of_arrival;
	this->date = date;
}

//Empty constructor
Flight_Ticket::Flight_Ticket(){
	companyName = "Null";
	flightNumber = 0;
	country_of_origin = "Null";
	country_of_destination = "Null";
	stopOver = "Null";
	price = "Null";
	time_of_departure = "Null";
	time_of_arrival = "Null";
	date = "Null";
}

//returns the key in lower case.
string Flight_Ticket::getKey(){
	string temporary = companyName;
	transform(temporary.begin(), temporary.end(), temporary.begin(), ::tolower);
	return temporary + "," + to_string(flightNumber);
}

//prints the object. 
void Flight_Ticket::print(){
	cout<<companyName<<","<<flightNumber<<","<<country_of_origin<<","<<country_of_destination<<","<<stopOver<<","<<price<<","<<time_of_departure<<","<<time_of_arrival<<","<<date<<endl;
}

//this is a print for the find operation.
void Flight_Ticket::printForFind(){
	cout<<"Company Name: "<<companyName<<endl;
	cout<<"Flight Number: "<<flightNumber<<endl;
	cout<<"Country of Origin: "<<country_of_origin<<endl;
	cout<<"Country of Destination: "<<country_of_destination<<endl;
	cout<<"Stop Over: "<<stopOver<<endl;
	cout<<"Price: "<<price<<endl;
	cout<<"Time of Departure: "<<time_of_departure<<endl;
	cout<<"Time of Arrival: "<<time_of_arrival<<endl;
	cout<<"Date: "<<date<<endl;
}

//returns the country of destination.
string Flight_Ticket::getCountry_of_destination(){
	return country_of_destination;
}

//returns the date.
string Flight_Ticket::getDate(){
	string tempDate = date;
	transform(tempDate.begin(), tempDate.end(), tempDate.begin(), ::tolower);
	return tempDate;
}

//== overload for comparison
bool Flight_Ticket::operator==(const Flight_Ticket& compared){
	return this->companyName == compared.companyName and 
		   this->flightNumber == compared.flightNumber and
		   this->country_of_origin == compared.country_of_origin and
		   this->country_of_destination == compared.country_of_destination and
		   this->stopOver == compared.stopOver and
		   this->price == compared.price and
		   this->time_of_departure == compared.time_of_departure and
		   this->time_of_arrival == compared.time_of_arrival and
		   this->date == compared.date;
}

//print for print to file. 
void Flight_Ticket::printToFile(ofstream& output){
	output<<companyName<<','<<flightNumber<<','<<country_of_origin<<','<<country_of_destination<<','<<stopOver<<','<<price<<','<<time_of_departure<<','<<time_of_arrival<<','<<date<<endl;
}