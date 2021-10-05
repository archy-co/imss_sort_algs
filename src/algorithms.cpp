#include "../include/algorithms.h"

void (*sort_algs[])(int*, int) = { insertion_sort, merge_sort,  
                                   selection_sort, shell_sort };

long (*sort_algs_verb[])(int*, int) = { insertion_sort_verb, merge_sort_verb,  
                                        selection_sort_verb, shell_sort_verb };

