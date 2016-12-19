#include "APA.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand (time(NULL));

    uint256_t a={0},b = {0},c = {0}, d={0}, r ={0};
    uint512_t m={0};
    Generate(a);
    Generate(b);
    Generate(c);
    Print(a);
    Print(b);
    Mul(a, b, m);
    Print(m + 16);
    Print(m);
    printf("\n");

    Div(m, c, a, r);

    Print(c);
    Print(a);
    Print(r);

    printf("\n");


    Print(r);

    printf("URA\n");
    Generate(a);
    Generate(b);
    Generate(c);

    Add(a, b, c);
    Sub(c, b, d);

    Print(a);
    Print(b);
    Print(c);
    Print(d);

    printf("%d\n", Cmp(c, d));
    return 0;
}