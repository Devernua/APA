cmake_minimum_required(VERSION 3.6)
project(APA)

#set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c APA.h APA.c lab4/encrypt.c lab4/decrypt.c lab3/pow_mod.c lab3/cycle_pow_mod.c)
add_executable(APA ${SOURCE_FILES})
add_executable(Decrypt lab4/decrypt.c APA.h APA.c)
add_executable(Encrypt lab4/encrypt.c APA.h APA.c)
add_executable(lab3 lab3/pow_mod.c APA.h APA.c)
add_executable(lab3_2 lab3/cycle_pow_mod.c APA.c APA.h)