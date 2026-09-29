#include <stdio.h>

typedef struct _instance{
    int val;
    int count;
    int rcount;
} inst;

typedef struct _measure{
    inst f;
    inst s;
    inst th;
} Method;

void reset(inst *x){
    x->val = 0;
    x->rcount++;
}

void calib(inst *x, int a){
    x->val += a;
    x->count++;
}

int main(void){
    Method x = {
    .f = { .val = 18, .count = 0, .rcount = 0},
    .s = { .val = 31, .count = 0, .rcount = 0},
    .th = { .val = 12, .count = 0, .rcount = 0},
    };

    printf("Start %d, %d, %d\n", x.f.val, x.s.val, x.th.val);
    calib(&x.f, 4);
    calib(&x.s, -3);
    calib(&x.th, 0);
    calib(&x.th, 5);
    printf("\nAfter calibration:\n vals=%d %d %d\n", x.f.val, x.s.val, x.th.val);
    printf("calibtrations=%d %d %d\n", x.f.count, x.s.count, x.th.count);
    printf("resets= %d %d %d\n", x.f.rcount, x.s.rcount, x.th.rcount);
    // After Reset
    reset(&x.f);
    printf("\nAfter reset:\nvals=%d %d %d\n", x.f.val, x.s.val, x.th.val);
    printf("calibrations=%d %d %d\n", x.f.count, x.s.count, x.th.count);
    // reset();
    printf("resets= %d %d %d\n", x.f.rcount, x.s.rcount, x.th.rcount);
    return 0;
}
