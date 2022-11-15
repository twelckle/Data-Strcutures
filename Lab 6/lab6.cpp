//============================================================================
// Name         : lab6_Queue.cpp
// Author       : Theo Welckle
// Version      : 1.0
// Date Created : March 1, 2022
// Date Modified: March 1, 2022
// Copyright    : All rights are reserved
// Description  : Queue implementation using internal Array
//============================================================================

#include<iostream>
#include<iomanip> //for setw() manipulator
#include<exception>
#include <unistd.h>
#include<sstream>
#include<string>
#include<time.h>
#ifdef _WIN32
	#define clear_screen "cls"
#else
	#define clear_screen "clear"
#endif
#define SIZE 5
#define TOP 0
#define LEFT 1
#define BOTTOM 2
#define RIGHT 3
#define MAX_CARS 200
int current_signal;
int SPEED=1; //1=slowest 
using namespace std;
//===================================================
class QueueEmpty: public exception
{
	public:
		virtual const char* what() const throw()
		{
			return "Queue is Empty"; 
		}
};
//=================================================
class QueueFull: public exception
{
public:
	virtual const char* what() const throw()
	{
		return "Queue is Full";
	}
};
//=================================================

template <typename T>
class Queue
{
	private:
		T *array;
		int N;	//Array Size (Capacity)
		int r;	//index where a new element will be added
	public:
		Queue(int N); // N is the Capacity of Queue
		~Queue();
		void enqueue(T); 
		T dequeue();
		bool isEmpty();
		bool isFull();
		friend void display();
};
//===========================================
class Car
{
	private:
		time_t arrival_time;
	public:
		Car()
		{}
		Car(time_t time_stamp): arrival_time(time_stamp)
		{}
		time_t get_arrival_time()
		{
			return arrival_time;
		}
};
//===========================================
void display();
//===========================================
Queue<Car> left_queue(SIZE);
Queue<Car> right_queue(SIZE);
Queue<Car> top_queue(SIZE);
Queue<Car> bottom_queue(SIZE);
//==========================================
int main()
{

	srand(time(NULL));
	int cars=0;
	time_t signal_timer = time(NULL);
	int waiting_time=0;
	current_signal = rand()%4;
	
	while(cars<MAX_CARS)
	{
		
		//complete the main function
		Car addCar(time(NULL)); //A new car with current time is created;

		int addToQueue = rand()%4; //random addToQueue is generated

		//Car is added to random queue.
		if(addToQueue == TOP){
			top_queue.enqueue(addCar);
		}
		else if(addToQueue == LEFT){
			left_queue.enqueue(addCar);
		}
		else if(addToQueue == BOTTOM){
			bottom_queue.enqueue(addCar);
		}
		else{
			right_queue.enqueue(addCar);
		}
	

		//Depending on the current green light. Cars will dequeue every iteration of the while loop.
		//waiting time is calculated by taking the current time minus the time the car was initialized with.
		//deqeue returns a Car data type, so arrival time can be called.
		if(current_signal == TOP){
			if(!top_queue.isEmpty()){
				waiting_time += time(NULL) - top_queue.dequeue().get_arrival_time();
				cars++;
			}
		}
		else if(current_signal == LEFT){
			if(!left_queue.isEmpty()){
				waiting_time += time(NULL) - left_queue.dequeue().get_arrival_time();
				cars++;
			}
		}
		else if(current_signal == BOTTOM){
			if(!bottom_queue.isEmpty()){
				waiting_time += time(NULL) - bottom_queue.dequeue().get_arrival_time();
				cars++;
			}
		}
		else{
			if(!right_queue.isEmpty()){
				waiting_time += time(NULL) - right_queue.dequeue().get_arrival_time();
				cars++;
			}
		}

		//Every 2 seconds the light will change
		if(time(NULL)-signal_timer == 2){
			signal_timer = time(NULL);
			current_signal++;
			current_signal%=4;
		}

		//.......................
		system(clear_screen);
		display();
		cout<<"Total cars passed through the junction:"<<cars<<endl;
		cout<<"Avg. waiting time for a car: "<<setprecision(3)<<(float(waiting_time)/cars)*SPEED<<" seconds"<<endl;	
		usleep(200000/SPEED); 	
	}
	return EXIT_SUCCESS;
}
//========================================================
void display()
{
	string spaces; 
	for(int j=0; j<=SIZE; j++)
		spaces+="     ";
	cout<<spaces<<"╔════╗"<<endl;
	for(int i=0; i<SIZE; i++)
	{
	  	cout<<spaces<<"║";
	  	if(i>=top_queue.N-top_queue.r)
	  		cout<<setw(4)<<" ▒▒ ";
	  	else
	  		cout<<"    ";
	  	cout<<"║"<<endl;
	  	cout<<spaces<<"╠════╣"<<endl;;
	}

	cout<<spaces<<"║";
	if(current_signal==TOP)
		cout<<"\033[1;32m"<<" ■■ "<<"\033[0m";
	else 
		cout<<"\033[1;31m"<<" ■■ "<<"\033[0m";
	cout<<"║"<<endl;

	cout<<"╔════";
	for(int i=0; i<SIZE; i++)
		cout<<"╦════";
	cout<<"╝    ╚";
	for(int i=0; i<SIZE; i++)
		cout<<"════╦";

	cout<<"════╗"<<endl;


	for(int i=0; i<SIZE; i++)
	{	
		cout<<"║";
		if(i>=left_queue.N-left_queue.r)
		  		cout<<setw(4)<<" ▒▒ ";
		else
			cout<<"    ";
	}
	cout<<"║";

	if(current_signal==LEFT)
		cout<<"\033[1;32m"<<" █ "<<"\033[0m";
	else 
		cout<<"\033[1;31m"<<" █ "<<"\033[0m";
	cout<<"      ";

	if(current_signal==RIGHT)
		cout<<"\033[1;32m"<<"   █ "<<"\033[0m";
	else 
		cout<<"\033[1;31m"<<"   █ "<<"\033[0m";
	//cout<<"      ";

	for(int i=0; i<SIZE; i++)
	{
		cout<<"║";
		if(i<right_queue.r)
		  		cout<<setw(4)<<" ▒▒ ";
		else
			cout<<"    ";
	}
	cout<<"║"<<endl;

	cout<<"╚════";
	for(int i=0; i<SIZE; i++)
		cout<<"╩════";
	cout<<"╗    ╔";
	for(int i=0; i<SIZE; i++)
		cout<<"════╩";
	cout<<"════╝"<<endl;

	 cout<<spaces<<"║";

	 if(current_signal==BOTTOM)
		cout<<"\033[1;32m"<<" ▄▄ "<<"\033[0m";
	else 
		cout<<"\033[1;31m"<<" ▄▄ "<<"\033[0m";
	cout<<"║"<<endl;

	for(int i=0; i<SIZE; i++)
	{

	  	cout<<spaces<<"╠════╣"<<endl;
	  	cout<<spaces;
	  			cout<<"║";
		if(i<bottom_queue.r)
		  		cout<<setw(4)<<" ▒▒ ║"<<endl;
		else
			cout<<"    ║"<<endl;
	}
	cout<<spaces<<"╚════╝"<<endl;
	cout<<endl;
}
//===============================================
//complete the missing functions/methods

template <typename T> Queue<T>::Queue(int N){

	r = 0;
	this->N = N;
	array = new T[N];

}

template <typename T> Queue<T>::~Queue(){
	delete array;
}

template <typename T> void Queue<T>::enqueue(T car){
	//if queue is not full, then add element to the queue. Update r (the next available spot in the queue)
	if(!isFull()){
		array[r] = car;
		r++;
	}
	
}
		

template<typename T> T Queue<T>::dequeue(){
	//Will return the first element in the array queue. 
	T returnCar = array[0];

	//must loop through the rest of the array and update the values so that there are no spaces in the array.
	//This is the inefficient part of the inefficient queue. 
	for(int i=0; i<N-1; i++){
		array[i] = array[i+1];
	}
	r--; //a element was removed so r must be decreased. 
	return returnCar;


		
}

template<typename T> bool Queue<T>::isEmpty(){
	//if r = 0 then the first place to be able to insert an element is at the begining. Since this is an inefficient
	//queue this means that the queue is empty.
	return r==0;
}

template<typename T> bool Queue<T>::isFull(){
	//if r = N this means that there is no index in the array to store another element. 
	return r==N;
};