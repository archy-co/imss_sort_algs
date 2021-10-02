#include "../include/algorithms.h"

void (*sort_algs[])(int*, int) = { selection_sort, insertion_sort,
                                   merge_sort, shell_sort };

long (*sort_algs_verb[])(int*, int) = { selection_sort_verb, insertion_sort_verb,
                                        merge_sort_verb, shell_sort_verb };

