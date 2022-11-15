#ifndef FITNESS
#define FITNESS

#include<string>

using namespace std;

//Fitness Class with attributes and functions (declaration).

class FitnessClass{
	public:
		string className;
		string classDate;
		string classTime;
		int maxCapacity;
		string roomNumber;
		string classID;
		int* listOfMembers;
		int spotsLeft;

		FitnessClass(string cname, string cdate, string ctime, int maxCap, string rnumber, string id);
		~FitnessClass();


};



#endif