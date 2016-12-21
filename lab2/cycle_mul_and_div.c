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

    for (size_t i = 0 ; i < 1024; i++)
    {
        printf("%zu\n", i);

        uint256_t dig1 = {0}, dig2 = {0};
        uint256_t res2 = {0}, res3 = {0};
        uint512_t res1 = {0};
        uint256_t zero = {0};

        Generate(dig1);
        Generate(dig2);

        Mul(dig1, dig2, res1);
        Div(res1, dig2, res2, res3);

        if (Cmp(res2, dig1) != 0 || Cmp(res3, zero) != 0) {
            Print(dig1);
            Print(dig2);

            for (size_t j = 32; j > 0; j--)
            {
                printf("%04x", res1[j - 1]);
            }
            printf("\n");
            Print(res2);
            Print(res3);
        }
    }

    return 0;
}