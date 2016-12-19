//
// Created by devernua on 19.12.16.
//

#include "APA.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

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
  uint16_t d = 0;  //бит переноса
  uint32_t T;

  for (size_t i = 0; i < size; i++)
  {
    T = (uint32_t)(a[i]) + (uint32_t)(b[i]) + (uint32_t)(d);
    c[i] = LOWORD(T);
    d = HIWORD(T);
  }

  return d;
}

uint16_t add_uint256(const uint256_t a, const uint256_t b, uint256_t c){
  return _add(a, b, SIZE, c);
}

uint16_t _sub(uint16_t const * const a, uint16_t const * const b, const size_t size, uint16_t * const c)
{
  uint16_t d = 0;  //бит переноса
  uint32_t T;

  for (size_t i = 0; i < size; i++)
  {
    T = (uint32_t)(a[i]) - (uint32_t)(b[i]) - (uint32_t)(d);
    c[i] = LOWORD(T);
    d = (HIWORD(T) == 0) ? 0 : 1;
  }

  return d;
}

uint16_t sub_uint256(const uint256_t a, const uint256_t b, uint256_t c){
  return _sub(a, b, SIZE, c);
}
