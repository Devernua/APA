cmake_minimum_required(VERSION 3.6)
project(APA)

set(SOURCE_FILES
        APA.h APA.c
        lab4/encrypt.c
        lab4/decrypt.c
        lab3/pow_mod.c
        lab3/cycle_pow_mod.c
        lab2/mul_and_div.c
        lab2/cycle_mul_and_div.c
        lab1/add_and_sub.c
        lab1/cycle_add_and_sub.c
        )

add_executable(Decrypt lab4/decrypt.c APA.h APA.c)
add_executable(Encrypt lab4/encrypt.c APA.h APA.c)
add_executable(lab3 lab3/pow_mod.c APA.h APA.c)
add_executable(lab3_2 lab3/cycle_pow_mod.c APA.c APA.h)
add_executable(lab2 lab2/mul_and_div.c APA.c APA.h)
add_executable(lab2_2 lab2/cycle_mul_and_div.c APA.c APA.h)
add_executable(lab1 lab1/add_and_sub.c APA.c APA.h)
add_executable(lab1_2 lab1/cycle_add_and_sub.c APA.c APA.h)