#include <stdio.h>

int larger(int a, int b){
    if (a >= b){
        return a;
    } else {
        return b;
    }
}

int smaller(int a, int b){
    if (a < b){
        return a;
    } else{
        return b;
    }
}

int main(void){
    int a = 12;
    int b = 7;
    int (*comp)(int a, int b);
    comp = larger;
    printf("큰 값: %d\n", comp(a, b));
    comp = smaller;
    printf("작은 값: %d\n", comp(a, b));
    return 0;
}
