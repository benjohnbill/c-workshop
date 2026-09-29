#include <stdio.h>

typedef struct _measure{
    int one;
    int two;

} Method;

void reset(int *x){
    *x = 0;
}

void calib(int *x, int *y){
    *x = *x + 4;
    *y = *y - 3;
}

int main(void){
    Method m = { .one = 18, .two = 31};
    calib(&(m.one), &(m.two));
    printf("After calibration: %d %d\n", m.one, m.two);
    reset(&(m.one));
    printf("After reset: %d %d\n", m.one, m.two);
}
