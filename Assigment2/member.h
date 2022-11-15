#ifndef MEMBER
#define MEMBER

#include<string>

using namespace std;

//Member with attributes and functions (declaration).

class Member{
	private:
		int ID;
		string firstName;
		string lastName;
		string userName;
		string password;
	public:
		Member(int memID, string first, string last, string user, string pass);
		Member();
		int getID();
		string getfirstName();
		string getlastName();
		string getuserName();
		string getpassword();

};


#endif