#include <iostream>
#include <fstream>
#include <cmath>
#include <chrono>
#include "../include/experiment.h"

using namespace std;

void (*fill_types[])(int*, int) = { randArr, ascArr, descArr, randLowArr };
const int FILL_TYPE_EXPERIMENT_REPS[EXPERIMENTS_COUNT] = { 5, 1, 1, 3 }; // different experiments repetition
const std::string experiments_names[] = {"Random", "Ascending",
                                       "Descending", "Random [1,3]"};



int appendRes(string filename, const long res[EXPERIMENTS_COUNT][FUNCS_COUNT][2]) {
    fstream result;

    result.open(filename, std::ios_base::app);
    if (!result.is_open()) {
        cout << "Failed to open file: file is opened" << filename << '\n';
        return -1;
    }
    else {
        for(int i = 0; i < EXPERIMENTS_COUNT; i++){
            for(int j = 0; j < FUNCS_COUNT; j++){
                result << res[i][j][0] << " " << res[i][j][1];
                if(j!=FUNCS_COUNT-1)
                    result << " | ";
            }
            result << "\n";
        }
        result << "\n";
        cout << "Chunk written to file successfully" << endl;
    }

    return 0;
}





void randArr(int *arr, int size){
    for(int i = 0; i < size; i++){
        arr[i] = rand()%(size+1);
    }
}
void ascArr(int *arr, int size){
    for(int i = 0; i < size; i++){
        arr[i] = i;
    }
}
void descArr(int *arr, int size){
    for(int i = 0; i < size; i++){
        arr[i] = size-i;
    }
}
void randLowArr(int *arr, int size){
    int max = 3;
    for(int i = 0; i < size; i++){
        arr[i] = rand()%max + 1;
    }
}

void printRes(const long res[EXPERIMENTS_COUNT][FUNCS_COUNT][2]){
    for(int i = 0; i < FUNCS_COUNT; i++) {
        for(int j = 0; j < EXPERIMENTS_COUNT; j++){
            cout << experiments_names[j] << ": " << endl << "  ";
            double time_ms = (double) res[j][i][0]/1000;    // convert microseconds to milliseconds
            long comparisons = res[j][i][1];
            cout << sort_algs_names[i] << ":   " << time_ms << " millisecs \t";
            cout << comparisons << " comparisons" << endl;
        }
        cout << endl;
    }
}

void expsFuncs(long res[EXPERIMENTS_COUNT][FUNCS_COUNT][2], const int size){
    // Three arrays are used: arr_init is changed only once initialized,
    // arr1 is sorted and time is recorded,
    // arr2 is sorted and number of comparisons is recorded.
    // arr1 and arr2 are initalized to be equal to arr_init on each round
    int arr_init[size], arr1[size], arr2[size];

    for(int k = 0; k < EXPERIMENTS_COUNT; k++){
        for(int i = 0; i < FILL_TYPE_EXPERIMENT_REPS[k]; i++){
            (fill_types[k])(arr_init, size);

            for(int j = 0; j < FUNCS_COUNT; j++){
                copy(arr_init, arr_init+size, arr1);
                copy(arr_init, arr_init+size, arr2);
                auto start = chrono::high_resolution_clock::now(); 
                (sort_algs[j])(arr1, size);
                auto stop = chrono::high_resolution_clock::now();
                long duration = (chrono::duration_cast<chrono::microseconds>(stop - start)).count();

                long comparisons = (sort_algs_verb[j](arr2, size));
                res[k][j][0] += duration;
                res[k][j][1] += comparisons;
            }
        }
        for(int i = 0; i < FUNCS_COUNT; i++) {
            res[k][i][0] /= FILL_TYPE_EXPERIMENT_REPS[k];
            res[k][i][1] /= FILL_TYPE_EXPERIMENT_REPS[k];
        }
    }
}

void performExperiment(){
    for(int i = 7; i <= 15; i++){
        cout << "****** 2^" << i << " ******" << endl;
        long res[EXPERIMENTS_COUNT][FUNCS_COUNT][2] = {};
        expsFuncs(res, pow(2, i));
        printRes(res);
        appendRes("data.txt", res);
        cout << "*****************" << endl << endl;
    }
}


void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}
