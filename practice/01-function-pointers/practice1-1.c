#include <stdio.h>

typedef struct _tree{
    int left;
    int *right;
    int (*operation)(int, int *);
} Calculator;

int add(int a, int *b){
    return a + *b;
}

int subtract(int a, int *b){
    return a - *b;
}

int main(void) {
    // Case 1
    int (*fp)(int, int *) = add;
    int x = 10;
    int y = 3;
    printf("add: %d\n", fp(x, &y));
    fp = subtract;
    printf("subtract: %d\n", fp(x, &y));

    // Case 2
    Calculator c;
    c.left = 20;
    *c.right = 5;
    c.operation = add;
    int result1 = c.operation(c.left, c.right);
    c.operation = subtract;
    int result2 = c.operation(c.left, c.right);
    printf("add: %d\n subtract: %d\n", result1, result2);
    return 0;
}
