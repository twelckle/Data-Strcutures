#ifndef ADMIN
#define ADMIN

#include<string>
#include "member.h"
#include "fitness.h"

using namespace std;

//Admin Class with attributes and functions (declaration).

class Admin{
	public:
		int adminID;
		string firstName;
		string lastName;
		string userName;
		string password;

		Admin(string first, string last, string user, string pass, int admID);


		void registerAdmin(Admin **list, int sizeOfArrays);
		void registerMember(Member **list, int sizeOfArrays);
		void addFitnessClass(FitnessClass **arr, int sizeOfArrays);
		void deleteFitnessClass(FitnessClass **arr, int sizeOfArrays);
		void updateClassDetails(FitnessClass** arr, int sizeOfArrays);


};

#endif