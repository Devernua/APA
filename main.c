#include "APA.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
    srand (time(NULL));

    uint256_t a={0},b = {0},c = {0}, d={0}, r ={0};
    uint512_t m={0};
    generate_uint256(a);
    generate_uint256(b);
    generate_uint256(c);
    print_uint256(a);
    print_uint256(b);
    mul_uint256(a,b,m);
    print_uint256(m+16);
    print_uint256(m);
    printf("\n");

    div_uint256(m,c,a,r);

    print_uint256(c);
    print_uint256(a);
    print_uint256(r);

    printf("\n");




    print_uint256(r);

    printf("URA\n");
    generate_uint256(a);
    generate_uint256(b);
    generate_uint256(c);

    add_uint256(a,b,c);
    sub_uint256(c,b,d);

    print_uint256(a);
    print_uint256(b);
    print_uint256(c);
    print_uint256(d);

    printf("%d\n", cmp_uint256(c,d));
    return 0;
}