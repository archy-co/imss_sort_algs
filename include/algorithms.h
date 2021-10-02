#ifndef ALGORIMTHS_H
#define ALGORIMTHS_H
#include <iostream>

#define FUNCS_COUNT 4

void insertion_sort(int* arr, int size);
void shell_sort(int* arr, int size);
void selection_sort(int* arr, int size);
void merge_sort(int *arr, int r, int l);

void merge_sort(int *arr, int r);
void merge(int *arr, int l, int m, int r);

long insertion_sort_verb(int* arr, int size);
long shell_sort_verb(int* arr, int size);
long selection_sort_verb(int* arr, int size);

long merge_verb(int* arr, int l, int m, int r);
long merge_sort_verb(int* arr, int size);
long merge_sort_verb(int* arr, int l, int r, long *comps);

const std::string sort_algs_names[] = {"Selection Sort", "Insertion Sort",
                                       "Merge Sort    ", "Shell Sort    "};

extern void (*sort_algs[])(int*, int);
extern long (*sort_algs_verb[])(int*, int);

#endif // ALGORIMTHS_H
