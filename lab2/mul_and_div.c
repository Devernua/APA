//
// Created by devernua on 20.12.16.
//

#include <stdlib.h>
#include <time.h>
#include <printf.h>
#include "../APA.h"

int main()
{
    srand((unsigned int) time(NULL));

    uint256_t dig1 = {0}, dig2 = {0};
    uint256_t res2 = {0}, res3 = {0};
    uint512_t res1 = {0};

    Generate(dig1);
    Generate(dig2);

    Mul(dig1, dig2, res1);
    Div(res1, dig2, res2, res3);

    Print(dig1);
    Print(dig2);

    for (size_t i = 32; i > 0; i--)
    {
        printf("%04x", res1[i - 1]);

    }
    printf("\n");

    Print(res2);
    Print(res3);

    printf("result of compare: %d\n", Cmp(res2, dig1));
    uint256_t zero = {0};
    printf("result of compare: %d\n", Cmp(res3, zero));

    return 0;
}