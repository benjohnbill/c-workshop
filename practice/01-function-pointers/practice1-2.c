#include <stdio.h>

// typedef struct _buyer{
//     void normal;
//     void VIP;
// } Buyer;

int basic_sale(int price){
    return price / 100;
}
int VIP_sale(int price){
    return price / 20;
}

int main(void){
    int price = 10000;
    int (*sale)(int);
    sale = basic_sale;
    printf("일반 회원 적립금: %d원\n", sale(price));
    sale = VIP_sale;
    printf("VIP 회원 적립금: %d원\n", sale(price));
    return 0;
}
