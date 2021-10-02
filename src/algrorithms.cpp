#include "include/algorithms.h"

void shell_sort(int* arr, int size){
    // Start with a big gap, then reduce the gap
    for (int gap = size/2; gap > 0; gap /= 2) {
        // Do a gapped insertion sort for this gap size.
        // The first gap elements a[0..gap-1] are already in gapped order
        // keep adding one more element until the entire array is
        // gap sorted
        for (int i = gap; i < size; i++) {
            // add a[i] to the elements that have been gap sorted
            // save a[i] in temp and make a hole at position i
            int temp = arr[i];
 
            // shift earlier gap-sorted elements up until the correct
            // location for a[i] is found
            int j;           
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
             
            //  put temp (the original a[i]) in its correct location
            arr[j] = temp;
        }
    }
}
 
void insertion_sort(int* arr, int size){
    for(int i = 1; i < size; i++){
        for(int j = i; j > 0; j--){
            if(arr[j] < arr[j-1]) {
                int temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
        }
    }
}

void selection_sort(int* arr, int size){
    int min_ind = 0;

    for(int i = 0; i < size; i++){
        min_ind = i;

        for(int j = i+1; j < size; j++){
            if(arr[j] < arr[min_ind])
                min_ind = j;
        }
        int temp = arr[i];
        arr[i] = arr[min_ind];
        arr[min_ind] = temp;
    }

}


void merge_sort(int* arr, int l, int r){
    if(r > l){
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
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
