//
// Created by devernua on 20.12.16.
//

#include <stdlib.h>
#include <time.h>
#include <printf.h>
#include "../APA.h"

int main()
{
    srand(time(NULL));


    uint256_t dig, res1, res2, tmp;

    for (size_t i = 0 ; i < 1024; i++)
    {
        printf("%u\n", i);

        uint256_t dig1 = {0}, dig2 = {0};
        uint256_t res2 = {0}, res3 = {0};
        uint512_t res1 = {0};
        Generate(dig1);
        Generate(dig2);

        Add(dig1, dig2, res1);
        Sub(res1, dig2, res2);

        if (Cmp(res2,dig1) != 0){
            Print(dig1);
            Print(dig2);

            Print(res1);
            Print(res2);
        }
    }

    return 0;
}