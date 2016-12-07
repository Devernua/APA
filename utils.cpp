//
// Created by devernua on 07.12.16.
//

#include "utils.h"
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <stdio.h>


void generate(uint256_t digit)
{
    for (size_t i = 0; i < SIZE; i++){
        digit[i] = (uint16_t) MAKEWORD((rand() % 0xFF), (rand() % 0xFF));
    }
}

void assign(uint16_t * a, const uint16_t * b, size_t size = SIZE)
{
    for (size_t i = 0; i < size; i++) {
        a[i] = b[i];
    }
}

void print(const uint256_t digit)
{
    for (size_t i = SIZE; i > 0; i--)
    {
        printf("%04x", digit[i - 1]);
    }
    printf("\n");
}

int cmp(const uint256_t a, const uint256_t b)
{
    for (size_t i = SIZE; i > 0; i--)
    {
        if (a[i - 1] > b[i - 1])
        {
            //Ïåðâîå ÷èñëî áîëüøå a > b
            return 1;
        }
        if (a[i - 1] < b[i - 1])
        {
            //Âòîðîå ÷èñëî áîëüøå b > a
            return -1;
        }
    }

    //×èñëà ðàâíû a == b
    return 0;
}

uint16_t add(const uint256_t a, const uint256_t b, uint256_t c)
{
    // Бит переноса разряда при сложении
    uint16_t d = 0;

    //Результат элементарного сложения слов
    uint32_t T;

    for (size_t i = 0; i < SIZE; i++)
    {
        //Элементарное сложение слов чисел с битом переноса
        T = (uint32_t)(a[i]) + (uint32_t)(b[i]) + (uint32_t)(d);

        //Сохранение полученного при сложении слова
        c[i] = LOWORD(T);

        //Установка бита переноса, возникающего при выходе значения T за границы слова
        d = HIWORD(T);
    }

    //Возврат бита переноса
    return d;
}

uint16_t sub(const uint256_t a, const uint256_t b, uint256_t c)
{
    // Бит переноса разряда при вычитании
    uint16_t d = 0;

    //Результат элементарного вычитания слов
    uint32_t T;

    for (uintmax_t i = 0; i < SIZE; i++)
    {
        //Элементарное вычитание слов чисел с битом переноса
        T = (uint32_t)(a[i]) - (uint32_t)(b[i]) - (uint32_t)(d);

        //Сохранение полученного при вычитании слова
        c[i] = LOWORD(T);

        //Установка бита переноса, возникающего при переполнении T
        d = (HIWORD(T) == 0) ? 0 : 1;
    }

    //Возврат бита переноса
    return d;
}

void mul(const uint256_t a, const uint256_t b, uint512_t c)
{
    //Слово переноса разряда при умножении
    uint16_t d;

    //Результат элементарного умножения слов
    uint32_t T;


    for (size_t i = 0; i < SIZE; i++)
    {
        //Обнуление переноса
        d = 0;

        for (size_t j = 0; j < SIZE; j++)
        {
            //Элементарное умножение слов чисел с переносом
            T = (uint32_t)c[i + j] + (uint32_t)a[i] * (uint32_t)b[j] + (uint32_t)d;

            //Сохранение полученного при умножении слова
            c[i + j] = LOWORD(T);

            //Перенос разряда
            d = HIWORD(T);
        }

        //Сохранение переноса в следующий разряд
        c[i + SIZE] = d;
    }
}

//Подпрограмма умножения длинного беззнакового числа на слово
// a - умножаемое число длинной size слов
// b - множитель длинной в 1 слово
// c - произведение a и b, размером size слов
//  Возвращаемые значения:
//     слово переноса
uint16_t mult_word(const uint256_t a, const uint16_t b, uint16_t* const c)
{
    //Результат элементарного умножения слов
    uint32_t T;

    //Слово переноса разряда при умножении
    uint16_t d = 0;

    for (size_t i = 0; i < SIZE; i++)
    {
        //Элементарное умножение слов с переносом
        T = (uint32_t)a[i] * (uint32_t)b + (uint32_t)d;

        //Сохранение полученного при умножении слова
        c[i] = LOWORD(T);

        //Перенос разряда
        d = HIWORD(T);
    }

    //Возврат слова переноса
    return d;
}

