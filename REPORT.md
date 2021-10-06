# Sort Algorithms comparison
Repository: *https://github.com/archy-co/imss_sort_algs.git*

In this work 4 sorting algorithms -- **Insertion sort**, **Merge Sort**, **Selection Sort** and **Shell Sort** -- were implemented and compared in time and number of comparisons in 4 different cases:
* **Random array** (5 experiments were performed and average value was taken). Max value -- array size+1
* **Ascending array** with values already sorted. Max value -- array size+1
* **Descending array** with values sorted in reverse order. Max value -- array size + 1
* **Random Low array** -- contains only elements from the set *{1, 2, 3}* - that is, the array with many repeated elements (3 experiments were performed and the average value was taken)

Each of the 4 algorithms was ran in all of the 4 cases mentioned above for arrays of size 2^7, 2^8, .. up to 2^15 inclusive (array size step = 2)

The result of the experiments are graphs, built with **matplotlib**

Note that different algorithms are used to record algorithm time and number of comparison: when recording time, optimized algorithm is used without any rudiments, but for number of comparisons slightly modified version of algorithms are used (with suffix `_verb` in the name) with comparisons' counter.

## Hardware Specification for Experiments
Experiments were performed with the following key hardware parameters:
* CPU: Intel Core i5-10210U CPU @ 1.60GHz, 8 cores
* Memory: SO-DIMM 8GB @ 2666 MHz 
* OS: Linux (I use Arch, btw)

## Algorithms
Following code is written in C++. For more, reffer to **src/insertion_sort.cpp**, **src/merge_sort.cpp**, **src/selection_sort.cpp**, **src/shell_sort.cpp** and related files
### Insertion Sort
``` C++
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
```
### Merge Sort
##### Merge sort recursive algorithm
``` C++
void merge_sort(int* arr, int l, int r){
    if(r > l){
        int m = l + (r - l) / 2;
        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}
```
##### Merge function
``` C++
void merge(int* arr, int l, int m, int r){ int arr_l_p = m-l+1, arr_r_p = r-m;
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
```
### Selection Sort
``` C++
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
```
### Shell Sort
``` C++
void shell_sort(int* arr, int size){
    for (int gap = size/2; gap > 0; gap /= 2) {
        for (int i = gap; i < size; i++) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}
```
## Experiments
`expsFuncs` function performs experiments and writes experiment data to file
The code below omits some important nuances such as imports or declaration/definition of some constants and functions. For more, reffer to **src/experiment.cpp**. Algorithms' modifications that count comparisons are implemented in **src/_algorithm_name_.cpp** below the main algorithm in the file.
``` C++
#define EXPERIMENTS_COUNT 4
#define FUNCS_COUNT 4

// sort_algs is an array of optimized functions that sort an array
void (*sort_algs[])(int*, int) = { selection_sort, insertion_sort, merge_sort, shell_sort };

// sort_algs_verb is an array of funcitons that sort an array and return number of comparisons
long (*sort_algs_verb[])(int*, int) = { selection_sort_verb, insertion_sort_verb, merge_sort_verb, shell_sort_verb };

// fill_types is an array of functions that generate arrays (random array, ascending array, descending array, and random array of set {1, 2, 3})
void (*fill_types[])(int*, int) = { randArr, ascArr, descArr, randLowArr };

// how many times each of experiments will be performed (random array will be performed 5 times and average will be taken; random array of set {1, 2, 3} is performed 3 times; in 2 other cases- only once)
const int FILL_TYPE_EXPERIMENT_REPS[EXPERIMENTS_COUNT] = { 5, 1, 1, 3 }; // different experiments repetition

void performExperiment(){
    for(int i = 7; i <= 15; i++){
        long res[EXPERIMENTS_COUNT][FUNCS_COUNT][2] = {};
        expsFuncs(res, pow(2, i));
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
```
#### Results
##### Random array
| ![Comparisons](https://raw.githubusercontent.com/archy-co/imss_sort_algs/main/graphs/0_comp.png) | ![Time](https://raw.githubusercontent.com/archy-co/imss_sort_algs/main/graphs/0_time.png) |
| :----------------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------: |

Selection sort is a bit slower than Insertion sort but generally correlates with it. Next, shell sort. Until some array size (in the given experiments until ~2^12) it has less comparisons and has better execution time then merge sort, but since array size = ~2^12 merge sort becomes better and shell sort increases more and more.
##### Sorted array
| ![Comparisons](https://raw.githubusercontent.com/archy-co/imss_sort_algs/main/graphs/1_comp.png) | ![Time](https://raw.githubusercontent.com/archy-co/imss_sort_algs/main/graphs/1_time.png) |
| :----------------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------: |

Insertion sort always preforms the best in this case, because it has least comparisons and best execution time. For arrays of size < 2^8 its execution time is is zero microseconds when run on the diven machine. Next, shell sort -- it is based on insertion sort so it is also reasonably fast and is 2nd least among all 4 algorithms in time and comparisons number. Then goes merge sort and the worst is selection sort.
##### Reverse-sorted array
| ![Comparisons](https://raw.githubusercontent.com/archy-co/imss_sort_algs/main/graphs/2_comp.png) | ![Time](https://raw.githubusercontent.com/archy-co/imss_sort_algs/main/graphs/2_time.png) |
| :----------------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------: |

In this case insertion sort and selection sort have worst execution time and comparisons number which coincides for both, as both will perform n^2 comparisons to sort reverse-ordered array. Better is merge sort and the best performance has shell sort
##### Random {1,2,3} array
| ![Comparisons](https://raw.githubusercontent.com/archy-co/imss_sort_algs/main/graphs/3_comp.png) | ![Time](https://raw.githubusercontent.com/archy-co/imss_sort_algs/main/graphs/3_time.png) |
| :----------------------------------------------------------------------------------------------: | :---------------------------------------------------------------------------------------: |

Execution time and comparisons number of this experiment correlates with the results of random array. However, for given array sizes, shell sort is always the best and performs better than merge sort. Insertion sort is the 3rd best and the worst one is selection sort.


## Conclusion
So selection sort performs in each experiment the largest number of comparisons and works for the longest period of time. Insertion sort's performance is the best only in case the array is already sorted. In most of the other cases merge sort and shell sort are significantly better than previous two and usually are close one to another. However, for random array, merge sort becomes better than shell sort starting from some array size (in the experiment conducted this array size was ~2^12) meanwhile comparisons of shell sort increasingly augments. In the same time, shell sort performs better for arrays with many repetitive elements.

## Author
Yaroslav Revera, UCU CS student
