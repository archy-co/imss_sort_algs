#include <iostream>
#include "include/algorithms.h"
#include <chrono>
#include <cmath>

#define RAND_EXPERIMENT_REPS 5
#define FUNCS_COUNT 4

using namespace std;

void printArray(int*, int);
void randArrFill(int*, int, int);
void printRes(long *res);

void experiment();

long* randomArr(int size);
void ascendingArr();
void descendingArr();
void repetitiveArr();

void basicExample();

string FUNCS[] = {"Selection Sort", "Insertion Sort",
                  "Shell Sort    ", "Merge Sort    "};
void (*sort_algs[])(int*, int) = { selection_sort, insertion_sort, shell_sort };

int main(){
    srand(time(0));
    //basicExample();
    experiment();

    return 0;
}


void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

void randArrFill(int *arr, int size, int max){
    for(int i = 0; i < size; i++){
        arr[i] = rand()%max;
    }
}

void experiment(){
    for(int i = 7; i <= 15; i++){
        long *randomArrRes = randomArr(pow(2, i));
        printRes(randomArrRes);
        cout << endl;
        ascendingArr();
        descendingArr();
        repetitiveArr();
        free(randomArrRes);
    }
}

long* randomArr(int size){
    int arr[size];
    long *results = (long*) malloc(sizeof(long) * 4);
    *results = 0, *(results+1) = 0, *(results+2) = 0, *(results+3) = 0;

    for(int i = 0; i < RAND_EXPERIMENT_REPS; i++){
        randArrFill(arr, size, size+1);

        for(int j = 0; j < FUNCS_COUNT-1; j++){
            auto start = chrono::high_resolution_clock::now(); 
            (sort_algs[j])(arr, size);
            auto stop = chrono::high_resolution_clock::now();

            long duration = (chrono::duration_cast<chrono::microseconds>(stop - start)).count();
            results[j] += duration;
        }

        auto start = chrono::high_resolution_clock::now(); 
        merge_sort(arr, 0, size-1);
        auto stop = chrono::high_resolution_clock::now();

        long duration = (chrono::duration_cast<chrono::microseconds>(stop - start)).count();
        results[3] += duration;
    }
    for(int i = 0; i < FUNCS_COUNT; i++)
        results[i] /= RAND_EXPERIMENT_REPS;

    return results;
}
void ascendingArr(){

}
void descendingArr(){

}
void repetitiveArr(){

}

void printRes(long *res){
    for(int i = 0; i < FUNCS_COUNT; i++)
        cout << FUNCS[i] << ": " << res[i] << endl;;
}
