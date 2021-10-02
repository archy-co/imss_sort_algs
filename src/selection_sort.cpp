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

long selection_sort_verb(int* arr, int size){
    long comps = 0;
    int min_ind = 0;

    for(int i = 0; i < size; i++, comps++){
        min_ind = i;

        for(int j = i+1; j < size; j++, comps+=2){
            if(arr[j] < arr[min_ind]) {
                min_ind = j;
            }
        }
        int temp = arr[i];
        arr[i] = arr[min_ind];
        arr[min_ind] = temp;
    }
    return comps;
}