uint16_t mult_word2(const uint512_t a, const uint16_t b, uint512_t c)
{
    //Результат элементарного умножения слов
    uint32_t T;

    //Слово переноса разряда при умножении
    uint16_t d = 0;

    for (size_t i = 0; i < SIZE*2; i++)
    {
        //Элементарное умножение слов с переносом
        T = (uint32_t)a[i] * (uint32_t)b + (uint32_t)d;

        //Сохранение полученного при умножении слова
        c[i] = LOWORD(T);

        //Перенос разряда
        d = HIWORD(T);
    }

    //Возврат слова переноса
    return d;
}

//Подпрограмма деления длинного беззнакового числа на слово
// a - делимое число длинной size слов
// b - делитель длинной в 1 слово
// c [Nullable] - частное a и b, размером size слов
// r [Nullable] - остаток от деления a на b, размером 1 слово
//  Возвращаемые значения:
//     остаток от деления
uint16_t div_word(const uint256_t a, const uint16_t b, uint256_t c, uint16_t* const r)
{
    //Элементарное делимое
    uint32_t T = 0;

    if (b == 0)
    {
        //Деление на ноль
        return UINT16_MAX;
    }

    for (size_t i = SIZE; i > 0; i--)
    {
        //Старшее слово - остаток предыдущего элементарного деления
        T <<= sizeof(uint16_t) * 8;

        //Младшее слово - очередное слово делимого числа
        T |= a[i - 1];

        //Сохранение результата элементарного деления
        c[i - 1] = LOWORD(T / (uint32_t)b);

        //Сохраниние остатка
        T %= b;
    }

    if (r != NULL)
    {
        //Сохраниние остатка в переменную r, если она передана
        *r = LOWORD(T);
    }

    //Возврат остатка
    return LOWORD(T);
}

uint16_t div_word2(const uint512_t a, const uint16_t b, uint256_t c, uint16_t* const r)
{
    //Элементарное делимое
    uint32_t T = 0;

    if (b == 0)
    {
        //Деление на ноль
        return UINT16_MAX;
    }

    for (size_t i = SIZE*2; i > 0; i--)
    {
        //Старшее слово - остаток предыдущего элементарного деления
        T <<= sizeof(uint16_t) * 8;

        //Младшее слово - очередное слово делимого числа
        T |= a[i - 1];

        //Сохранение результата элементарного деления
        c[i - 1] = LOWORD(T / (uint32_t)b);

        //Сохраниние остатка
        T %= b;
    }

    if (r != NULL)
    {
        //Сохраниние остатка в переменную r, если она передана
        *r = LOWORD(T);
    }

    //Возврат остатка
    return LOWORD(T);
}

