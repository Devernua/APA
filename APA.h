//
// Created by devernua on 19.12.16.
//

#ifndef APA_APA_H
#define APA_APA_H

#include <stdint.h>

#define SIZE 16

typedef uint16_t uint256_t[SIZE];
typedef uint16_t uint512_t[SIZE * 2];

typedef uint16_t WORD;
typedef uint32_t DWORD;

#define LOWORD(T) ((uint16_t) (T)     )
#define HIWORD(T) ((uint16_t) (T>>16) )
#define MAKEWORD(a,b)  ((((uint16_t)(a)) <<  8) + b)
#define MAKEDWORD(a,b) ((((uint32_t)(a)) << 16) + b)

void generate_uint256(uint256_t digit);
void print_uint256(const uint256_t digit);
int cmp_uint256(const uint256_t a, const uint256_t b);


uint16_t add_uint256(const uint256_t a, const uint256_t b, uint256_t c);
uint16_t sub_uint256(const uint256_t a, const uint256_t b, uint256_t c);

void mul_uint256(const uint256_t a, const uint256_t b, uint512_t c);
void div_uint256(const uint512_t U, const uint256_t V, uint256_t Q, uint256_t R);

#endif //APA_APA_H