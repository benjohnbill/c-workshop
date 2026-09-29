#include <stdio.h>

int main(int argc, char *argv[]){
    printf("argc = %d\n", argc);
    for (int i = 0; i <= argc; i++){
        // slot address -> string address "string"
        printf("argv[%d] @ %p -> %p \"%s\"\n",
               i, (void *)&argv[i], (void *)argv[i],
               argv[i] ? argv[i] : "(NULL)");
    }
    return 0;
}
