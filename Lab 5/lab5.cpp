//============================================================================
// Name         : lab5.cpp
// Author       : Theo Welcke
// Version      : 1.0
// Date Created : Feb 23
// Date Modified: Feb 25
// Copyright    : All rights are reserved
// Description  : Convert Infix expression to PostFix and then evaluate it
//============================================================================
#include<iostream>
#include<string>
#include<exception>
#include<math.h>
#include<ctype.h>

using namespace std;

bool isOperator(char); //Function which checks if the input char is an operator
int convertOpToInt (char); //Function which converts operators into int so their precdence can be compared
bool isleq(char, char); //Function which compare two operators  and return True if first operator has less or equal predence than the right operator
string infix2postfix(string);   //Function which converts an infix notaiton into a postfix notation (lab4)
float evaluate(string postfix);	 //Function which will evaluate a PostfixExpression and return the result
bool isBalanced(string expression); // Funciton which will check for balanced parentheses 


//==============StackEmpty exception Class===============
class StackEmpty:public exception{
	public:
		virtual const char* what() const throw(){
			return("Stack is Empty");
		}

};

class StackFull:public exception{
	public:
		virtual const char* what() const throw(){
			return("Stack is Full");
		}

};
//==============CStack Class===============
//declare the Cstack class here
template <typename T>
class Cstack
{
	public:
		Cstack(int cap = 100);
		~Cstack();
		void push(T e) throw(StackFull);
		void pop() throw(StackEmpty);
		const T& top() const throw(StackEmpty);
		int size() const;
		bool empty() const;

	private:
		T* S;
		int capacity;
		int t; 

};

template <typename T> Cstack<T>::Cstack(int cap){
	S = new T[cap];
	capacity = cap;
	t = -1;
}

//deletes the dynamically created array. 
template <typename T> Cstack<T>::~Cstack(){
	delete S;
}

//returns the size of the stack.
template <typename T> int Cstack<T>::size() const{
	return t+1;
}

//checks to see if the stack is empty
template <typename T> bool Cstack<T>::empty() const{
	return (t < 0);
}

//Return the top element.
template <typename T> const T& Cstack<T>::top() const throw(StackEmpty){
	if(empty()) throw StackEmpty();
	return S[t];
}

//removes the top element.
template<typename T> void Cstack<T>::pop() throw(StackEmpty){
	if(empty()) throw StackEmpty();
	t--;
}

//inserts an element on top of the stack.
template<typename T> void Cstack<T>::push(T e) throw(StackFull){
	if(size() == capacity) throw StackFull();
	S[++t] = e;
}

//=============Main funciton ==============
int main()
{

	while(true)
	{
		string infix;  						//Infix expression
		cout<<"Enter an Infix Expression: ";
		cin>>infix;
		try
		{
			if(infix=="exit") 
				break;
			
			else if(!isBalanced(infix)) 
			{
				cout<<"Expression is not Balanced "<<endl;
				continue;
			}

			string postfix = infix2postfix(infix);	//Postfix Expression
			cout<<"The postfix form is: "<<postfix<<endl;
			float ans=evaluate(postfix);			//evaluate the postfix Expresion
			cout<<infix<<"="<<ans<<endl;		//print the final answer
		}
		catch(exception &e)
		{
			cout<<"Exception: "<<e.what()<<endl;
		}
	}

	return EXIT_SUCCESS;
}
//=====================================================================
bool isOperator(char ch)
{
	if( ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='^')
		return true;
	else
		return false;

}
//Function which converts operators into int so their precdence can be compared
int convertOpToInt (char ch)
{
    if (ch=='+' || ch=='-') return 1;
    if (ch=='*' || ch=='/') return 2;
    if (ch=='^') return 3;
    return 0;
}
//Helper Function which compare two operators and return True if first operator
//has less or equal predence than the right operator
bool isleq(char opA, char opB)
{
	return (convertOpToInt(opA)<=convertOpToInt(opB));
}

//Funciton which will check for balanced parentheses 
bool isBalanced(string expression)
{
	Cstack<char> myStack;

	//For every char in the expression
	for(int i=0;i<expression.length();i++){
		if(expression[i]=='(') myStack.push(expression[i]); //if the char is and ( push to stack
		else if(expression[i] == ')'){ //if the char is ) then try to pop(ie see if there is the corresponding ( char.
			try{
				 myStack.pop();
			}
			catch(exception &exc) //if the stack is empty that means there is an ) without its pair so return false.
			{
				return false;
			}

		}
	}
	return(myStack.empty()); //if the stack is empty then its balanced. If it still has a ( element then it is not balnced.
}

// Function which converts an Infix Notaiton to a Postfix notation
string infix2postfix(string infix)
{

	//0.Create a stack of type char to store operators/parenthesis and string postfix
	Cstack<char> myStack;
	string postfix;
	//1.Push “(“onto Stack, and add “)” to the end of INFIX.
	myStack.push('(');
	infix += ')';

	//2.Scan INFIX from left to right
	for(int i = 0; i<infix.length(); i++){
		//check if element is an operator 
		if(isOperator(infix[i])){
			//check if the top of the stack is an operator and if that element has a higher precedence. If so continue to pop and add to postfix.
			while(isOperator(myStack.top()) && isleq(infix[i],myStack.top())){
				postfix+=myStack.top();
				myStack.pop();
			}
			myStack.push(infix[i]);
		}
		//If a left parenthesis is found, push it onto Stack.
		else if(infix[i] == '(') myStack.push('(');
		
		//.6.	If a ")" is found, then: 
			//a.Repeatedly pop from Stack and add to POSTFIX each operator 
			//(on the top of Stack) until a "(" found.
			//b.	Remove(pop) the "(" from the stack
		else if(infix[i] == ')'){
			while(myStack.top() != '('){
				postfix += myStack.top();
				myStack.pop();
			}
			myStack.pop();
		}
		
		else postfix += infix[i];
					
	}

	return postfix;
}

// //Function which will evaluate a PostfixExpression and return the result
float evaluate(string postfix)		
{	

	//1. Create a stack of type float to store the operands
	Cstack<float> evaluateStack;

	//Scan the postfix expression from left to right for every element
	for(int i = 0; i<postfix.length(); i++)
	{
		//if an operator is found pop 2 elements from the stack,
	    //apply the operator on it and push the result back to the stack
		if(isOperator(postfix[i])){
			int first;
			int second;
			float pushNumber;


			second = evaluateStack.top()-'0'; //change char into int
			evaluateStack.pop();
			first = evaluateStack.top()-'0'; //change char into int
			evaluateStack.pop();


			if(postfix[i] == '+'){
				pushNumber = first+second;
			}
			else if(postfix[i] == '-'){
				pushNumber = first-second;
			}
			else if(postfix[i] == '*'){
				pushNumber = first*second;
			}
			else{
				pushNumber = first/second;

			}
			evaluateStack.push(pushNumber+'0'); //change int back into char. 
		}
		else{
			evaluateStack.push(postfix[i]);
		}


	}
	//return the value from the top of the stack (i.e. the final answer)
	return evaluateStack.top()-'0';//change the char back into int.
}