#include <stdio.h>

typedef struct _timer{
    char *name;
    int time;
} Timer;

typedef struct _timecount{
    int count;
    Timer one;
    Timer two;
} Timecount;

void pass(Timer *t){
    if (t->time == 1){
        t->time--;
        printf("[%s] done at 0\n", t->name);
    }
    if (t->time == 0){
        return;
    } t->time--;
}

int main(void){
    Timecount x = {
        .count = 3,
        .one = { .name = "tea", .time = 2 },
        .two = { .name = "stretch", .time = 3},
    };
    Timecount *t = &x;
    for (int i = 1; i <= t->count; i++){
        pass(&(t->one));
        pass(&(t->two));
        // if (t->one.time == 0){
        //     printf("[%s] done at 0\n", t->one.name);
        // } if (t->two.time == 0){
        //     printf("[%s] done at 0\n", t->two.name);
        // }
        printf("Round %d: tea = %d, strech = %d\n", i, t->one.time, t->two.time);
    }
    return 0;
}
