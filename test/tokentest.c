#include <stdio.h>
#include <string.h>

int main() {
    char str[] = "Hello, world! This is a test string.";
    const char delim[] = " ,.!"; // Delimiters are space, comma, period, and exclamation mark
    char *token, *saveptr;

    // Initial call to strtok_r
    token = strtok_r(str, delim, &saveptr);
    //printf("%s\n", token);
    // Subsequent calls to strtok_r
    while (token != NULL) {
        printf("Token: %s\n", token);
        token = strtok_r(NULL, delim, &saveptr);
    }

    return 0;
}


