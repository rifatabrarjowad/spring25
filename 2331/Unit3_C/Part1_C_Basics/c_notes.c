// Rifat Abrar Jowad
#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> 
#include <stdint.h> 
#define YEAR 2025
int a();
int b();
int main(int argc, char *argv[]) {
    printf("Hello World!\n");
    printf("The year is %d\n", YEAR);

    uint8_t x = 255; 
    x++; 
    printf("X is now: %d\n", x); 

    if(!x){
        printf("Not X\n");
    }
    for (uint8_t a = 0; a < 10; a++){
        printf("%d\n", a);
    }
    int b = 90;
    do {
        printf("%d\n", b);
        b--;
    } while (b > 80);

    a();
    return 0;
}
int a(){
    return b();
}
int b(){
    return 0;
}