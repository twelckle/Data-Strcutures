//============================================================================
// Name         : lab2_2
// Author       : Theo Welckle
// Version      : 1
// Date Created : Feb 1
// Date Modified: Feb 1
// Description  : A C++ Program that add, subtracts and multiplies dynamially
//                created matrices
// Copyright © 2021. All rights reserved.
//============================================================================
#include<iostream>
#include<cstdlib>
#include<ctime>
#include<iomanip>
using namespace std;

//function declaration
int** add(int** matrix1, int** matrix2, int rows, int cols);
int** subtract(int** matrix1, int** matrix2, int rows, int cols);
int** multiply(int** matrix1, int** matrix2, int rows1, int cols1, int rows2, int cols2);
void fill(int** matrix, int rows, int cols);
void display(int** matrix, int rows, int cols);
void cleanup(int** matrix, int rows);
int main()
{
	int **matrix1=NULL;
	int **matrix2=NULL;
	int rows1, cols1, rows2, cols2;
	int **ans1=NULL, **ans2=NULL, **ans3=NULL;

	cout<<"Enter the number of rows for first Matrix :";
	cin>>rows1;
	cout<<"Enter the number of columns for first Matrix :";
	cin>>cols1;
	cout<<"Enter the number of rows for second Matrix :";
	cin>>rows2;
	cout<<"Enter the number of columns for second Matrix :";
	cin>>cols2;

	// Create dynamic 2D arrays
	matrix1 = new int*[rows1];
	for(int i=0; i<rows1; i++)
		matrix1[i] = new int[cols1];
	matrix2 = new int*[rows2];
	for(int i=0; i<rows2; i++)
		matrix2[i] = new int[cols2];

	srand(time(NULL));				//Pass System time to to srand function to create different random numbers everytime the program starts
	fill(matrix1,rows1,cols1);		//fill both matrices with random values (int the range of 0-20)
	fill(matrix2,rows2,cols2);
	cout<<"Matrix1 :"<<endl;
	display(matrix1, rows1, cols1);
	cout<<"Matrix2 :"<<endl;
	display(matrix2, rows2, cols2);
	
	if(rows1 == rows2 and cols1 == cols2)		//Pefrom addition only if both matrices have same dimensions
	{
		ans1 = add(matrix1, matrix2, rows1, cols1);
		cout<<"Matrix1 + Matrix2 :"<<endl;
		display(ans1,rows1, cols1);

		ans2 = subtract(matrix1, matrix2, rows1, cols1);
		cout<<"Matrix1 - Matrix2 :"<<endl;
		display(ans2,rows1, cols1);
	}

	if(cols1 == rows2)							//Perform mutliplicaiton if colums of first matrix are rows to the columns of second matrix
	{
		ans3 = multiply(matrix1,matrix2,rows1, cols1, rows2, cols2);
		cout<<"Matrix1 * Matrix2 :"<<endl;
		display(ans3,rows1,cols2);
	}

	//Perform necessary cleanup (delete dynamically created memory)
	cleanup(matrix1,rows1);
	cleanup(matrix2,rows2);
	cleanup(ans1,rows1);
	cleanup(ans2,rows2);
	cleanup(ans3,rows1);

	return 0;
}
//===============================================================
// add two matrices and return the result back to calling program
int** add(int** matrix1, int** matrix2, int rows, int cols)
{
	//Create memory in the heap for a 2D array
	int** matrixAddition = new int*[rows];
	for(int i=0; i<rows;i++){
		matrixAddition[i] = new int[cols];
	}

	//loop through the two arrays and add the values together and assign them to matrix3.
	for(int r = 0; r<rows; r++){
		for(int c = 0; c<cols; c++){
			matrixAddition[r][c] = matrix1[r][c] + matrix2[r][c];
		}
	}

	return matrixAddition;

}
//===============================================================
// subtract two matrices (matrix1-matrix2) and return result
int** subtract(int** matrix1, int** matrix2, int rows, int cols)
{
	//Create memory in the heap for a 2D array
	int** matrixSubtraction = new int*[rows];
	for(int i=0; i<rows;i++){
		matrixSubtraction[i] = new int[cols];
	}

	/*
	PLEASE READ

	On the document it says matrix2 - matrix1, but then both on the program output of the starter code
	and the comments on the starter code say matrix1 - matrix2. So I didn't know which one to trust. So
	I went with matrix1 - matrix2. 

	if it was matrix2 - matrix1 it would be:
	matrixSubtraction[r][c] = matrix2[r][c] - matrix1[r][c];

	*/
	//loop through the two arrays and add the values together and assign them to matrix3.
	for(int r = 0; r<rows; r++){
		for(int c = 0; c<cols; c++){
			matrixSubtraction[r][c] = matrix1[r][c] - matrix2[r][c];
		}
	}
	return matrixSubtraction;

}
//==============================================================
// multiply two matrices and return the result
int** multiply(int** matrix1, int** matrix2, int rows1, int cols1, int rows2,int cols2)
{
	
	//Create memory in the heap for a 2D array
	// matrix 1 * matrix 2 = r1 by c1 * r2 by c2 = r1 by c2. 
	int** matrixMultiplication = new int*[rows1];
	for(int i=0; i<rows1;i++){
		matrixMultiplication[i] = new int[cols2];
	}

	for(int r1 = 0; r1<rows1; r1++){
		for(int c2 = 0; c2<cols2; c2++){
			for(int k = 0; k<rows2; k++){ //a integer k is needed to iterate over the shared value that is not used.

			matrixMultiplication[r1][c2] += matrix1[r1][k] * matrix2[k][c2];

			}
		}
	}

	return matrixMultiplication;

}
//===============================================================
// fill the matrix with random values in the range of 0 to 20
void fill(int** matrix, int rows, int cols)
{
	//todo
	for(int r=0; r<rows; r++){
		for(int c = 0; c<cols; c++){
		matrix[r][c] = rand() % 20; //will give a random value as modulus gives the remainder. 
		}
	}
}
//===============================================================
// display the matrix in two dimension form
void display(int** matrix, int rows, int cols)
{


	for(int r=0; r<rows; r++){
		for(int c = 0; c<cols; c++){

			int temp = matrix[r][c];
			int counter = 0;

			//in order to get the length of the number(in char) to adjust spaces accordingly.
			while(temp > 9 || temp < -9){ 
				temp = temp / 10;
				counter++;
			}
			if(matrix[r][c] < 0) counter+=1; //negative number means extra char.

			//spaces depended on number length(in char)
			for(int spaces = 0; spaces<6-counter; spaces++){
				cout<<" ";
			}
			cout<<matrix[r][c];

		}
		cout<<endl;
	}

	cout<<endl<<endl;

}
//==============================================================
// delete the memory dynaicall reserved for matrix 
void cleanup(int** matrix, int rows)
{

	for(int i = 0; i<rows; i++){
		int* m = matrix[i];
		delete m;
	}
	delete[] matrix;


}