// U - делимое
// V - делитель
// Q - частное
// R - остаток
void div(const uint512_t U, const uint256_t V, uint256_t Q, uint256_t R)
{
    uint16_t q, buf1, buf2;                /* для промежуточного хранения */
    uint16_t U2[33] = {0};   /* для нормализованного U */
    uint16_t V2[SIZE + 1] = {0},   /* для нормализованного V */
             R2[SIZE + 1] = {0};	/* для промежуточного умножения */
    uint32_t inter;                     /* для промежуточных операций */
    uintmax_t i, j, k;                          /* индексные переменные */
    uint16_t d;                            /* нормализующий множитель */



    // ReSharper disable once CppPossiblyErroneousEmptyStatements
    for (i = SIZE; (i > 0)&(!V[i - 1]); i--);  /* анализ делителя, отсекаем старшие незначащие нули */
    size_t sizeV = i;                          /* новый размер делителя */
    if (sizeV == 0) return;                  /* исключение "Деление на ноль" (просто уходим) */

    // ReSharper disable once CppPossiblyErroneousEmptyStatements
    for (k = SIZE*2; (k > 0)&(!U[k - 1]); k--);  /* анализ делимого, отсекаем старшие незначащие нули */
    size_t sizeU = k;                          /* новый размер делимого */

    if (sizeV > sizeU)                     /* если делитель больше делимого, то */
    {
        if (R != NULL) assign(R, U);        /* остаток равен делимому */
        return;                        /* уходим */
    }
    if (sizeV == 1)                   /* если делитель - 1 слово, то */
    {
        div_word2(U, V[0], Q, R);     /* применяем упрощенный алгоритм */
        return;                        /* уходим */
    }

    /*--- Нормализация: */
    d = (uint16_t)(((uint32_t)UINT16_MAX + 1) / ((uint32_t)V[sizeV - 1] + 1)); /* нормализующий множитель */
    if (d != 1)                            /* если d не 1, */
    {
        V2[sizeV] = mult_word(V, d, V2);   /* умножаем V на d */
        U2[sizeU] = mult_word2(U, d, U2);   /* умножаем U на d */
    }
    else
    {                                   /* если d == 1, */
        assign(V2, V, sizeV);             /* V2 = V */
        V2[sizeV] = 0;
        assign(U2, U, sizeU);             /* U2 = U */
        U2[sizeU] = 0;
    }

    /*--- Основной цикл */
    for (j = sizeU; j >= sizeV; j--)           /* организация главного цикла по j (sizeU-sizeV раз) */
    {
        /*--- Очередное слово частного */
        inter = MAKEDWORD(U2[j], U2[j - 1]); /* пригодится */
        if (U2[j] == V2[sizeV - 1])          /* если старшие слова равны, */
            q = UINT16_MAX;                 /* слово частного q = MAXDIGIT */
        else {                        /* иначе */
            q = (uint16_t)(inter / V2[sizeV - 1]);/* j-е слово частного q находим делением */
            /* если q великоват, */

            /*--- Коррекция слова частного */
            if (((uint32_t)V2[sizeV - 2] * q) > (MAKEDWORD((uint16_t)(inter%V2[sizeV - 1]), U2[j - 2])))
            {
                q--;    /* коррекция слова частного уменьшением q на 1 */
            }
        }

        /*--- Вычитание кратного делителя */
        uint256_t TMP ={0};
        assign(TMP, V2, sizeV);
        buf1 = mult_word(TMP, q, R2);  /* умножаем V на q */
        for (int i = 0; i < SIZE; i++) TMP[i] = 0;
        assign(TMP, U2 + j - sizeV, sizeV);
        buf2 = sub(TMP, R2, TMP);/* вычитаем результат умножения *////ATTENTION
        assign(U2 + j - sizeV, TMP, sizeV);
        inter = (uint32_t)U2[j] - buf1 - buf2;
        //U2[j] = LOWORD(inter); //Never used

        /*--- Коррекция остатка и частного */
        if (HIWORD(inter))              /* если результат шага отрицательный, */
        {                               /* компенсирующее сложение */
            for (int i = 0; i < SIZE; i++) TMP[i] = 0;
            assign(TMP, U2 + j - sizeV, sizeV);
            /*buf2 = */add(TMP, V2, TMP);///ATTENTION
            assign(U2 + j - sizeV, TMP, sizeV);
            //U2[j] += buf2; //Never used
            q--;                        /* коррекция слова частного q на 1 */
        }
        if (Q != NULL)                           /* если адрес частного Q не 0, */
            Q[j - sizeV] = q;               /* запоминаем j-е слово частного q */
    }

    /*--- Завершение */
    if (R != NULL)                               /* если адрес остатка R не 0, */
    {
        uint256_t TMP ={0};
        assign(TMP, U2, sizeV);
        div_word(TMP, d, R, NULL);   /* денормализация остатка R */
    }
}

void multMod(const uint256_t a, const uint256_t b, const uint256_t n, uint256_t c)
{
    uint512_t e = {0};
    uint256_t tmp = {0};
    mul(a,b,e);
    div(e,n,tmp,c);
}

void pow(const uint256_t a, const uint256_t b, const uint256_t n, uint256_t c)
{
    size_t i;
    c[0] = 1;

    for(i = 1; i < SIZE; i++)
        c[i] = 0;

    for(i = 16 * SIZE-1; i > 0; i--)
    {
        printf("%d\n", i);
        multMod(c,c,n,c);
        if((b[i/16]>>(i%16))&1)
            multMod(c,a,n,c);
    }
}