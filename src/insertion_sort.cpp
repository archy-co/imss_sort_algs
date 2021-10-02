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

long insertion_sort_verb(int* arr, int size){
    long comps = 0;
    for(int i = 1; i < size; i++, comps++){
        for(int j = i; j > 0; j--, comps+=2){
            if(arr[j] < arr[j-1]) {
                int temp = arr[j];
                arr[j] = arr[j-1];
                arr[j-1] = temp;
            }
        }
    }
    return comps;
}
