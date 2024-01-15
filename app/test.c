#include <stdio.h>
#include <string.h>
#include <stdlib.h>


struct s {
    int field;
    int field2;
};

int main(){
    // int *some[10];
    //stack
    struct s my_stack;
    my_stack.field = 0;
    my_stack.field2 = 1;
    //calloc
    struct s *my_calloc;
    my_calloc = (struct s*) calloc(1, sizeof(struct s));
    my_calloc->field = 1;
    my_calloc->field2 = 2;
    //malloc
    struct s *my_malloc;
    my_malloc = (struct s*) malloc(sizeof(struct s));
    my_malloc->field = 3;
    my_malloc->field2 = 4;
    //memset
    struct s *my_memset;
    memset(&my_memset, 0, sizeof(struct s));
    my_malloc->field = 5;
    my_malloc->field2 = 6;
}