// project3.c
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LENGTH 15

// Function prototypes
void memDump(char *str);
int getHash(char *str);
bool isPalindrome(char *str);
void printFromIndex(char *str);
void reverseString(char *str);

int main() {
    char word[MAX_LENGTH + 1];
    int option;

    printf("Enter an all lowercase word, max of 15 characters: ");
    scanf("%15s", word);

    do {
        printf("\nChoose an option:\n");
        printf("1) Memory dump\n");
        printf("2) Print hash value\n");
        printf("3) Determine if your word is a palindrome\n");
        printf("4) Print the word from an index\n");
        printf("5) Reverse the string\n");
        printf("Option (number): ");
        scanf("%d", &option);

        switch (option) {
            case 1:
                memDump(word);
                break;
            case 2:
                printf("Hash value: %d\n", getHash(word));
                break;
            case 3:
                if (isPalindrome(word)) {
                    printf("Nice, \"%s\" is a palindrome :)\n", word);
                } else {
                    printf("Sadly, \"%s\" is not a palindrome :(\n", word);
                }
                break;
            case 4:
                printFromIndex(word);
                break;
            case 5:
                reverseString(word);
                printf("Reversed string: %s\n", word);
                break;
            default:
                printf("Invalid option, please try again.\n");
        }
    } while (option < 1 || option > 5);

    return 0;
}

void memDump(char *str) {
    printf("Memory Dump:\n");
    while (*str) {
        printf("%p %d %c\n", (void *)str, *str, *str);
        str++;
    }
}

int getHash(char *str) {
    int sum = 0, length = 0;
    while (*str) {
        sum += *str;
        length++;
        str++;
    }
    return sum / length;
}

bool isPalindrome(char *str) {
    char *start = str;
    char *end = str + strlen(str) - 1;
    while (start < end) {
        if (*start != *end) {
            return false;
        }
        start++;
        end--;
    }
    return true;
}

void printFromIndex(char *str) {
    int index;
    printf("What index should I start at? ");
    scanf("%d", &index);

    int length = strlen(str);
    if (index < 0 || index >= length) {
        printf("Oops! That isn’t a valid starting index, try again later.\n");
    } else {
        printf("So, \"%s\" starting at index %d is \"%s\"\n", str, index, str + index);
    }
}

void reverseString(char *str) {
    char *start = str;
    char *end = str + strlen(str) - 1;
    while (start < end) {
        char temp = *start;
        *start = *end;
        *end = temp;
        start++;
        end--;
    }
}
