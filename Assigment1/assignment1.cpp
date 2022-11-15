//============================================================================
// Name         : Assignment.cpp
// Author       : Theo Welckle
// Version      : 1.0
// Date Created : Feb 11
// Date Modified: Feb 11
// Copyright    : All rights are reserved
// Description  : A Simple Fitness Center Management System
//============================================================================

#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include"admin.h"
#include"fitness.h"
#include"member.h"

using namespace std;

//========================================================================================================================================
//Functions for logging in

template <typename T, typename M>
bool checkUserAndPass(T array, int size, string username, string password, M& user){
	for(int i = 0; i<size; i++){
		if(array[i] == NULL) break;//checks to see if all possible objects have been checked
		if(array[i]->userName == username && array[i]->password == password){ //if objects username and password are equal to the ones provided by the user.
			user = array[i];
			return true;
		}
	}
	return false;
}


template <typename T, typename M>
bool login(T **array, int sizeOfArrays, M& user){

	string username;
	string password; 

	cout<<endl<<"Please enter your username: ";
	cin>>username;
	cout<<"Please enter your password: ";
	cin>>password;

	//This checks if the objects in memory match have attributes that match the username and password provided by user. 
	return(checkUserAndPass(array, sizeOfArrays, username, password, user));

}

//========================================================================================================================================
//Creates files for all three arrays and stores their information in their respective text files. 
//Since all three arrays have slightly different attributes (+ attribute names) I decided against a template.
void quitProgram(FitnessClass** arr1, Admin** arr2, Member** arr3, int sizeOfArrays){

	//Save info of Fitness Classes (Class ID, Class Name, Class date, Class time,Maximum capacity, Room number) to FitnessClassesTable.txt
	ofstream fout("FitnessClassesTable.txt");
	if(fout){
		for(int i=0; i<sizeOfArrays; i++){
			if(arr1[i]==NULL) break;
			else{
				fout<<arr1[i]->className<<", "<<arr1[i]->classDate<<", "<<arr1[i]->classTime
					<<", "<<arr1[i]->maxCapacity<<", "<<arr1[i]->roomNumber<<endl;
			}

		}
	}
	else{
		perror("");
	}


	//Save info of Admin (Admin ID,First name, Last name, Username, Password) to AdminsTable.txt
	ofstream aout("AdminsTable.txt"); 
	if(aout){
		for(int i=0; i<sizeOfArrays; i++){
			if(arr2[i]==NULL) break;
			else{
				aout<<arr2[i]->adminID<<", "<<arr2[i]->firstName<<", "<<arr2[i]->lastName
					<<", "<<arr2[i]->userName<<", "<<arr2[i]->password<<endl;
			}

		}
	}
	else{
		perror("");
	}


	//Save info of Member (Member ID,First name, Last name, Username, Password) to MembersTable.txt
	ofstream mout("MembersTable.txt"); 
	if(mout){
		for(int i=0; i<sizeOfArrays; i++){
			if(arr3[i]==NULL) break;
			else{
				mout<<arr3[i]->memberID<<", "<<arr3[i]->firstName<<", "<<arr3[i]->lastName
					<<", "<<arr3[i]->userName<<", "<<arr3[i]->password<<endl;
			}

		}
	}
	else{
		perror("");
	}

}

//========================================================================================================================================
//Print out commands for terminal-based user interface
void listAdminCommands(){

	cout<<endl<<endl;
	cout<<"1) Register a new Admin"<<endl;
	cout<<"2) Register a new member"<<endl;
	cout<<"3) Add a fitness class"<<endl;
	cout<<"4) Delete a fitness class"<<endl;
	cout<<"5) Update the details of a fitness class"<<endl;
	cout<<"6) Display the Classes with Vacancies"<<endl;
	cout<<"7) Log out"<<endl;
	cout<<"8) Quit program"<<endl<<endl;
	cout<<"Enter the number of the required action: [1-7]: ";

}

void listMemberCommands(){
	cout<<endl<<endl;
	cout<<"1) Book a Class"<<endl;
	cout<<"2) Cancel a Booking"<<endl;
	cout<<"3) View classes with vacancies"<<endl;
	cout<<"4) Log out"<<endl;	
	cout<<"5) Quit program"<<endl<<endl;
	cout<<"Enter the number of the required action: [1-4]: ";

}


void printClassDetails(FitnessClass* fitClass){
	cout<<endl<<endl;
	cout<<"This class is available: "<<endl;
	cout<<"Class Name: "<<fitClass->className<<endl;
	cout<<"Class Date: "<<fitClass->classDate<<endl;
	cout<<"Class Time: "<<fitClass->classTime<<endl;
	cout<<"Room Number: "<<fitClass->roomNumber<<endl;
	cout<<"Class ID: "<<fitClass->classID<<endl;
}

//========================================================================================================================================

