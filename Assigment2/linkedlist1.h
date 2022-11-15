#ifndef LINKEDLIST1
#define LINKEDLIST1

#include<string>
#include"linkedstack.h"
#include"admin.h"
#include"fitness.h"
#include"member.h"



using namespace std;
template <class T> class LinkedList1;
template <class T> class Node;


template <class T>
class Node{
	private:
		T elem;
		Node* next;

	public:
		Node();
		Node<T>* getNext();
		T getElem();

	friend class LinkedList1<T>;
};

template <class T>
class LinkedList1{
	private:
		Node<T>* head;
	public:
		LinkedList1();
		~LinkedList1();
		bool empty() const;
		Node<T>* front() const;
		void addFront(const T&);
		void removeFront();
		void removeNode(Node<T>* e);
		Node<T>* getHead();
		bool login(string inputUsername, string inputPassword);
		int getId(string inputUsername, string inputPassword);
		void registerMember(LinkedList1<Member>& memberList);
		void registerAdmin();
		void printAllMembers(LinkedList1<Member>& members);
		void addFitnessClass(LinkedList1<FitnessClass>& FitnessClassList);
		void deleteFitnessClass(LinkedList1<FitnessClass>& FitnessClassList);
		void updateClassDetails(LinkedList1<FitnessClass>& FitnessClassList);
		void changeClassCapacity(LinkedList1<FitnessClass>& FitnessClassList);
		void splitClass(LinkedList1<FitnessClass>& FitnessClassList);
		void viewClassesWithVacancies(LinkedList1<FitnessClass>& FitnessClassList);
		void bookAClass(LinkedList1<FitnessClass>& FitnessClassList, int logedInUserID);
		void viewBookingList(LinkedList1<FitnessClass>& FitnessClassList, int logedInUserID);
		void cancelBooking(LinkedList1<FitnessClass>& FitnessClassList, int logedInUserID);
		void quitProgram(string fileName);
		void quitProgramForFitness(string fileName);

};


#endif