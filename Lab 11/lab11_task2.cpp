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
		HashNode **nodeArray;		    // Array of Pointers to Hash Nodes
		//Comment out the line above and uncomment line below for Task 3
		//list<HashNode> *buckets;		// Array of lists of type Hash Nodes
		int size;					    //Current Size of HashTable
		int capacity;				    // Total Capacity of HashTable
		int collisions;					// Total Number of Collisions
	public:
		HashTable(int capacity);
		unsigned long hashCode(string key);
		void insert(string key, string value);
		string search(string key);
		//void erase(string key); //uncomment it for Task3
		int getSize();
		int getCollisions();
		~HashTable();

};
HashTable::HashTable(int capacity)
{
	nodeArray = new HashNode*[capacity];			// Array of Pointers to Hash Nodes
	for(int i=0; i<capacity; i++)
		nodeArray[i] = nullptr;
	//Comment out the line above and uncomment line below for Task 3
	//buckets = new list<HashNode>[capacity];	  //Array of a list/chain
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
	//first use your hash function to get the index where the code should be. 
	int index = abs(int(hashCode(key)));
	//make the node.
	HashNode* insertNode = new HashNode(key, value);

	//traverse the array size until an open index is found. Once found add Node to that index.
	//Since the size of the array is larger then the amount of input data and the size of array is a prime number, we will always reach a empty index.
	for(int i = 0; i<capacity; i++){
		if(nodeArray[index] == nullptr){
			nodeArray[index] = insertNode;
			size++;
			break;	
		}
		//use quadratic probing making sure the index does not go out of range of the array. 
		index = int((index+pow(i,2))) % capacity;
		collisions++;
	}

}


//===================================================
string HashTable::search(string key)
{
	//first use your hash function to get the index where the code should be. 
	int index = abs(int(hashCode(key)));;

	//traverse the array size until the key is found (return value), or until a nullptr is reached in which case the key doesn't exist in the array.
	for(int i = 0; i<capacity; i++){
		if(nodeArray[index] == nullptr){
			return "This does not exist in the array";
		}
		else if(nodeArray[index]->key == key){
			return nodeArray[index]->value;
		}
	//continue to update the index as when inserting we used quadratic probing to insert the node.
	index = int((index+pow(i,2))) % capacity;
	}
	return "";

}
//=====================================================
// Uncomment it for Task 3
/*void HashTable::erase(string key)
{
	//TODO
}*/
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
	//delete every Node in the list, then delete the list.
	for(int i = 0; i<capacity; i++){
		delete nodeArray[i];
	}
	delete[] nodeArray;
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
		//else if(command == "erase")	  myHashTable.erase(argument1);
		else if(command == "help")	  cout<<"Commands available \ninsert <key,value>\nsearch <key>\nerase <key>"<<endl;
		else if(command == "exit")	  break;
		else cout<<"Invalid command !!!"<<endl;
	}
	return 0;
}