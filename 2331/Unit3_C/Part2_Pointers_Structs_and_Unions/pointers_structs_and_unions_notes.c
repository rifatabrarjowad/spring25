#include <stdio.h> 
#include <stdlib.h> 
int main(int argc, char *argv[]) {
    // int x;
    // int* x_pointer  = &x; // memory adress 
    // *x_pointer = 6;
    // printf("Before: %p %d\n", x_pointer, x);
    // x_pointer += 1;
    // printf("After: %p\n", x_pointer);
    // printf("%ld %ld\n", sizeof(int), sizeof(x));
    // int y = (int) 3.14;
    // int* malloced = (int*) malloc(sizeof(int));
    // printf("%d", *malloced);
    // int* calloced = (int*) calloc(1,sizeof(int));
    // *calloced = 7;
    // printf("Before: %p %d\n", calloced, *calloced);
    // free(calloced);
    // printf("After: %p %d\n", calloced, *calloced);
    // int number[5];
    // *(number + 3) = 4;
    // int* number2 = (int*) calloc(5, sizeof(int));
    // number2[3] = 7;
    // number2[10] = 9;
    // number2[-1] = 8;
    char word[11];
    printf("Enter a word: ");
    scanf("%10s", word);
    printf("%s\n", word);

    return 0;
}