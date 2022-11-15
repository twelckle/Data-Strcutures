#ifndef FITNESS
#define FITNESS

#include<string>
#include"linkedstack.h"


using namespace std;

//Fitness Class with attributes and functions (declaration).

class FitnessClass{

	private:
		string className;
		string classDate;
		string classTime;
		int maxCapacity;
		string roomNumber;
		string ID;
		LinkedStack<int>* listOfMembers;


	public:
		FitnessClass(string id, string cname, string cdate, string ctime, int maxCap, string rnumber, LinkedStack<int>* members);
		FitnessClass(string id, string cname, string cdate, string ctime, int maxCap, string rnumber);
		FitnessClass();
		void addToListOfMembers(int e);

		string getclassName();
		string getclassDate();
		string getclassTime();
		int getmaxCapacity();
		string getroomNumber();
		string getID();
		LinkedStack<int>* getlistOfMembers();

		void setclassName(string i);
		void setclassDate(string i);
		void setclassTime(string i);
		void setmaxCapacity(int i);
		void setroomNumber(string i);
		void setID(string i);

};
#endif