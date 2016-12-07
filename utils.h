//
// Created by devernua on 07.12.16.
//

#ifndef APA_UTILS_H
#define APA_UTILS_H
#include <cstdint>
#include <cstdlib>

typedef uint16_t uint256_t[16];
typedef uint16_t uint512_t[32];
#define SIZE (sizeof(uint256_t) / sizeof(uint16_t))

#define LOWORD(T)((uint16_t)(T))
#define HIWORD(T)((uint16_t)(T>>16))
#define MAKEWORD(a,b) ((((uint16_t)(a))<<8) | b)
#define MAKEDWORD(a,b) ((((uint32_t)(a))<<16)+b)
//#define MAKELONG(a,b)((((uint32_t)(a))<<16)+b)

void generate(uint256_t digit);
void assign(uint16_t * a, const uint16_t *b, size_t size);
void print(const uint256_t digit);
int cmp(const uint256_t a, const uint256_t b);


uint16_t add(const uint256_t a, const uint256_t b, uint256_t c);
uint16_t sub(const uint256_t a, const uint256_t b, uint256_t c);
void mul(const uint256_t a, const uint256_t b, uint512_t c);

//Подпрограмма умножения длинного беззнакового числа на слово
// a - умножаемое число длинной size слов
// b - множитель длинной в 1 слово
// c - произведение a и b, размером size слов
//  Возвращаемые значения:
//     слово переноса
uint16_t mult_word(const uint256_t a, const uint16_t b, uint16_t* const c);
uint16_t mult_word2(const uint512_t a, const uint16_t b, uint512_t c);


//Подпрограмма деления длинного беззнакового числа на слово
// a - делимое число длинной size слов
// b - делитель длинной в 1 слово
// c [Nullable] - частное a и b, размером size слов
// r [Nullable] - остаток от деления a на b, размером 1 слово
//  Возвращаемые значения:
//     остаток от деления
uint16_t div_word(const uint256_t a, const uint16_t b, uint256_t c, uint16_t* const r);

uint16_t div_word2(const uint512_t a, const uint16_t b, uint256_t c, uint16_t* const r);

// U - делимое
// V - делитель
// Q - частное
// R - остаток

void div(const uint512_t U, const uint256_t V, uint256_t Q, uint256_t R);

void multMod(const uint256_t a, const uint256_t b, const uint256_t n, uint256_t c);

void pow(const uint256_t a, const uint256_t b, const uint256_t n, uint256_t c);

#endif //APA_UTILS_H
