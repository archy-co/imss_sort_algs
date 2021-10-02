#ifndef ARRAY_FILL_H
#define ARRAY_FILL_H

#include <iostream>
#include "../include/algorithms.h"


#define EXPERIMENTS_COUNT 4

void randArr(int *arr, int size);
void ascArr(int *arr, int size);
void descArr(int *arr, int size);
void randLowArr(int *arr, int size);
void printRes(const long res[FUNCS_COUNT][EXPERIMENTS_COUNT][2]);
void printArray(int* arr, int size);

void performExperiment();
void expsFuncs(long res[FUNCS_COUNT][EXPERIMENTS_COUNT][2], const int size);

extern void (*fill_types[EXPERIMENTS_COUNT])(int*, int);

extern const std::string experiments_names[];
extern const int FILL_TYPE_EXPERIMENT_REPS[EXPERIMENTS_COUNT]; // different experiments repetition


#endif // ARRAY_FILL_H
