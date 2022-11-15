#include<string>
#include"admin.h"

using namespace std;

Admin::Admin(int admID, string first, string last, string user, string pass){
	ID = admID;
	firstName = first;
	lastName = last;
	userName = user;
	password = pass;
}

Admin::Admin(){
	ID = 123;
	firstName = "empty";
	lastName = "empty";
	userName = "empty";
	password = "empty";
}

int Admin::getID() {return ID;}
string Admin::getfirstName() {return firstName;}
string Admin::getlastName() {return lastName;}
string Admin::getuserName() {return userName;}
string Admin::getpassword() {return password;}