#include <iostream>
#include <cmath>
#include "include/algorithms.h"
#include "include/experiment.h"

using namespace std;

void test();

int main(){
    srand(time(0));
    //test();
    performExperiment();

    return 0;
}

void test(){

    int arr1[7] = {1, 3, 5, 2, 5, 4, 1};
    int arr2[7] = {8, 4, 6, 3, 2, 1, 4};
    int arr3[7] = {1, 2, 3, 4, 5, 6, 7};
    int arr4[7] = {7 ,6, 5, 4, 3, 2, 1};
    cout << shell_sort_verb(arr1, 7) << endl;
    cout << shell_sort_verb(arr2, 7) << endl;
    cout << shell_sort_verb(arr3, 7) << endl;
    cout << shell_sort_verb(arr4, 7) << endl;
}
