//
// Created by devernua on 20.12.16.
//

#include <string.h>
#include <assert.h>
#include "stdint.h"
#include "stdio.h"
#include "../APA.h"

int main(int argc, char *argv[], char *envp[])
{
    //uint256_t e = { 0xd65d, 0xbb19, 0xf996, 0xbed4, 0xecb2, 0xeff1, 0x80d5, 0xab77, 0xd9a7, 0x71d2, 0xbafe, 0xa396, 0x4d49, 0xe1e3, 0x95aa, 0x1367 };
    uint256_t d = {0x1545, 0xdeb8, 0xc548, 0x72c6, 0x2180, 0x2f06, 0xa69b, 0xd15e, 0x5b4f, 0x2da8, 0xee7c, 0x740b, 0x07bf, 0x2bf2, 0x794b, 0x279d };
    uint256_t n = {0x6d13, 0xffcb, 0xd640, 0xba83, 0x1158, 0x9c72, 0xdae5, 0x1b7b, 0x4387, 0x3d6d, 0x8a17, 0x678f, 0x0aa3, 0x74cd, 0x128b, 0xd9ae };

    assert(argc == 3);

    FILE *in = fopen(argv[1], "rb");
    FILE *out = fopen(argv[2], "wb");

    size_t count = 0;
    uint256_t M = {0};
    size_t size = fread(M, sizeof(uint8_t), 32, in);
    while (size) {
        uint256_t b = {0};
        count++;
        RSA_decrypt(M, d, n, b);
        uint8_t s[32] = {0};
        for (size_t i = 0; i < 16; i++) {
            s[2 * i] = (uint8_t) (b[i] >> 8);
            s[2 * i + 1] = (uint8_t) b[i];
        }
        size = fread(M, sizeof(uint8_t), 32, in);

        fwrite(s, sizeof(uint8_t), (size) ? 30 : strlen((char *) s), out);
    }

    fclose(in);
    fclose(out);

    printf("%zu\n", count);

    return 0;

}