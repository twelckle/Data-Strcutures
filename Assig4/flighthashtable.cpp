#include<iostream>
#include<fstream>
#include<string>
#include<math.h>
#include "mylist.h"
#include "flighthashtable.h"
#include "flightticket.h"

class HashNode;

//constructor
FlightHASHTABLE::FlightHASHTABLE(){

	size = 0;
	collisions = 0;

	//This is for the 1K csv file
	capacity = 1259;
	buckets = new MyList<HashNode>[1259];
	

	//This if for the 10K csv file
	//capacity = 12503;
	//buckets = new MyList<HashNode>[12503];	
	

	//This is for the 100K csv file.
	//capacity = 125003;
	//buckets = new MyList<HashNode>[125003];	
}

//destructor
FlightHASHTABLE::~FlightHASHTABLE(){

}

//hashcode #1 in my write up. 
long FlightHASHTABLE::hashCode1(string key){
	//splits into the airline name and number.
	string name;
	string number;
	bool comma = true;
	int i = 0;


	while(i<key.length()){
		if(comma){
			if(key[i] == ',') comma = false;
			else name += key[i];
		}
		else{
			number += key[i];
		}
		i++;
	}

	//Does the cycle shift hashing on the key.
	unsigned int hashKey = 0;
	for(int i = 0; i<name.length();i++){
		hashKey = (hashKey << 5) | (hashKey >> 27);
		hashKey += (unsigned int) name[i];
	}
	//adds number to the key.
	return (hashKey+stoi(number)) % capacity;

}

//Hash code #2 in my write up.
long FlightHASHTABLE::hashCode2(string key){
	//splits into the airline name and number.
	string name;
	string number;
	bool comma = true;
	int i = 0;
	while(i<key.length()){
		if(comma){
			if(key[i] == ',') comma = false;
			else name += key[i];
		}
		else{
			number += key[i];
		}
		i++;
	}
    int hashKey = 0;
	//for every letter in the string, multply its asci value with 33 to the power of the position of the character. 
	//add this value to the hashKey, and make sure the hashkey value is not greater then the value of the array capcity. 
	for(int i = 0; i<name.length(); i++){
		hashKey = hashKey + name[i] * (int(pow(33,i))); //chose 33 because of the class slides saying certain prime numbers decrease collisions.
	}
	hashKey += stoi(number);
	return hashKey % capacity;
}			


//implement and test different hash functions 
//This is hashcode #3 in my write up.
long FlightHASHTABLE::hashCode(string key){
	//splits into the airline name and number.
	string name;
	string number;
	bool comma = true;
	int i = 0;

	while(i<key.length()){
		if(comma){
			if(key[i] == ',') comma = false;
			else name += key[i];
		}
		else{
			number += key[i];
		}
		i++;
	}

	//here I took the idea of Polynomial hashing and I just added the first and last letters together before applying the hash.
	unsigned int hashKey = 0;
	int end = key.length();
	for(int i = 0; i<end; i++){
		if(end-i<=1){
			hashKey = hashKey + (name[i]+name[end]) * (int(pow(33,i))); //chose 33 because of the class slides saying certain prime numbers decrease collisions.
			end--;
		}
		else{
			hashKey = hashKey + name[i] * (int(pow(33,i))); //chose 33 because of the class slides saying certain prime numbers decrease collisions.

		}
	}

	//add the number to the end.
	return (hashKey + stoi(number)) % capacity;

}

//Load all the flight-tickets from the CSV file to the HashTable
int FlightHASHTABLE::importCSV(string path){
	int numberOfImports = 0;
	ifstream myFile;

	//open file and read all the information into the corresponding strings.
	myFile.open(path);
	if(myFile.good() == false) return -1;
	string firstline;
	getline(myFile, firstline);
	while(myFile.good()){

		Flight_Ticket* newFlight;
		string companyName;
		string flightNumber;
		string country_of_origin;
		string country_of_destination;
		string stopOver;
		string price;
		string time_of_departure;
		string time_of_arrival;
		string date;

		getline(myFile, companyName,',');
		getline(myFile, flightNumber,',');
		getline(myFile, country_of_origin,',');
		getline(myFile, country_of_destination,',');
		getline(myFile, stopOver,',');
		getline(myFile, price,',');
		getline(myFile, time_of_departure,',');
		getline(myFile, time_of_arrival,',');
		getline(myFile, date, '\n');
		date = date.substr(0,date.length()-1);

		if(companyName == "") continue;

		//change string to int and see if the contact is a favorite or not.
		int realFlightNumber = stoi(flightNumber);

		//create new contact, new key and insert into tree.
		newFlight = new Flight_Ticket(companyName, realFlightNumber, country_of_origin, country_of_destination, stopOver, price, time_of_departure, time_of_arrival, date);
		int added = add(newFlight);
		if(added == -1) cout<<"Duplicate Item could not add"<<endl;
		else{
			numberOfImports++;
		}
	
	}
	myFile.close();
	return numberOfImports;
}

