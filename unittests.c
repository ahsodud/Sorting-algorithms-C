#include <assert.h>
#include <string.h>
#include <stdio.h>

void runTests();

int main() {
    runTests();
    printf("All tests passed!\n");
    return 0;
}

void runTests() {
    char elements_to_sort[MAX_SIZE][MAX_SIZE];
    char sort_type[7];
    char data_type[7];
    
    // Test case 1: Valid input
    char *argv1[] = {"./a2", "bubble", "int", "3", "1,2,3"};
    assert(ErrorsCheck(5, argv1, sort_type, data_type, 3, elements_to_sort) == 0);
    assert(strcmp(sort_type, "bubble") == 0);
    assert(strcmp(data_type, "int") == 0);
    assert(strcmp(elements_to_sort[0], "1") == 0);
    assert(strcmp(elements_to_sort[1], "2") == 0);
    assert(strcmp(elements_to_sort[2], "3") == 0);

    // Test case 2: Invalid algorithm
    char *argv2[] = {"./a2", "invalid", "int", "3", "1,2,3"};
    assert(ErrorsCheck(5, argv2, sort_type, data_type, 3, elements_to_sort) == 2);

    // Test case 3: Invalid data type
    char *argv3[] = {"./a2", "bubble", "invalid", "3", "1,2,3"};
    assert(ErrorsCheck(5, argv3, sort_type, data_type, 3, elements_to_sort) == 3);

    // Test case 4: Element count is not an integer
    char *argv4[] = {"./a2", "bubble", "int", "abc", "1,2,3"};
    assert(ErrorsCheck(5, argv4, sort_type, data_type, 3, elements_to_sort) == 4);

    // Test case 5: Invalid element count (less than 1)
    char *argv5[] = {"./a2", "bubble", "int", "0", "1,2,3"};
    assert(ErrorsCheck(5, argv5, sort_type, data_type, 0, elements_to_sort) == 5);

    // Test case 6: Not enough elements given
    char *argv6[] = {"./a2", "bubble", "int", "3", "1,2"};
    assert(ErrorsCheck(5, argv6, sort_type, data_type, 3, elements_to_sort) == 6);

    // Test case 7: Too many elements given
    char *argv7[] = {"./a2", "bubble", "int", "3", "1,2,3,4"};
    assert(ErrorsCheck(5, argv7, sort_type, data_type, 3, elements_to_sort) == 7);

    // Test case 8: Invalid number of arguments
    char *argv8[] = {"./a2", "bubble", "int", "3"};
    assert(ErrorsCheck(4, argv8, sort_type, data_type, 3, elements_to_sort) == 1);
}

