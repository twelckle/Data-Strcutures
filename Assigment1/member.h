#ifndef MEMBER
#define MEMBER

#include<string>
#include "fitness.h"

using namespace std;

//Member with attributes and functions (declaration).

class Member{
	public:
		int memberID;
		string firstName;
		string lastName;
		string userName;
		string password;
		Member(string first, string last, string user, string pass, int memID);
		void bookAClass(FitnessClass** fitClassArr, int sizeOfArrays, Member* user);
		void cancelBooking(FitnessClass** fitClassArr, int sizeOfArrays, Member* user);
};


#endif