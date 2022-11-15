#include<iostream>
#include<string>
#include<fstream>
#include<cstdlib>
#include"fitness.h"
#include"member.h"



using namespace std;

////to ensure there are no random 0 values in the middle of the list. 
void cleanUpArray(FitnessClass* arr, int locationOfDeletion){

		//if the value to ther right (in the listof members array) is an id number and the index is not out of bounds 
		//-> switch the values of right and left. recursively call function until 0 is at the back of the array.
		if(!(locationOfDeletion+1>=arr->maxCapacity)&&arr->listOfMembers[locationOfDeletion+1]!=0){
			arr->listOfMembers[locationOfDeletion] = arr->listOfMembers[locationOfDeletion+1];
			arr->listOfMembers[locationOfDeletion+1] = 0;
			cleanUpArray(arr, locationOfDeletion+1);
		}
}

	


Member::Member(string first, string last, string user, string pass, int memID){
	
	firstName = first;
	lastName = last;
	userName = user;
	password = pass;
	memberID = memID;

}

//
void Member::bookAClass(FitnessClass** fitClassArr, int sizeOfArrays, Member* user){
	bool success = false;

	//user input
	string inputClassID;
	cout<<"What is the class ID for the class you want to book: "<<endl;
	cin>>inputClassID;

	for(int i = 0; i<sizeOfArrays; i++){
		//loop array until object is found where the classID matches user given ID and the spotsleft are greater then 0.
		if(fitClassArr[i]!= NULL && fitClassArr[i]->classID == inputClassID && fitClassArr[i]->spotsLeft>0){ 

			//Add userID to the listOfMembers array (attribute of FitnessClass)
			fitClassArr[i]->listOfMembers[(fitClassArr[i]->maxCapacity) - (fitClassArr[i]->spotsLeft)] = user->memberID;
			fitClassArr[i]->spotsLeft--; //subtracts spotsleft by one.
			cout<<"Successfully booked!"<<endl;
			success = true;
			break;
		}

	}
	if(!success) cout<<"Sorry this class is not available"<<endl;


}

void Member::cancelBooking(FitnessClass** fitClassArr, int sizeOfArrays, Member* user){
	bool success = false;

	//user input
	string inputClassID;
	cout<<"What is the class ID for the class you want to cancel your booking: ";
	cin>>inputClassID;

	//lopp array until objet is found where classId matches user given ID
	for(int i=0; i<sizeOfArrays; i++){
		if(fitClassArr[i]!=NULL && fitClassArr[i]->classID == inputClassID){

			//loop the listOfMembers array until userID is found
			for(int k=0; k<fitClassArr[i]->maxCapacity;k++){				
				if(fitClassArr[i]->listOfMembers[k]==user->memberID){
					fitClassArr[i]->listOfMembers[k] = 0; //reassign that index to 0
					cleanUpArray(fitClassArr[i], k); //clean up array so 0 is randomly in the middle of the array.
					fitClassArr[i]->spotsLeft++; //increase the spots open. 
					cout<<"Successfully canceled Booking!"<<endl;
					success = true;
					break;
				}
			}
			break;
		}
	}
	if(!success) cout<<"Sorry this class is not available"<<endl;
}

