#include <stdio.h>

typedef struct _comparision{
    int l;
    int r;
    int (*choose)(int x, int y);
} Comparision;

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
    } else {
        return b;
    }
}

int main(void){
// Case 1(larger)

    Comparision obj1;
    obj1.l = 12;
    obj1.r = 7;
    obj1.choose = larger;

    Comparision obj2;
    obj2.l = 4;
    obj2.r = 9;
    obj2.choose = smaller;

    int x1 = obj1.choose(obj1.l, obj1.r);
    int y1 = obj2.choose(obj2.l, obj2.r);
    printf("\n첫 번째: %d\n", x1);
    printf("두 번째: %d\n", y1);

// Case 2(smaller)
    obj1.choose = smaller;
    int x2 = obj1.choose(obj1.l, obj1.r);
    int y2 = obj2.choose(obj2.l, obj2.r);
    printf("변경 후 첫 번째: %d\n", x2);
    printf("변경 후 두 번째: %d\n", y2);
    return 0;
}
