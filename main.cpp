//
//  main.cpp
//  QuickSortPractice
//
//  Created by Kevin Nguyen on 9/20/18.
//  Copyright © 2018 Kevin Nguyen. All rights reserved.
//
// 7 4 6 8 9 2 5 pivot = 7
// is 7 < 5 ? yes
//switch
//5 4 6 8 9 2 7,
//locate position i and j
// swap 8 and 2
//5 4 6 2 9 8 7
//5 4 6 2 | 7 8 9
//
//  main.cpp
//  bubbleSort
//
//  Created by Kevin Nguyen on 9/6/18.
//  Copyright © 2018 Kevin Nguyen. All rights reserved.
//

/*
 
1 - reptition
2 - condition to stop
3 - How we call by changing argument
 
*/

#include <iostream>
#include <cstdlib>
#include <iomanip>

using namespace std;

int *generateRandomNumberArray(int arraySize);
void outputTable(double, double, double, double);
void mergeSort(int array[], int left, int right);
void print (int [], int);
void swap (int *a, int *b);
int partition (int array[], int low, int high);
void quickSort(int array[], int low, int high);
void runQuickSort(double &time, int array[], int numOfElements);
int *copyArray (int array[], int size);
void runMergeSort(double &time, int *array, int numOfElements);
void runSelectionTest(double &, int*, int);

int main() {
    int testTenK = 10000;
    int testFiftyK= 50000;
    int *randomTenThousand= generateRandomNumberArray(testTenK);
    int *copyTenThousand = copyArray(randomTenThousand, testTenK);
    int *randomFiftyK = generateRandomNumberArray(testFiftyK);
    int *copyFiftyK = copyArray(randomFiftyK, testFiftyK);
    double timeOne{}, timeTwo{}, timeThree{}, timeFour{};
    runMergeSort(timeOne, randomTenThousand, testTenK);
    runMergeSort(timeTwo, randomFiftyK, testFiftyK);
    runQuickSort(timeThree, copyTenThousand, testTenK);
    runQuickSort(timeFour, copyFiftyK, testFiftyK);
    outputTable(timeOne,timeTwo, timeThree, timeFour);
    return 0;
}

int *copyArray(int array[], int size) {
    int *arrayCopy = new int[size];
    for (int i = 0; i < size; i++) {
        arrayCopy[i] = array[i];
    }
    return arrayCopy;
}

void runMergeSort(double &time, int array[], int numOfElements) {
    clock_t start = clock();
    mergeSort(array, 0, numOfElements - 1);
    clock_t end = clock();
    time = (end - start) / (double) CLOCKS_PER_SEC;
}

void runQuickSort(double &time, int array[], int numOfElements) {
    clock_t start = clock();
    quickSort(array, 0, numOfElements -1);
    clock_t end = clock();
    time = (end - start) / (double) CLOCKS_PER_SEC;
}

int *generateRandomNumberArray(int arraySize) {
    int *numbersArray = new int[arraySize];
    for (int i = 0; i < arraySize; i++) {
        numbersArray[i] = rand();
    }
    return numbersArray;
}

void swap(int *numOne, int *numTwo) {
    int temp = *numOne;
    *numOne = *numTwo;
    *numTwo = temp;
}

int partition (int array[], int low, int high) {
    int pivot = array[high]; // pivot
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }
    swap(&array[i + 1], &array[high]);
    return (i + 1);
}

void quickSort(int array[], int low, int high) {
    if (low < high) {
        int partitionIndex = partition(array, low, high);
        quickSort(array, low, partitionIndex - 1);
        quickSort(array, partitionIndex + 1, high);
    }
}

void merge(int array[], int leftStart, int middle, int rightEnd) {
    int leftIndex;
    int rightIndex;
    int mergedIndex;
    //getting the left and right sizes for the left and right arrays
    int leftSize = middle - leftStart + 1;
    int rightSize = rightEnd - middle;
    
    //creating temp arrays
    int leftArray[leftSize], rightArray[rightSize];
    //copy data to temp arrays Left and Right
    for(leftIndex = 0; leftIndex < leftSize; leftIndex++) {
        leftArray[leftIndex] = array[leftStart + leftIndex];
    }
    
    for (rightIndex = 0; rightIndex < rightSize; rightIndex++ ) {
        rightArray[rightIndex] = array[middle + 1  + rightIndex];
    }
    
    //merged the temp arrays back into array [left .... right]
    leftIndex = 0;
    rightIndex = 0;
    mergedIndex = leftStart;
    
    while(leftIndex < leftSize && rightIndex < rightSize) {
        if (leftArray[leftIndex] <= rightArray[rightIndex]) {
            array[mergedIndex] = leftArray[leftIndex];
            leftIndex++;
        } else {
            array[mergedIndex] = rightArray[rightIndex];
            rightIndex++;
        }
        mergedIndex++;
    }
    //filling what is left of the leftArray and rightArray
    while(leftIndex < leftSize) {
        array[mergedIndex] = leftArray[leftIndex];
        leftIndex++;
        mergedIndex++;
    }
    
    while(rightIndex < rightSize) {
        array[mergedIndex] = rightArray[rightIndex];
        rightIndex++;
        mergedIndex++;
    }
    
}

void mergeSort(int array[], int left, int right) {
    //conditon to break the recursion
    if (left < right) {
        //same thing as (l + r) / 2
        int middle = left + (right - left) / 2;
        //splits up the left side of the array
        mergeSort(array, left, middle);
        //splits up the right side of the array
        mergeSort(array, middle + 1, right);
        //merges the left and right sides
        merge(array, left, middle, right);
    }
}

void outputTable(double time1, double time2, double time3, double time4) {
    cout << setw(15) << "Total input(#'s)" << setw(20) << "Merge(s)" << setw(20) << "Quick(s)"  << endl  << endl;
    cout << setw(15) << 10000 << setw(20) << time1 << setw(20) << time3 << endl << endl;
    cout << setw(15) << 50000 << setw(20) << time2 << setw(20) << time4 << endl << endl;
   
}

void print(int array[], int size) {
    for (int i  = 0; i < size; i++) {
        cout << array[i] << endl;
    }
}

