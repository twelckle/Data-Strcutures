#include<string>
#include"fitness.h"
using namespace std;

//constructor
FitnessClass::FitnessClass(string cname, string cdate, string ctime, int maxCap, string rnumber, string cid){
	className = cname;
	classDate = cdate;
	classTime = ctime;
	maxCapacity = maxCap;
	roomNumber = rnumber;
	classID = cid;
	spotsLeft = maxCap;
	listOfMembers = new int[maxCap];
}

//deconstructor for the list of membors in a class atribute (dynamically created) 
FitnessClass::~FitnessClass(){
	delete[] listOfMembers;
}
