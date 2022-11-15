//============================================================================
// Name         : main.cpp
// Author       : Theo Welckle
// Version      : 1.0
// Date Created : March 2
// Date Modified: Feb 7
// Copyright    : All rights are reserved
// Description  : Fitness Center 2
//============================================================================

#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include<sstream>

#include "admin.h"
#include "member.h"
#include "fitness.h"
#include "linkedstack.h"
#include "linkedlist1.h"

using namespace std;




LinkedList1<Member> MemberList;
LinkedList1<Admin> AdminList;
LinkedList1<FitnessClass> FitnessClassList;
int logedInUserID;



void inputData(){

	//==============================READ MEMBERS TEXT FILE ===============================================================

	ifstream fin("Members.txt");

	int ID; string firstname, lastname, username, password, tempID;
	string line;

	while(getline(fin,line)){
		stringstream ss(line);
		getline(ss,tempID,',');
		getline(ss,lastname,',');
		getline(ss,firstname,',');
		getline(ss,username,',');
		getline(ss,password,',');
		ID = stoi(tempID);

		Member temp = Member(ID, firstname, lastname, username, password);
		MemberList.addFront(temp);
	}

	fin.close();

	//==============================READ ADMINS TEXT FILE ===============================================================

	ifstream fin1("Admins.txt");

	while(getline(fin1,line)){
		stringstream ss(line);
		getline(ss,tempID,',');
		getline(ss,lastname,',');
		getline(ss,firstname,',');
		getline(ss,username,',');
		getline(ss,password,',');
		ID = stoi(tempID);

		Admin temp = Admin(ID, firstname, lastname, username, password);
		AdminList.addFront(temp);
	}

	fin1.close();

	//==============================READ FITENESSCLASSES TEXT FILE ===============================================================

	ifstream fin2("FitnessClasses.txt");

	string fitID, cname, cdate, ctime, tempMaxCap, rnumber, arrayOfMembers;
	int maxCap;

	while(getline(fin2,line)){
		stringstream ss(line);
		getline(ss,fitID,',');
		getline(ss,cname,',');
		getline(ss,cdate,',');
		getline(ss,ctime,',');
		getline(ss,tempMaxCap,',');
		getline(ss,rnumber,',');
		getline(ss,arrayOfMembers,']');
		maxCap = stoi(tempMaxCap);

		arrayOfMembers = arrayOfMembers.substr(1,arrayOfMembers.length()-1);
		FitnessClass temp = FitnessClass(fitID, cname, cdate, ctime, maxCap, rnumber);
		string tempNumber;
		int number;
		int i=0;
		while(arrayOfMembers.length()>i){
			if(arrayOfMembers[i]==','){
				number = stoi(tempNumber);
				temp.addToListOfMembers(number);
				tempNumber = "";
			}
			else{
				tempNumber += arrayOfMembers[i];
			}
			i++;
		}
		number = stoi(tempNumber);
		temp.addToListOfMembers(number);
		FitnessClassList.addFront(temp);

	}

}

int login(){

	string userType;
	while(true){
		bool breakLoop = false;
		do{
			cout<<"Please enter the category of your account before logging in: [admin/member] "<<endl;
			cin>>userType;

		}
		while(userType!="Admin"&&userType!="admin"&&userType!="Member"&&userType!="member");
		break;

	}

	while(true){
		string userInputUsername;
		string userInputPassword;
		cout<<"What is your username: ";
		cin>>userInputUsername;
		cout<<"What is your password: ";
		cin>>userInputPassword;

		if(userType == "Admin"|| userType == "admin"){
			if(AdminList.login(userInputUsername,userInputPassword)){
				logedInUserID = AdminList.getId(userInputUsername,userInputPassword);
				return 1;
			}
		}
		else{
			if(MemberList.login(userInputUsername, userInputPassword)){
				logedInUserID = MemberList.getId(userInputUsername,userInputPassword);
				return 2;
			}
		}

		cout<<"Do not recognize this password or username. Please try again"<<endl;

	}

}

void listAdminCommands(){

	cout<<endl<<endl;
	cout<<"1) Register a new Admin"<<endl;
	cout<<"2) Register a new member"<<endl;
	cout<<"3) View list of Members"<<endl;
	cout<<"4) Add a fitness class"<<endl;
	cout<<"5) Delete a fitness class"<<endl;
	cout<<"6) Update the details of a fitness class"<<endl;
	cout<<"7) Update the capactiy of a fitness class"<<endl;
	cout<<"8) Split a fitness class into two classes"<<endl;
	cout<<"9) Display the classes with Vacancies"<<endl;
	cout<<"10) Log out"<<endl;
	cout<<"11) Quit program"<<endl<<endl;
	cout<<"Enter the number of the required action: [1-11]: ";

}

void listMemberCommands(){
	cout<<endl<<endl;
	cout<<"1) Book a class"<<endl;
	cout<<"2) Display the classes with Vacancies"<<endl;
	cout<<"3) View current bookings"<<endl;
	cout<<"4) Cancel booking"<<endl;
	cout<<"5) Log out"<<endl;
	cout<<"6) Quit program"<<endl<<endl;
	cout<<"Enter the number of the required action: [1-6]: ";

}

bool adminControls(){

	string userInput;
	
	do{
		listAdminCommands();
		cin>>userInput;
		if(userInput == "1") AdminList.registerAdmin();
		else if(userInput == "2") AdminList.registerMember(MemberList);
		else if(userInput == "3") AdminList.printAllMembers(MemberList);
		else if(userInput == "4") AdminList.addFitnessClass(FitnessClassList);
		else if(userInput == "5") AdminList.deleteFitnessClass(FitnessClassList);
		else if(userInput == "6") AdminList.updateClassDetails(FitnessClassList);
		else if(userInput == "7") AdminList.changeClassCapacity(FitnessClassList);
		else if(userInput == "8") AdminList.splitClass(FitnessClassList);
		else if(userInput == "9") AdminList.viewClassesWithVacancies(FitnessClassList);
		else if(userInput == "10"){
			cout<<endl<<"Logging out"<<endl<<endl;
			return true;
		}
		else if(userInput == "11");
		else cout<<"Invalid Entry"<<endl;

	}
	
	while(userInput != "11");

	return false;


}

bool memberControls(){
	string userInput;
	do{
		listMemberCommands();
		cin>>userInput;
		if(userInput == "1") MemberList.bookAClass(FitnessClassList, logedInUserID);
		else if(userInput == "2") MemberList.viewClassesWithVacancies(FitnessClassList);
		else if(userInput == "3") MemberList.viewBookingList(FitnessClassList, logedInUserID);
		else if(userInput == "4") MemberList.cancelBooking(FitnessClassList, logedInUserID);
		else if(userInput == "5"){
			cout<<endl<<"Logging out"<<endl<<endl;
			return true;
		}
		else if(userInput == "6");
		else cout<<"Invalid Entry"<<endl;
	}

	while(userInput != "6");

	return false;
}


int main(){
	inputData();
	int userType;
	bool continueUsing = true;
	while(continueUsing){
		userType = login();
		cout<<"You have logged in successfully!"<<endl;
		if(userType == 1){
			cout<<"Welcome Back Admin"<<endl;
			continueUsing = adminControls();
		}
		else{
			cout<<"Welcome Back Member"<<endl;
			continueUsing = memberControls();
		}
	}

	AdminList.quitProgram("Admins.txt");
	MemberList.quitProgram("Members.txt");
	FitnessClassList.quitProgramForFitness("FitnessClasses.txt");

	cout<<endl<<"Thank you for using the Fitness System"<<endl;
	return 0;
};