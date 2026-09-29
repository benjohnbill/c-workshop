#include <stdio.h>
#include <stdlib.h>

typedef struct _contact{
    char *name;
    char *memo;
} Contact;

void change(Contact *c){
    if (!c || !c->memo){
        return;
    }
    c->memo = "malloc and free";
}

int main(void){
    Contact *c = malloc(sizeof(*c));
    if (c == NULL){
        perror("Allocation failed");
        return 1;
    }

    c->name = "Mina";
    c->memo = "C study";

    printf("\n%s: %s\n" , c->name, c->memo);
    change(c);
    printf("%s: %s\n" , c->name, c->memo);
    free(c);
    c = NULL;

    return 0;
}
