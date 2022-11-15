//============================================================================
// Name         : lab14.cpp
// Author       : Theo Welckle
// Version      : 1.0
// Date Created : 05-06-2022
// Date Modified: 05-06-2022 
// Copyright    : All rights are reserved
// Description  : Sorting Algorithms (Selection Sort, Bubble Sort, Insertion Sort, Merge Sort, Quick Sort, Heap Sort)
//============================================================================

#include<iostream>
#include<vector>
#include<iomanip>
#include<algorithm>
using namespace std;
#define SIZE 1000
#define MAX 1000
template <typename T> void selection_sort(T array[], int n);
template <typename T> void bubble_sort(T array[], int n);
template <typename T> void insertion_sort(T array[], int n);
template <typename T> void merge_sort(T array[], int left, int right);
template <typename T> void merge(T array[], int left, int right, int mid);
template <typename T> void quick_sort(T array[], int left, int right);
template <typename T> int partition(T array[], int left, int right);
template <typename T> void print(T array[], int size);
int main()
{
    int array[SIZE];
    srand(time(NULL));
    for(int i=0; i<SIZE;i++) array[i] = rand()%MAX;
    cout<<endl;
    
    int start = clock();
    selection_sort(array,SIZE);
    int stop = clock ();
    print(array,SIZE);
    cout<<"Selection Sort took: "<<float(stop - start )/  CLOCKS_PER_SEC*1000<<" milliseconds"<<endl;
    random_shuffle(array,array+SIZE);

    cout<<endl;
    start = clock();
    bubble_sort(array,SIZE);
    stop = clock ();
    print(array,SIZE);
    cout<<"Bubble Sort took: "<<float(stop - start )/  CLOCKS_PER_SEC*1000<<" milliseconds"<<endl;
    random_shuffle(array,array+SIZE);

    cout<<endl;
    start = clock();
    insertion_sort(array,SIZE);
    stop = clock ();
    print(array,SIZE);
    cout<<"Insertion Sort took: "<<float(stop - start )/  CLOCKS_PER_SEC*1000<<" milliseconds"<<endl;
    random_shuffle(array,array+SIZE);

    cout<<endl;
    start = clock();
    merge_sort(array,0,SIZE-1);
    stop = clock ();
    print(array,SIZE);
    cout<<"Merge Sort took: "<<float(stop - start )/  CLOCKS_PER_SEC*1000<<" milliseconds"<<endl;
    random_shuffle(array,array+SIZE);

    cout<<endl;
    start = clock();
    quick_sort(array,0,SIZE-1);
    stop = clock ();
    print(array,SIZE);
    cout<<"Quick Sort took: "<<float(stop - start )/  CLOCKS_PER_SEC*1000<<" milliseconds"<<endl;

    return EXIT_SUCCESS;
}
//========================================================
template <typename T> void print(T array[], int size)
{
    for(int i=0; i<size; i++)
        cout<<array[i]<<" ";
    cout<<endl;
}

template <typename T> void selection_sort(T array[], int n){
    //a nested for loops that goes through the entire array until the minimum is found. Then swaps minimum to the begning of the array.
    //repeats however ignores the first index which is already sorted. 
    for(int i = 0; i<n;i++){
        int index = i;
        for(int k=i+1;k<n;k++){
            if(array[k]<array[index]){
                index = k;
            }
        }
        T temp = array[i];
        array[i] = array[index];
        array[index] = temp;
    }
}

template <typename T> void bubble_sort(T array[], int n){
    //compares first elements and switches if the first is bigger then the second. This continues until the largest element
    //is at the back of the array.
    for(int i = 0; i<n; i++){
        for(int k = i+1; k<n; k++){
            if(array[i]>array[k]){
                T temp = array[k];
                array[k] = array[i];
                array[i] = temp;
            }
        }
    }
}

