//
// Created by devernua on 19.12.16.
//

#ifndef APA_APA_H
#define APA_APA_H

#include <stdint.h>

#define SIZE 16

typedef uint16_t uint256_t[SIZE];
typedef uint16_t uint512_t[SIZE * 2];

//typedef uint16_t WORD;
//typedef uint32_t DWORD;

#define LOWORD(T) ((uint16_t) (T)     )
#define HIWORD(T) ((uint16_t) (T>>16) )
#define MAKEWORD(a,b)  ((((uint16_t)(a)) <<  8) + b)
#define MAKEDWORD(a,b) ((((uint32_t)(a)) << 16) + b)

void Generate(uint256_t digit);
void Print(const uint256_t digit);
int Cmp(const uint256_t a, const uint256_t b);


uint16_t Add(const uint256_t a, const uint256_t b, uint256_t c);
uint16_t Sub(const uint256_t a, const uint256_t b, uint256_t c);

void Mul(const uint256_t a, const uint256_t b, uint512_t c);
void Div(const uint512_t U, const uint256_t V, uint256_t Q, uint256_t R);

void MulMod(const uint256_t a, const uint256_t b, const uint256_t n, uint256_t c);
void Pow(const uint256_t a, const uint256_t b, const uint256_t n, uint256_t c);

void RSA_encrypt(const uint256_t M, const uint256_t e, const uint256_t n, uint256_t C);
void RSA_decrypt(const uint256_t C, const uint256_t d, const uint256_t n, uint256_t M);

#endif //APA_APA_H