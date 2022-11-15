#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include"member.h"
#include"admin.h"
#include"fitness.h"

using namespace std;

//to ensure there are no random NULL values in the middle of the list. 
void cleanUpList(FitnessClass** arr, int numberLeft, int sizeOfArrays){

	//if next object in arr isn't NULL and not out of bounds -> switch the values of right and left. recursively call function until NULL is at the back of the array.
	if(!(arr[numberLeft+1]==NULL)&&!(numberLeft+1>=sizeOfArrays)){ 
		arr[numberLeft] = arr[numberLeft+1];
		arr[numberLeft+1] = NULL;
		cleanUpList(arr, numberLeft+1, sizeOfArrays);
	}

}

//printing out change fitness class user options.
void updateClassOptions(){
	cout<<endl<<"What data would you like to update: "<<endl;
	cout<<"1) Class ID"<<endl;
	cout<<"2) Class Name"<<endl;
	cout<<"3) Cladd Date"<<endl;
	cout<<"4) Class time"<<endl;
	cout<<"5) Maximum capacity"<<endl;
	cout<<"6) Room number"<<endl<<endl;
	cout<<"Please enter a number [1-6]: ";



}

//Turns string into all lowercase using ASCI values. 
string toLower(string name){
	for(int i=0; i<name.length(); i++){
		if(name[i]>='A'&&name[i]<='Z'){
			name[i]=name[i]+32;
		}
	}
	return name;
}

//Constructor
Admin::Admin(string first, string last, string user, string pass, int admID) {

	firstName = first;
	lastName = last;
	userName = user;
	password = pass;
	adminID = admID;

}


void Admin::registerAdmin(Admin **list, int sizeOfArrays){
	for(int i = 0; i<sizeOfArrays; i++){ //loops entire array until a NULL is found. 
		if(list[i] == NULL){
			string firstname;
			string lastname;
			int id = rand()%9000 + 1000; //Creates random 4 digit ID.
			string username;
			string password;

			//User input
			cout<<"What is the new Admin's first name: ";
			cin>>firstname;
			cout<<"What is the new Admin's last name: ";
			cin>>lastname;


			//creates username and password that are data type string which have different 4 digit random values. 
			username = toLower(firstname) + to_string(id);
			password = toLower(lastname) + to_string(rand()%9000 + 1000);

			//create new object of Admin and assign to big array in correspodning index value. 
			list[i] = new Admin(firstname, lastname, username, password, id);
			cout<<"Successfully registered new Admin!"<<endl;
			break; 
		}

	}
}

void Admin::registerMember(Member **list, int sizeOfArrays){
	for(int i = 0; i<sizeOfArrays; i++){
		if(list[i] == NULL){ //loops entire array until a NULL is found. 
			string firstname;
			string lastname;
			int id = rand()%9000 + 1000;
			string username;
			string password;

			//User input
			cout<<"What is the new Member's first name: ";
			cin>>firstname;
			cout<<"What is the new Member's last name: ";
			cin>>lastname;

			//creates username and password that are data type string which have different 4 digit random values. 
			username = toLower(firstname) + to_string(id);
			password = toLower(lastname) + to_string(rand()%9000 + 1000);

			//create new object of Member and assign to big array in correspodning index value.
			list[i] = new Member(firstname, lastname, username, password, id);
			cout<<"Successfully registered new Member!"<<endl;
			break; 
		}

	}
}

void Admin::addFitnessClass(FitnessClass** arr, int sizeOfArrays){
	for(int i = 0; i<sizeOfArrays; i++){
		if(arr[i]==NULL){ //loops entire array until a NULL is found. 
			string cname;
			string cdate;
			string ctime;
			int maxcap;
			string rnumber;
			string cid;

			//User input
			cout<<"What is the name of the class: ";
			cin>>cname;

			cout<<"What is the date of the class: ";
			cin>>cdate;

			cout<<"What is the time of the class: ";
			cin>>ctime;

			cout<<"What is the maximum capacity of the class (please input an integer): ";
			cin>>maxcap;

			cout<<"What is the room number of the class: ";
			cin>>rnumber;

			cout<<"What is the class ID: ";
			cin>>cid;

			//create new object of FitnessClass and assign to big array in correspodning index value.
			arr[i] = new FitnessClass(cname, cdate, ctime, maxcap, rnumber, cid);
			cout<<endl<<endl<<"Succesfully created new class"<<endl;
			break;
		}
	}

}

void Admin::deleteFitnessClass(FitnessClass** arr, int sizeOfArrays){

	string inputRemoveClass;
	int counter = 0;
	bool deletedClass = false;

	//user input
	cout<<"What is the ID number of the class you would like to remove: ";
	cin>>inputRemoveClass;


	for(int i=0; i<sizeOfArrays; i++){
		if(arr[i]==NULL) break;//loops entire array until null is found. 
		else{
			if(arr[i]->classID == inputRemoveClass){ //for objects != null the classID is checked with user given ID.
				delete arr[i];
				arr[i] = NULL;
				deletedClass = true;
				cleanUpList(arr,counter, sizeOfArrays); //makes sure the array does not have a NULL in the middle of its elements. 
				cout<<"Done"<<endl;
			}
		}
		counter++;
	}

	if(!deletedClass) cout<<"Do not recognize this class ID"<<endl;
}


void Admin::updateClassDetails(FitnessClass** arr, int sizeOfArrays){

	//user input
	string inputUpdateClass;
	cout<<"What is the ID number of the class you would like to update: ";
	cin>>inputUpdateClass;


	for(int i=0; i<sizeOfArrays; i++){
		if(arr[i]==NULL){ //if loop encounter NULL then no more objects in array. ID is not recognized
			cout<<"Class ID not recognized."<<endl;
		 	break;
		}
		else{
			if(arr[i]->classID == inputUpdateClass){ //if ID is recognized by a FitnessClass object
				while(true){

					int updatePortion;
					string updateTo;
					updateClassOptions(); //prints user options

					//user input
					cin>>updatePortion;
					cout<<"What would you like to change this to: ";
					cin>>updateTo;

					//updates corresponding attribute to userinput value. 
					if(updatePortion==1){
						arr[i]->classID = updateTo;
						break;
					}
					else if(updatePortion==2){
						arr[i]->className = updateTo;
						break;
					}
					else if(updatePortion==3){
						arr[i]->classDate = updateTo;
						break;
					}
					else if(updatePortion==4){
						arr[i]->classTime = updateTo;
						break;
					}
					else if(updatePortion==5){
						arr[i]->maxCapacity = stoi(updateTo);
						arr[i]->spotsLeft = stoi(updateTo);
						break;
					}
					else if(updatePortion==6){
						arr[i]->roomNumber = updateTo;
						break;
					}
					else{
						cout<<"Invalid Input. Try again. "<<endl;
					}
				}
				cout<<"Done."<<endl;
				break;
			}	


		}
	}
}

