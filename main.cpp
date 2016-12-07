#include "utils.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main() {
//    std::cout << "Hello, World!" << std::endl;
    srand (time(NULL));
    uint256_t a={0},b = {0},c = {0}, d={0};
    generate(a);
    generate(b);
    //print(a);
    //print(b);
    //add(a,b,c);
    //print(c);
    //sub(c,a,d);
  //  if (cmp(d,b) == 0) printf("TRUE\n");
//    if(cmp(c,b) > 0) printf("TRUE\n");

   // print(d);
    b[15]=0;
    div(a,b,c,d);
    printf("\n");
    print(a);
    print(b);
    print(c);
    print(d);

    return 0;
}