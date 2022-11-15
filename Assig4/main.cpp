
//=================================================================================
// Name         : DS Assignment#4 
// Author       : 
// Version      : 1.0
// Date Created : Apr-17-2022
// Date Modified: 
// Description  : Starter Code for Flight-Ticket Management System using HASH TABLE in C++
//=================================================================================
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<time.h>

#include "flightticket.h"
#include "flighthashtable.h"

//==========================================================
void listCommands()
{
	cout<<"\n----------------------------------"<<endl;
	cout<<"import <path>      	:Import flight-tickets from a CSV file"<<endl
		<<"export <path>      	:Export flight-tickets to a CSV file"<<endl
		<<"count_collisions   	:Print number of collisions"<<endl
		<<"add                	:Add a new flight-ticket"<<endl
		<<"delete <key>       	:Delete a flight-ticket"<<endl
		<<"find <key>         	:Find a flight-ticket's details"<<endl
		<<"allinday <date>    	:Display all flight-tickets in a day"<<endl
		<<"printASC <key>     	:Print flight-tickets in ascending order"<<endl
		<<"exit               	:Exit the program"<<endl;
}
//==========================================================

// to be completed with all the necessary method definitions

//==========================================================
int main(void)
{
	FlightHASHTABLE myFlightHASHTABLE;

	while(true)
	{
		//list commands, get user input and depending on input call the corresponding function.
		listCommands();
		cout<<">";
		string userInput;
		string command;
		string key1;
		string key2;

		getline(cin,userInput);

		stringstream sstr(userInput);
		getline(sstr,command,' ');
		getline(sstr,key1,',');
		getline(sstr,key2);

		//imports file into the code. 
		if(command == "import"){
			int number = myFlightHASHTABLE.importCSV(key1);
			cout<<number<<" contacts were added!"<<endl;
		}

		//exports data to a file.
		else if(command == "export"){
			int number = myFlightHASHTABLE.exportCSV(key1);
			cout<<number<<" contacts were exported!"<<endl;
		}

		//returns the number of collisions.
		else if(command == "count_collisions"){
			cout<<myFlightHASHTABLE.count_collisions()<<endl;
		}

		//adds a piece of data depending on the users input. 
		else if(command == "add"){
			string companyName, country_of_origin, country_of_destination, stopover, price, time_of_departure, time_of_arrival, date, catchstring;
			int flight_number;
			cout<<"Please enter the details of the flight-ticket: "<<endl;
			cout<<"Company Name: ";
			cin>>companyName;
			cout<<"Flight Number: ";
			cin>>flight_number;
			cout<<"Country of Origin: ";
			cin>>country_of_origin;
			cout<<"Country of Destination: ";
			cin>>country_of_destination;
			cout<<"Stopover: ";
			cin>>stopover;
			cout<<"Price: ";
			cin>>price;
			cout<<"Time of Departure: ";
			cin>>time_of_departure;
			cout<<"Time of Arrival: ";
			cin>>time_of_arrival;
			cout<<"Date: ";
			cin>>date;
			getline(cin,catchstring);

			Flight_Ticket* newFlight = new Flight_Ticket(companyName, flight_number, country_of_origin, country_of_destination, stopover, price, time_of_departure, time_of_arrival, date);
			bool added = myFlightHASHTABLE.addByUser(newFlight);
			if(added) cout<<"Successfully beend added!"<<endl;
			else{
				cout<<"Element Already Exisits"<<endl;
			}

		}

		//detletes data point depedning on user unput.
		else if(command == "delete"){
			myFlightHASHTABLE.removeRecord(key1, stoi(key2));
		}

		//prints all data that correspond to a specified key.
		else if(command == "find"){
			clock_t begin,end;
			begin = clock();
			myFlightHASHTABLE.find(key1, stoi(key2));
			end = clock();
			double difference = double(end - begin)/CLOCKS_PER_SEC;
			cout<<endl;
			cout<<"Time Taken: "<<difference<<" seconds"<<endl;
		}

		//prints all data from a certain day.
		else if(command == "allinday"){
			myFlightHASHTABLE.allinday(key1);
		}

		//prints in ascending order of a key given.
		else if(command == "printASC"){
			myFlightHASHTABLE.printASC(key1, stoi(key2));
		}
		else if(command == "exit") break;
	}
	return 0;
}
