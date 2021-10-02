#include "../include/algorithms.h"
#include <iostream>

void merge_sort(int* arr, int l, int r){
    if(r > l){
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// Initializing function called by user
void merge_sort(int* arr, int size){
    int l = 0;
    if(size-1 > l){
        int m = l + (size-1 - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, size-1);
        merge(arr, l, m, size-1);
    }
}

void merge(int* arr, int l, int m, int r){
    int arr_l_p = m-l+1, arr_r_p = r-m;
    int arr_l[arr_l_p], arr_r[arr_r_p];

    for(int i = 0; i < arr_l_p; i++)    arr_l[i] = arr[l+i];
    for(int i = 0; i < arr_r_p; i++)    arr_r[i] = arr[m+1+i];

    int i = 0, j = 0, n = l;
    while(i < arr_l_p && j < arr_r_p){
        if(arr_l[i] <= arr_r[j]) {
            arr[n] = arr_l[i];
            i++;
        }
        else{
            arr[n] = arr_r[j];
            j++;
        }
        n++;
    }

    while(i < arr_l_p){
        arr[n] = arr_l[i];
        n++, i++;
    }
    while(j < arr_r_p){
        arr[n] = arr_r[j];
        n++, j++;
    }
}

long merge_sort_verb(int* arr, int l, int r, long *comps){
    (*comps)++;
    if(r > l){
        int m = l + (r - l) / 2;
        merge_sort_verb(arr, l, m, comps);
        merge_sort_verb(arr, m + 1, r, comps);
        (*comps) += merge_verb(arr, l, m, r);
    }
    return *comps;
}

// Initializing function called by user
long merge_sort_verb(int* arr, int size){
    long comps = 0;
    int l = 0;
    comps++;
    if(size-1 > l){
        int m = l + (size-1 - l) / 2;
        merge_sort_verb(arr, l, m, &comps);
        merge_sort_verb(arr, m + 1, size-1, &comps);
        comps += merge_verb(arr, l, m, size-1);

    }
    return comps;
}

long merge_verb(int* arr, int l, int m, int r){
    long comps = 0;

    int arr_l_p = m-l+1, arr_r_p = r-m;
    int arr_l[arr_l_p], arr_r[arr_r_p];

    for(int i = 0; i < arr_l_p; i++, comps++)    arr_l[i] = arr[l+i];
    for(int i = 0; i < arr_r_p; i++, comps++)    arr_r[i] = arr[m+1+i];

    int i = 0, j = 0, n = l;
    comps++;        // first while loop conditional comparison
    while(i < arr_l_p && j < arr_r_p){
        comps+=2;   // while loop conditional comparison

        comps++;    // if statement comparison
        if(arr_l[i] <= arr_r[j]) {
            arr[n] = arr_l[i];
            i++;
        }
        else{
            arr[n] = arr_r[j];
            j++;
        }
        n++;
    }

    comps++;
    while(i < arr_l_p){
        comps++;
        arr[n] = arr_l[i];
        n++, i++;
    }
    comps++;
    while(j < arr_r_p){
        comps++;
        arr[n] = arr_r[j];
        n++, j++;
    }
    return comps;
}
