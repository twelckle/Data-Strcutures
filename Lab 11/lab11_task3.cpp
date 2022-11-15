//============================================================================
// Name         : lab11.cpp
// Author       : Khalid Mengal
// Version      : 1.0
// Date Created : 25-04-2020
// Date Modified: 18-11-2021 
// Copyright    : All rights are reserved
// Description  : HashTable Implmentation using C++
//============================================================================

#include<iostream>
#include<fstream>
#include<sstream>
#include<math.h>
#include<string>
#include<list>
#include<cstdlib>

using namespace std;
class HashNode
{
	private:
		string key;
		string value;
	public:
		HashNode(string key, string value)
		{
			this->key = key;
			this->value = value;
		}
		friend class HashTable;

};

class HashTable
{
	private:
		//HashNode **nodeArray;		    // Array of Pointers to Hash Nodes
		//Comment out the line above and uncomment line below for Task 3
		list<HashNode> *buckets;		// Array of lists of type Hash Nodes
		int size;					    //Current Size of HashTable
		int capacity;				    // Total Capacity of HashTable
		int collisions;					// Total Number of Collisions
	public:
		HashTable(int capacity);
		unsigned long hashCode(string key);
		void insert(string key, string value);
		string search(string key);
		void erase(string key); //uncomment it for Task3
		int getSize();
		int getCollisions();
		~HashTable();

};
HashTable::HashTable(int capacity)
{
	buckets = new list<HashNode>[capacity];	//Array of a list/chain	
	this->capacity = capacity;
	this->size = 0;
	this->collisions = 0;
}

unsigned long HashTable::hashCode(string key)
{
	int hashKey = 0;
	//for every letter in the string, multply its asci value with 33 to the power of the position of the character. 
	//add this value to the hashKey, and make sure the hashkey value is not greater then the value of the array capcity. 
	for(int i = 0; i<key.length(); i++){
		hashKey = (hashKey + key[i] * (int(pow(33,i))))%capacity; //chose 33 because of the class slides saying certain prime numbers decrease collisions.
	}
	return hashKey;
		
}
//================================================
void HashTable::insert(string key, string value)
{
	//insert is constant time for seperate chaining.
	//find index. Create Node. Add node to the end of the list at the index in the array.
	int index = abs(int(hashCode(key)));
	HashNode newEntry = HashNode(key, value);
	buckets[index].push_back(newEntry);
	size++;

}
//===================================================
string HashTable::search(string key)
{
	//get the index.
	int index = abs(int(hashCode(key)));
	list<HashNode>::iterator it;
	int i = 0;
	//iterate over the list, if key is found in the list return the value. otherwise return not found. 
	for(it = buckets[index].begin(); it!=buckets[index].end(); it++){
		if(it->key == key) return it->value;
		i++;
	}

	return "Not found";
}
//=====================================================
// Uncomment it for Task 3
void HashTable::erase(string key)
{
	//get index
	int index = abs(int(hashCode(key)));
	list<HashNode>::iterator it;
	int i = 0;
	bool inArray = false;

	//iterate over the list, if key is found erase it from the list.
	for(it = buckets[index].begin(); it!=buckets[index].end(); it++){
		if(it->key == key){
			buckets[index].erase(it);
			cout<<"Done"<<endl;
			inArray = true;
		}
		i++;
	}
	if(!inArray){
		cout<<"Not in system"<<endl;
	}


}
//=====================================================
int HashTable::getSize()
{
	return this->size;
}
//======================================================
int HashTable::getCollisions()
{
	return this->collisions;
}
//======================================================
HashTable::~HashTable()
{
	delete[] buckets;
}

//======================================================
int main(void)
{
	ifstream fin;
	fin.open("zipcodes.csv");
	if(!fin){
		cout<<"Can not open the file <zipcodes.txt>...!"<<endl;
		exit(-1);
	}

	string line;
	HashTable myHashTable(24851);// Prime number bigger than >24850 (19880*1.25);
	getline(fin,line);  //skip first line
	while(!fin.eof())
	{
		string key, value;
		getline(fin,key,',');
		getline(fin,value);
		cout<<key<<":"<<value<<endl;
		myHashTable.insert(key,value);

	}
	fin.close();
	cout<<"==================================================="<<endl;
	cout<<"Hash Table size = "<<myHashTable.getSize()<<endl;
	cout<<"Total Number of Collisions = "<<myHashTable.getCollisions()<<endl;
	cout<<"Avg. Number of Collisions Per Entry = "<<float(myHashTable.getCollisions())/myHashTable.getSize()<<endl;
	cout<<"==================================================="<<endl;

	string user_input, command, argument1, argument2;

	while(true)
	{
	
		cout<<">";
		getline(cin,user_input);

		stringstream sstr(user_input);
		getline(sstr,command,' ');
		getline(sstr,argument1,',');
		getline(sstr,argument2);

			if(command == "search") cout<<"Zip code for "<<argument1<<" is: "<<myHashTable.search(argument1)<<endl;
		else if(command == "insert") {myHashTable.insert(argument1,argument2);}
		//Uncomment following line for the Task 3
		else if(command == "erase")	  myHashTable.erase(argument1);
		else if(command == "help")	  cout<<"Commands available \ninsert <key,value>\nsearch <key>\nerase <key>"<<endl;
		else if(command == "exit")	  break;
		else cout<<"Invalid command !!!"<<endl;
	}
	return 0;
}