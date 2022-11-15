#ifndef FlightHASHTABLE_H
#define FlightHASHTABLE_H

#include<iostream>
#include<string>
#include<math.h>
#include "flightticket.h"
#include "mylist.h"
// include additional header files as needed

using namespace std;

template <typename T>
class MyList;


class HashNode
{
	private:
		string key; // key = companyName+flightNumber
		Flight_Ticket value;

	public:
		HashNode(string key, Flight_Ticket value)
		{
			this->key = key;
			this->value = value;
		}
		
		void print(){
			value.print();
		}

		void printForFind(){
			value.printForFind();
		}

		string getDate(){
			return value.getDate();
		}

		Flight_Ticket getValue(){
			return value;
		}

		friend class FlightHASHTABLE;
};

//=============================================================================
class FlightHASHTABLE
{
	private:
		MyList<HashNode> *buckets;				//List of Buckets, Please create your own List Class called MyList
		int size;					    //Current Size of HashTable
		int capacity;				    // Total Capacity of HashTable
		int collisions; 
		// add more attributes as needed
	public:
		FlightHASHTABLE();						//constructor
		~FlightHASHTABLE();						//destructor
		long hashCode(string key); 						//implement and test different hash functions 
		long hashCode1(string key);
		long hashCode2(string key);
		int importCSV(string path); 			//Load all the flight-tickets from the CSV file to the HashTable
		int exportCSV(string path); 			//Export all the flight-tickets from the HashTable to a CSV file in an ascending order		
		int count_collisions();					//return the number of collisions on the HashTable
		int add(Flight_Ticket* data);			//add new flight to the HashTable
		bool addByUser(Flight_Ticket* data); 	//an add that allows the user to add a flight to the hashTable.
		void removeRecord (string companyName, int flightNumber);	//Delete a record with key from the hashtable
		void find(string companyName, int flightNumber);		//Find and Display records with same key entered 
		void allinday(string date);  					//Find and Display records with same day entered
		void printASC(string companyName, int flightNumber);  		//display the collisions for the entered key in an ascending order 

		// add more methods as needed	
};

#endif
