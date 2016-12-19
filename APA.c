//
// Created by devernua on 19.12.16.
//

#include "APA.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <assert.h>

void generate_uint256(uint256_t digit)
{
  for (size_t i = 0; i < SIZE; i++) {
    digit[i] = (uint16_t) MAKEWORD((rand() % 0xFF), (rand() % 0xFF));
  }
}

void print_uint256(const uint256_t digit)
{
  for (size_t i = SIZE; i > 0; i--)
  {
    printf("%04x", digit[i - 1]);
  }
  printf("\n");
}

int cmp_uint256(const uint256_t a, const uint256_t b)
{
  for (size_t i = SIZE; i > 0; i--)
  {
    if (a[i - 1] > b[i - 1])
    {
      // a > b
      return 1;
    }
    if (a[i - 1] < b[i - 1])
    {
      // b > a
      return -1;
    }
  }

  // a == b
  return 0;
}

void _assign(uint16_t * const a, uint16_t const * const b, const size_t size)
{
  for (size_t i = 0; i < size; i++) {
    a[i] = b[i];
  }
}

uint16_t _add(uint16_t const * const a, uint16_t const * const b, const size_t size, uint16_t * const c)
{
  uint16_t d = 0;
  uint32_t T;

  for (size_t i = 0; i < size; i++)
  {
    T = (uint32_t)(a[i]) + (uint32_t)(b[i]) + (uint32_t)(d);
    c[i] = LOWORD(T);
    d = HIWORD(T);
  }

  return d; //перенос
}

uint16_t add_uint256(const uint256_t a, const uint256_t b, uint256_t c){
  return _add(a, b, SIZE, c); //перенос
}

uint16_t _sub(uint16_t const * const a, uint16_t const * const b, const size_t size, uint16_t * const c)
{
  uint16_t d = 0;
  uint32_t T;

  for (size_t i = 0; i < size; i++)
  {
    T = (uint32_t)(a[i]) - (uint32_t)(b[i]) - (uint32_t)(d);
    c[i] = LOWORD(T);
    d = (HIWORD(T) == 0) ? 0 : 1;
  }

  return d;  //перенос
}

uint16_t sub_uint256(const uint256_t a, const uint256_t b, uint256_t c){
  return _sub(a, b, SIZE, c); //перенос
}

uint16_t _mul_word(uint16_t const * const a, const size_t size, const uint16_t b, uint16_t * const c)
{
    uint16_t d = 0;
    uint32_t T;

    for (size_t i = 0; i < size; i++)
    {
        T = (uint32_t)a[i] * (uint32_t)b + (uint32_t)d;
        c[i] = LOWORD(T);
        d = HIWORD(T);
    }
    return d; //перенос
}

void _mult(uint16_t const * const a, const size_t size_a, uint16_t const * const b, const size_t size_b, uint16_t* const c, const size_t size_c)
{
    uint16_t d;
    uint32_t T;

    assert(size_c >= size_a + size_b);

    for (size_t i = 0; i < size_c; i++) {
        c[i] = 0;
    }

    for (size_t i = 0; i < size_a; i++)
    {
        d = 0;
        for (size_t j = 0; j < size_b; j++)
        {
            T = (uint32_t)c[i + j] + (uint32_t)a[i] * (uint32_t)b[j] + (uint32_t)d;
            c[i + j] = LOWORD(T);
            d = HIWORD(T);
        }
        c[i + size_b] = d;
    }
}

void mul_uint256(const uint256_t a, const uint256_t b, uint512_t c){
    _mult(a, SIZE, b, SIZE, c, SIZE * 2);
}

void _div_word(uint16_t const * const a, const size_t size, const uint16_t b, uint16_t* const c, uint16_t* const r)
{
    uint32_t T = 0;

    assert(b != 0); //деление на ноль

    for (size_t i = size; i > 0; i--) {
        T <<= 16;
        T |= a[i - 1];
        if (c != NULL) c[i - 1] = LOWORD(T / (uint32_t) b);
        T %= b;
    }

    if (r != NULL) {
        *r = LOWORD(T);
    }
}

void _div(uint16_t const * const U, uint16_t const * const V, uint16_t* const Q, uint16_t* const R, size_t sizeU, size_t sizeV)
{
    uint16_t q, buf1, buf2;
    uint16_t U2[sizeU + 1],
             V2[sizeV + 1],
             R2[sizeV + 1];
    uint32_t inter;
    size_t i, j, k;
    uint16_t d;

    if (R != NULL) for (i = 0; i < sizeV; i++) R[i] = 0;
    if (Q != NULL) for (i = 0; i < sizeU; i++) Q[i] = 0;

    for (i = sizeV; (i > 0)&(!V[i - 1]); i--);
    sizeV = i;
    assert(sizeV != 0);

    for (k = sizeU; (k > 0)&(!U[k - 1]); k--);
    sizeU = k;

    if (sizeV > sizeU)
    {
        if (R != NULL) _assign(R, U, sizeU);
        return;
    }
    if (sizeV == 1)
    {
        _div_word(U, sizeU, V[0], Q, R);
        return;
    }


    d = (uint16_t)(((uint32_t)UINT16_MAX + 1) / ((uint32_t)V[sizeV - 1] + 1));
    if (d != 1)
    {
        V2[sizeV] = _mul_word(V, sizeV, d, V2);
        U2[sizeU] = _mul_word(U, sizeU, d, U2);
    }
    else
    {
        _assign(V2, V, sizeV);
        V2[sizeV] = 0;
        _assign(U2, U, sizeU);
        U2[sizeU] = 0;
    }


    for (j = sizeU; j >= sizeV; j--)
    {
        inter = MAKEDWORD(U2[j], U2[j - 1]);
        if (U2[j] == V2[sizeV - 1])
            q = UINT16_MAX;
        else {
            q = (uint16_t)(inter / V2[sizeV - 1]);

            if (((uint32_t)V2[sizeV - 2] * q) > (MAKEDWORD((uint16_t)(inter%V2[sizeV - 1]), U2[j - 2])))
            {
                q--;
            }
        }

        buf1 = _mul_word(V2, sizeV, q, R2);
        buf2 = _sub(U2 + j - sizeV, R2, sizeV, U2 + j - sizeV);
        inter = (uint32_t)U2[j] - buf1 - buf2;

        if (HIWORD(inter))
        {
            _add(U2 + j - sizeV, V2, sizeV, U2 + j - sizeV);
            q--;
        }
        if (Q != NULL)
            Q[j - sizeV] = q;
    }

    if (R != NULL)
    {
        _div_word(U2, sizeV, d, R, NULL);
    }
}

void div_uint256(const uint512_t U, const uint256_t V, uint256_t Q, uint256_t R){
    _div(U, V, Q, R, SIZE*2, SIZE);
}
