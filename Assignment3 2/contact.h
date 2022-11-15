#ifndef CONTACT_H
#define CONTACT_H

#include<iostream>
#include<fstream>
using namespace std;

class Contact
{
	private:
		string fname;
		string lname;
		string email;
		string primaryPhone;
		string city;
		string country;
		bool isFav;

	public:
		Contact(string fname, string lname, string email, string primaryPhone, string city, string country, bool isFav);
		//a bunch of setter functions
		void setFirstName();
		void setLastName();
		void setEmail();
		void setPhone();
		void setCity();
		void setCountry();
		void setFav(bool boolfav);

		//two getter functions
		string getKey();
		bool getFav();

		//2 prints for different uses
		void print();
		void printForExport(ofstream& output);

		
};

#endif