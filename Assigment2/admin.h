#ifndef ADMIN
#define ADMIN

#include<string>

using namespace std;

//Admin Class with attributes and functions (declaration).

class Admin{
	private:
		
		int ID;
		string firstName;
		string lastName;
		string userName;
		string password;

	public:
		Admin(int admID, string first, string last, string user, string pass);
		Admin();
		int getID();
		string getfirstName();
		string getlastName();
		string getuserName();
		string getpassword();
};

#endif