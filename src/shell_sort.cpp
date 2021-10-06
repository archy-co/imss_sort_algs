void shell_sort(int* arr, int size){
    for(int gap = size/2; gap > 0; gap /= 2){
        for(int i = gap; i < size; i++){
            int temp = arr[i];
 
            int j = i;
            for (; (j >= gap) && (temp < arr[j-gap]); j -= gap)
                arr[j] = arr[j-gap];
             
            arr[j] = temp;
        }
    }
}

long shell_sort_verb(int* arr, int size){
    int comps = 0;
    for(int gap = size/2; gap > 0; gap /= 2, comps++){
        for(int i = gap; i < size; i++, comps++){
            int temp = arr[i];
 
            int j = i;
            for(; (j >= gap) && (temp < arr[j-gap]); j -= gap, comps+=2)
                arr[j] = arr[j-gap];
             
            arr[j] = temp;
        }
    }
    return comps;
}
