#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

// Define the struct properly using typedef
typedef struct {
    char color[11];
    char breed[16];
    int age;
} Cat;

// Function prototype
void add_to_age(Cat* cat);

int main(int argc, char* argv[]) {
    Cat felix;
    printf("Enter the color of the cat: ");
    scanf("%10s", felix.color);

    strcpy(felix.breed, "persian");

    printf("Enter the age of the cat: ");
    scanf("%d", &felix.age);

    add_to_age(&felix);  // Correct function call

    // Correct memory allocation using typedef'd Cat
    Cat* garfield = (Cat*) calloc(1, sizeof(Cat));
    garfield->age = 6;

    free(garfield);

    Cat cats[5]; // Correct memory allocation

    for (int i = 0; i < 5; i++) {
        cats[i].age = i * 4;
    }

    // Incorrect memory allocation
    Cat* cats2 = (Cat*) calloc(5, sizeof(Cat));
    free(cats2); // Correct memory deallocation
    return 0;
}

// Function definition
void add_to_age(Cat* cat) {
    cat->age += 7;
}
