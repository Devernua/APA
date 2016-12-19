#include "APA.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
//    std::cout << "Hello, World!" << std::endl;
    srand (time(NULL));
    uint256_t a={0},b = {0},c = {0}, d={0};
    generate_uint256(a);
    generate_uint256(b);
    generate_uint256(c);
    //print(a);
    //print(b);
    add_uint256(a,b,c);
    sub_uint256(c,b,d);
    //print(c);
    //sub(c,a,d);
  //  if (cmp(d,b) == 0) printf("TRUE\n");
//    if(cmp(c,b) > 0) printf("TRUE\n");

   // print(d);
    //pow(a,b,c,d);
    //printf("\n");
    print_uint256(a);
    print_uint256(b);
    print_uint256(c);
    print_uint256(d);

    printf("%d\n", cmp_uint256(c,d));
    return 0;
}