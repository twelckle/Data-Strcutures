#ifndef FLIGHT_TICKET_H
#define FLIGHT_TICKET_H

#include<iostream>
#include<string>
using namespace std;

class Flight_Ticket
{
	private:
		string companyName;
		int flightNumber;
		string country_of_origin;
		string country_of_destination;
		string stopOver;
		string price;
		string time_of_departure;
		string time_of_arrival;
		string date;

	public:
		Flight_Ticket(); //constructor
		Flight_Ticket(string companyName, int flightNumber, string country_of_origin, string country_of_destination, string stopOver, string price, string time_of_departure, string time_of_arrival, string date);//constructor
		string getKey();//returns key
		string getCountry_of_destination();//returns country of destination
		string getDate();//returns date.
		void print(); //prints all elements
		void printForFind(); //prints elements in a ceratin format
		bool operator==(const Flight_Ticket& compared); //checks to see if parameter Flight_ticket is the same as the current flight ticket. Operator overload
		void printToFile(ofstream& output); //prints to the export file.
		// add additional methods as needed
};

#endif
