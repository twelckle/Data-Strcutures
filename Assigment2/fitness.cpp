#include<string>
#include"fitness.h"
#include "linkedstack.h"

using namespace std;

FitnessClass::FitnessClass(string id, string cname, string cdate, string ctime, int maxCap, string rnumber){

	ID = id;
	className = cname;
	classDate = cdate;
	classTime = ctime;
	maxCapacity = maxCap;
	roomNumber = rnumber;
	listOfMembers = new LinkedStack<int>();

}

FitnessClass::FitnessClass(){
	ID = "testing";
	className = "testing";
	classDate = "testing";
	classTime = "testing";
	maxCapacity = 123;
	roomNumber = "testing";
	listOfMembers = new LinkedStack<int>(); 
}

void FitnessClass::addToListOfMembers(int e){
	listOfMembers->push(e);
}

string FitnessClass::getclassName(){return className;}
string FitnessClass::getclassDate(){return classDate;}
string FitnessClass::getclassTime(){return classTime;}
int FitnessClass::getmaxCapacity(){return maxCapacity;}
string FitnessClass::getroomNumber(){return roomNumber;}
string FitnessClass::getID(){return ID;}
LinkedStack<int>* FitnessClass::getlistOfMembers(){return listOfMembers;}

void FitnessClass::setclassName(string i){className = i;}
void FitnessClass::setclassDate(string i){classDate = i;}
void FitnessClass::setclassTime(string i){classTime = i;}
void FitnessClass::setmaxCapacity(int i){maxCapacity = i;}
void FitnessClass::setroomNumber(string i){roomNumber = i;}
void FitnessClass::setID(string i){ID = i;}