//Deallocate the objects stored in the big arrays. Called at the very end of main() for all three big arrays. 
template <typename T>
void deallocate(T arr, int sizeOfArrays){
	for(int i = 0; i<sizeOfArrays; i++){
		delete arr[i];
	}
}

//This is a function availible to all members once logged in. It 
void viewClassesWithVacancies(FitnessClass** fitClassArr, int sizeOfArrays){
	bool printed = false;
	for(int i = 0; i<sizeOfArrays; i++){
		if(fitClassArr[i]==NULL) break;
		else{
			if(fitClassArr[i]->spotsLeft>0){
				printClassDetails(fitClassArr[i]);
				printed = true;

			}
		}
	}
	if(!printed) cout<<"No classes are currently vacant"<<endl;
}

//========================================================================================================================================
//Corresponding Controls that go with the print outs for the terminal-based user interface. Calls the correct function if necessary.
bool adminControls(Admin** adminArr, Member** memberArr, FitnessClass** fitClassArr, int sizeOfArrays, Admin* user){

	string userInput;
	
	do{
		listAdminCommands();
		cin>>userInput;
		if(userInput == "1")		user->registerAdmin(adminArr, sizeOfArrays);
		else if(userInput == "2")   user->registerMember(memberArr, sizeOfArrays);
		else if(userInput == "3")	user->addFitnessClass(fitClassArr, sizeOfArrays);
		else if(userInput == "4")	user->deleteFitnessClass(fitClassArr, sizeOfArrays);
		else if(userInput == "5")	user->updateClassDetails(fitClassArr, sizeOfArrays);
		else if(userInput == "6")   viewClassesWithVacancies(fitClassArr,sizeOfArrays);
		else if(userInput == "7")	return false;
		else if(userInput == "8")	return true;
		else cout<<"Invalid Entry"<<endl;

	}
	
	while(userInput != "7");

	return false;


}

bool memberControls(FitnessClass** fitClassArr, int sizeOfArrays, Member* user){
	string userInput;

	do{
		listMemberCommands();
		cin>>userInput;
		if(userInput == "1")		user->bookAClass(fitClassArr,sizeOfArrays,user);
		else if(userInput == "2")   user->cancelBooking(fitClassArr,sizeOfArrays,user);
		else if(userInput == "3")	viewClassesWithVacancies(fitClassArr,sizeOfArrays);
		else if(userInput == "4")	return false;	
		else if(userInput == "5")	return true;
		else cout<<"Invalid Entry"<<endl;

	}
	while(userInput != "4");

	return false;
}

//========================================================================================================================================

int main(){

	int sizeOfArrays = 4;

	//Creating Admin Array that stores Admin object.
	Admin* adminArr[sizeOfArrays];
	for(int i=0; i<sizeOfArrays; i++) adminArr[i] = NULL;


	//Creating Member Array that stores member objects
	Member* memberArr[sizeOfArrays];
	for(int i=0; i<sizeOfArrays; i++) memberArr[i] = NULL;

	//Creating FitnessClass Array that stores FitnessClass objects
	FitnessClass* fitClassArr[sizeOfArrays];
	for(int i=0; i<sizeOfArrays; i++) fitClassArr[i]=NULL;

	//First Admin Object
	adminArr[0] = new Admin("admin", "admin", "admin1", "admin1", 1);


	//========================================================================================================= 
	//Logining in
	string userType;

	cout<<endl<<"Welcome ot the fitness management system!"<<endl;
	while(true){
		bool breakLoop = false;
		do{
			cout<<"Please enter the category of your account before logging in: [admin/member]"<<endl;
			cin>>userType;

		}
		while(userType!="Admin"&&userType!="admin"&&userType!="Member"&&userType!="member");


		while(true){
			//if admin is logging in, admin login is called along with the corresponding admin controls
			if(userType=="Admin"||userType=="admin") {
				Admin* user;
				if(login(adminArr, sizeOfArrays, user)){
					cout<<endl<<endl<<"Welcome back!"<<endl;
					breakLoop = adminControls(adminArr, memberArr, fitClassArr, sizeOfArrays, user);
					break;
				} 
			}
			//if member is logging in, member login is called along with the corresponding member controls
			else if(userType=="Member"||userType=="member"){
				Member* user;
				if(login(memberArr, sizeOfArrays,user)){
					cout<<endl<<endl<<"Welcome back "<<endl;
					breakLoop = memberControls(fitClassArr,sizeOfArrays,user);
					break;
				}
			}

			cout<<"Do not recognize username or password. Try again"<<endl;
			
		}
		if(breakLoop) break;
	}


	//Save data to respective files
	quitProgram(fitClassArr, adminArr, memberArr,sizeOfArrays);
	cout<<endl<<"Thank you for using the management system!"<<endl<<endl;

	//deallocate memory. 
	deallocate(memberArr, sizeOfArrays);
	deallocate(fitClassArr, sizeOfArrays);
	deallocate(adminArr, sizeOfArrays);

	return 0;
}

//========================================================================================================================================