template <typename T> void insertion_sort(T array[], int n){
    
    //goes through each index and inserts the element into the correct location in the array. 1st element sorted. 2nd element is comared
    //with the first. Third element is placed in the correct spot either before both, between, or at the end. And so forth.
    for(int i = 1; i<n; i++){
        T checkValue = array[i];
        int index = i;
        while(index>0 and array[index-1]>checkValue){
            array[index] = array[index-1];
            index--;
        }
        array[index] = checkValue;
    }


}

/*

I'm going to be very transparant and say that a lot of this code is from help from the internet. I understand that the goal of these
labs is to write your own code, however with the merge and quick sort algorithms I could understand how they work conceptually
but putting them in code was very difficult for me. I spent almost 2 hours on each algorithm trying to understand each line of the code that I have
written here. Although some of this code is not soley my thinking, I have gone over each line to ensure I understand what each line is doing.
At some point trying to come up with your own solution seems pointless as I was not getting anywhere.
Eventually you must seek other resources. I hope this makes sense.

*/

template <typename T> void merge_sort(T array[], int left, int right){

    if(left >= right) return;

    //this middle index is taken by adding the left number to the middle between left and right. This at first did not make
    //sense to me. however when you recursively call the function left becomes in the middle of the array. Therefore the middle can not
    //be calculated strictly using (right - left)/2

    int middle = left + (right-left)/2;

    //recursively call merge sort until the index between left and right is 1.
    merge_sort(array, left, middle);
    merge_sort(array,middle+1,right);

    //then merge up.
    merge(array,left,right,middle);
}


template <typename T> void merge(T array[], int left, int right, int mid){

    //Make new arrays with sizes equal to the index of right and left. Fill the new arrays with the values in the original array.
    int* arrayLeft = new int[mid-left+1];
    int* arrayRight = new int[right-mid];

    for(int i = 0; i<mid-left+1; i++){
        arrayLeft[i] = array[left+i];
    }

    for(int i = 0; i<right-mid; i++){
        arrayRight[i] = array[mid+1+i];
    }

    int i = left;
    int first = 0;
    int second = 0;

    //Until one of the arrays reaches its end, check to see which position is smaller. The smaller position will be added to the 
    //index of the original array. Then the apprpriate indexes will be updated.
    while(first<mid-left+1 and second<right-mid){
        if(arrayLeft[first] <= arrayRight[second]){
            array[i] = arrayLeft[first];
            first++;
        }
        else{
            array[i] = arrayRight[second];
            second++;
        }
        i++;
    }

    //one subarray will reach the end before the other. These two while statements do the same thing however one does it for subarray 1
    //and the other for subarray2. Only one of these while statments will run. The while statement adds the remaining indexs that did not 
    //get added to the original array in the first while loop to the orignal array. 
    while(first<mid-left+1){
        array[i] = arrayLeft[first];
        i++;
        first++;
    }
    while(second<right-mid){
        array[i] = arrayRight[second];
        i++;
        second++;
    }

}


template <typename T> void quick_sort(T array[], int left, int right){
    if(left<right){
        //we need to place the pivot in the middle of the array. and have all values less then the pivot on the left, and all
        //values greater then the pivot on the right. The partition function does this.
        int partitionindex = partition(array, left, right);

        //Now we call quick sort for each side of the array. However we exclude the pivot as that is in the right location.
        quick_sort(array,left,(partitionindex-1));
        quick_sort(array, (partitionindex+1), right);
    }
}

template <typename T> int partition(T array[], int left, int right){
    //we choose the pivot to be the last value in the array window.
    //index is the first index of the window.
    int pivot = array[right];
    int index = left;

    //we traverse the array and for each value that is smaller then the pivot we put it to the right of the index that the pivot will
    //be inserted in at. Otherwise keep the index where it is. 
    for(int i = left; i < right; i++){
        if(array[i]<pivot){
            int temp = array[index];
            array[index] = array[i];
            array[i] = temp;
            index++;
        }

    }

    //put the pivot in the right location by switching it with a value that is bigger then the pivot value.
    int temp = array[index];
    array[index] = array[right];
    array[right] = temp;

    //return the index in which the pivot is located in the array. 
    return index;
}