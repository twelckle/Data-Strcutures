#include<string>
#include "member.h"

using namespace std;


Member::Member(int memID, string first, string last, string user, string pass){
	ID = memID;
	firstName = first;
	lastName = last;
	userName = user;
	password = pass;
}

Member::Member(){
	ID = 123;
	firstName = "empty";
	lastName = "empty";
	userName = "empty";
	password = "empty";
}

int Member::getID() {return ID;}
string Member::getfirstName() {return firstName;}
string Member::getlastName() {return lastName;}
string Member::getuserName() {return userName;}
string Member::getpassword() {return password;}
