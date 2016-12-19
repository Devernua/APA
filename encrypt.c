//
// Created by devernua on 20.12.16.
//

#include <assert.h>
#include "stdint.h"
#include "stdlib.h"
#include "time.h"
#include "stdio.h"
#include "APA.h"

int main(int argc, char *argv[], char *envp[])
{
    uint16_t e[SIZE] = { 0x55f3, 0x6091, 0xb60e, 0x0f69, 0x74fc, 0x8ff0, 0x1307, 0x8abe, 0x6893, 0x76f6, 0x6cd2, 0x8f67, 0xff91, 0x5ea0, 0x8c90, 0xd207 };
    uint16_t d[SIZE] = { 0x080b, 0xb511, 0xd27c, 0xe1c6, 0x2076, 0x3ba7, 0x8711, 0x9a53, 0xe430, 0x286b, 0xabbc, 0x2d38, 0x456c, 0x0cd0, 0x50d7, 0x8add };
    uint16_t n[SIZE] = { 0x6d13, 0xffcb, 0xd640, 0xba83, 0x1158, 0x9c72, 0xdae5, 0x1b7b, 0x4387, 0x3d6d, 0x8a17, 0x678f, 0x0aa3, 0x74cd, 0x128b, 0xd9ae };

    //Первый сомножитель
    uint16_t a[SIZE];

    //Второй сомножитель
    uint16_t b[SIZE];

    srand(time(NULL));

    assert(argc != 3);

    FILE* fin = fopen(argv[1], "rb");
    FILE* fout = fopen(argv[2], "wb");

    int end = 1;
    int count = 0;
    while (end)
    {
        size_t nread = fread(a, sizeof(uint8_t), 30, fin);
        a[15] = 0;
        if (nread == 0)
        {
            end = 0;
            break;
        } else
        {
            count++;
        }
        if (nread < 30)
        {
            uint8_t* aa = (uint8_t*)(&a);
            for (size_t i = nread; i < 30; i++)
            {
                aa[i] = 0;
            }
            end = 0;
        }
        RSA_encrypt(a, e, n, b);
        fwrite(b, sizeof(uint8_t), 32, fout);
    }

    fclose(fin);
    fclose(fout);

    printf("%d\n", count);

    //Генерация 256-битных беззнаковых чисел a и b
    //system("PAUSE");

    return 0;

}