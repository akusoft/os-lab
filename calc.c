#include <stdio.h>

struct calc{
    char *type;
    int price;
    int (*plus)(int a, int b);
    int (*multiply)(int a, int b);
};

int
int_plus(int a, int b){
    return a+b;
}

int
int_multiply(int a, int b){
    return a*b;
}

struct calc int_calc = {
    .type = "Integer Calculator",
    .price = 10,
    .plus = int_plus,
    .multiply = int_multiply,
};

int
main(void){
    struct calc *calc;
    calc = &int_calc;
    printf("%s\n", calc->type);
    printf("￥%d\n", calc->price);
    printf("3+5=%d\n", calc->plus(3, 5));
    printf("3*5=%d\n", calc->multiply(3, 5));
    return 0;
}