//Export all the flight-tickets from the HashTable to a CSV file in an ascending order	
int FlightHASHTABLE::exportCSV(string path){
	int numberOfExports = 0;

	//open the file, and print to the file. Keep track of number of Exports
	ofstream myFile;
	myFile.open(path);
	if(myFile.is_open()){
		//This prints the header to the file.
		myFile<<"companyName"<<','<<"flightNumber"<<','<<"country_of_origin"<<','<<"country_of_destination"<<','<<"stopOver"<<','<<"price"<<','<<"time_of_departure"<<','<<"time_of_arrival"<<','<<"date"<<endl;
		for(int i = 0; i<capacity; i++){
			if(!buckets[i].empty()){
				//calls a flightiket function with the file being the parameter. This allows the flight ticket class to print to the file. 
				numberOfExports += buckets[i].printToFile(myFile);
			}
		}
		return numberOfExports; 
	}
	//return -1 if the file does not open.
	else{
		return -1;
	}


}				

//return the number of collisions on the HashTable
int FlightHASHTABLE::count_collisions(){
	return collisions;
}				

//add new flight to the HashTable
int FlightHASHTABLE::add(Flight_Ticket* data){
	//call functino
	int index = abs(int(hashCode(data->getKey())));
	bool canCreate = true;
	//if bucket is not empty check if there is the same flight information already added in the bucket. If not then add and increase collision
	if(!buckets[index].empty()){
		canCreate = buckets[index].checkIfSame(data);
		if(canCreate == false) return -1;
		else{
			collisions++;
		}
	};

	//create entry and add to bucket.
	HashNode* newEntry = new HashNode(data->getKey(), *data);
	buckets[index].add(newEntry);
	size++;
	return 1;
}	

bool FlightHASHTABLE::addByUser(Flight_Ticket* data){	
	//Call function
	int index = abs(int(hashCode(data->getKey())));
	bool canCreate = true;
	//if bucket is not empty check if there is the same flight information already added in the bucket. If not then add and increase collision
	if(!buckets[index].empty()){
		canCreate = buckets[index].checkIfSame(data);
		if(canCreate == false) return false;
		else{
			collisions++;
		}
	}
	//create entry and add to bucket.
	HashNode* newEntry = new HashNode(data->getKey(), *data);
	buckets[index].add(newEntry);
	size++;
	return true;
}

//Delete a record with key from the hashtable
void FlightHASHTABLE::removeRecord(string companyName, int flightNumber){
	//create the key in lower case.
	transform(companyName.begin(), companyName.end(), companyName.begin(), ::tolower);
	string key = companyName + "," + to_string(flightNumber);	

	//find the hashkey and check if the key exists. If it does removeFromlist. Else prompt user that entry doesn't exist.  
	int index = abs(int(hashCode(key)));
	if(buckets[index].empty()){
		cout<<"No such entry exists"<<endl;
	}
	else{
		buckets[index].removeFromList();
	}
}
//Find and Display records with same key entered 
void FlightHASHTABLE::find(string companyName, int flightNumber){
	//create the key in lower case.
	transform(companyName.begin(), companyName.end(), companyName.begin(), ::tolower);
	string key = companyName + "," + to_string(flightNumber);

	//find the hashkey and check if the key exists. If it does print. Else prompt user that entry doesn't exist. 
	int index = abs(int(hashCode(key)));
	if(!buckets[index].empty()) buckets[index].printForFind();
	else{
		cout<<"Not Found!"<<endl;
	}
}

//Find and Display records with same day entered
void FlightHASHTABLE::allinday(string date){
	//this function goes through every position in the array and if not empty checks every object in the list to see if the date is the same. 
	//If it is then that object is printed.
	transform(date.begin(), date.end(), date.begin(), ::tolower);
	bool printed = false;
	for(int i = 0; i<capacity; i++){
		if(!buckets[i].empty()){
			bool returnbool = buckets[i].printDate(date);
			if(printed == false and returnbool == true) printed = true;
		}
	}
	if(!printed) cout<<"Not Found!"<<endl;
}

//display the collisions for the entered key in an ascending order 
void FlightHASHTABLE::printASC(string companyName, int flightNumber){

	//Gets key
	transform(companyName.begin(), companyName.end(), companyName.begin(), ::tolower);
	string key = companyName + "," + to_string(flightNumber);

	//gets hashkey. Prints if bucket isn't empty.
	int index = abs(int(hashCode(key)));
	if(!buckets[index].empty()) buckets[index].print();
	else{
		cout<<"Not Found!"<<endl;
	}

}
