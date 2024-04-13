/**
Filename: pcolor.c (implementation of pcolor.h)
Description: Print character with some color in terminal
Prepared by: Asisten IF2110
Created at: 17/10/2019
Modified at: 23/10/2023
**/


#include "Color/pcolor.hpp"

void print_red(string c)
{
    std::cout << RED << c << NORMAL;
}

void print_green(string c)
{
    std::cout << GREEN << c << NORMAL;
}

void print_blue(string c)
{
    std::cout << BLUE << c << NORMAL;
}
