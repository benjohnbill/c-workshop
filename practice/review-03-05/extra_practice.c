#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _memo{
    char *str;
    int time;
    int count;
} Memo;

// void add_memo(Memo *m){

// }

// void change(Memo *m, char *s){
//     m->str = s;
//     m->time = 45;
//     m->count++;
//     printf("Check %d: %s, %d\n", m->count, m->str, m->time);
// }


    // If wanting to use change(),
    // 1. new string malloc()
    // 2. strcpy/memcpy from s to the new string
    // 3. free(outdated m->str)
    // 4. m->str = new string adress

int main(void){
    char input[32] = "original";
    Memo *m = malloc(sizeof(*m));
    m->str = malloc(sizeof(input));
    m->time = 30;
    m->count = 0;
    memcpy(m->str, input, sizeof(input));
    strcpy(input, "changed");
    printf("Check Original input[]\n %s\n\n", m->str);
    printf("Check m->str : \nCount %d: \n'%s', %d\n\n", m->count, m->str, m->time);
    printf("Check input[] : \nCount %d: \n'%s', %d\n", m->count, input, m->time);

    // change(m, "Changed");
    // change(m, "Rechanged");
    free(m->str);
    free(m);
    m = NULL;
    return 0;
}
