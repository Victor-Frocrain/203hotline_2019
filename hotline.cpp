/*
** EPITECH PROJECT, 2020
** yams
** File description:
** yams.cpp
*/

#include "hotline.hpp"
#include <string>
#include <fstream>
#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
#include <time.h>

void dispHelp()
{
    std::ifstream fs("help");

    if (!fs.fail()) {
        std::cout << fs.rdbuf() << std::endl;
    }
}

int parseArgs(char *arg1, char *arg2, Datas &datas)
{
    std::string s1(arg1);
    std::string s2(arg2);

    for (size_t i = 0; i < s1.length(); i++) {
        if (s1[i] < '0' || s1[i] > '9')
            return MY_ERROR;
    }
    for (size_t i = 0; i < s2.length(); i++) {
        if (s2[i] < '0' || s2[i] > '9')
            return MY_ERROR;
    }
    datas.n = std::stoi(s1);
    datas.k = std::stoi(s2);
    if (datas.k > datas.n)
        return MY_ERROR;
    return MY_SUCCESS;
}

int parseArgs(char *arg1, Datas &datas)
{
    std::string s1(arg1);

    for (size_t i = 0; i < s1.length(); i++) {
        if (s1[i] < '0' || s1[i] > '9')
            return MY_ERROR;
    }
    datas.d = std::stoi(s1);
    return MY_SUCCESS;
}

double factorial(double nb)
{
    double result = nb;

    if (nb == 0)
        return 1;
    for(nb--; nb > 1; nb--)
        result *= nb;
    return result;
}

double binomy(double n, double k)
{
    double i = 0;
    double j = 0;
    double p = 1;

    if (k < (n - k))
        i = k;
    else
        i = n - k;
    for (; j < i; j++) {
        p = p * (n - j) / (i - j);
    }
    return p;
}

std::string makeString(unsigned __int128 nb)
{
    std::string copy = "";
    std::string result = "";

    for (; nb > 0; nb /= 10)
        copy += nb % 10 + '0';
    for (int i = copy.length() - 1; i >= 0; i--)
        result += copy[i];
    return result;
}

unsigned __int128 coefficent(Datas &datas)
{
    unsigned __int128 result = 1.0;
    for (int x = 0; x < datas.k; x++)
        result = result * (datas.n - x) / (x + 1);
    return result;
}

int computeAll(Datas &datas, bool coef)
{
    int result = MY_SUCCESS;
    double X = 0.0;
    int nb1 = 0;
    int nb2 = 0;
    double p = 0.0;
    double n = 3500;
    double overload = 0.0;
    double app = (datas.d / (8.0 * 3600.0));
    double apoisson = 3500 * app;
    clock_t t;

    if (coef) {
        X = datas.k;
        nb1 = X;
        nb2 = datas.n;
        std::cout << nb1 << "-combinations of a set of size " << nb2 << ":" << std::endl;
        std::cout << makeString(coefficent(datas)) << std::endl;
    }
    else {
        std::cout << "Binomial distribution:" << std::endl;
        t = clock();
        for (; X <= 50; X++) {
            p = binomy(n, X) * std::pow(app, X) * std::pow((1.0 - app), (n - X));
            nb1 = X;
            std::cout << nb1 << " -> " << std::fixed << std::setprecision(3) << p;
            if (nb1 != 4 && nb1 != 9 && nb1 != 14 && nb1 != 19 && nb1 != 24 && nb1 != 29 && nb1 != 34 && nb1 != 39 && nb1 != 44 && nb1 != 49 && nb1 != 50)
                std::cout << "\t";
            else
                std::cout << std::endl;
            if (X <= 25)
                overload += p;
        }
        overload = 1 - overload;
        overload *= 100;
        std::cout << "Overload: " << std::fixed << std::setprecision(1) << overload << "%" << std::endl;
        std::cout << "Computation time: " << std::fixed << std::setprecision(2) << ((float)t)/CLOCKS_PER_SEC * 1000 << " ms" << std::endl;

        std::cout << std::endl << "Poisson distribution:" << std::endl;
        t = clock();
        for (X = 0, overload = 0; X <= 50; X++) {
            p = std::exp(-apoisson) * std::pow(apoisson, X) / factorial(X);
            nb1 = X;
            std::cout << nb1 << " -> " << std::fixed << std::setprecision(3) << p;
            if (nb1 != 4 && nb1 != 9 && nb1 != 14 && nb1 != 19 && nb1 != 24 && nb1 != 29 && nb1 != 34 && nb1 != 39 && nb1 != 44 && nb1 != 49 && nb1 != 50)
                std::cout << "\t";
            else
                std::cout << std::endl;
            if (X <= 25)
                overload += p;
        }
        overload = 1 - overload;
        overload *= 100;
        std::cout << "Overload: " << std::fixed << std::setprecision(1) << overload << "%" << std::endl;
        std::cout << "Computation time: " << std::fixed << std::setprecision(2) << ((float)t)/CLOCKS_PER_SEC * 1000 << " ms" << std::endl;
    }
    return result;
}

int hotline(int ac, char **args)
{
    int result = MY_SUCCESS;
    Datas datas;

    if (ac < 2)
        result = MY_ERROR;
    else if (ac == 2) {
        std::string arg(args[1]);
        if (arg == "-h")
            dispHelp();
        else if (parseArgs(args[1], datas) == MY_ERROR)
            return MY_ERROR;
        else
            result = computeAll(datas, false);
    }
    else if (ac == 3) {
        if (parseArgs(args[1], args[2], datas) == MY_ERROR)
            return MY_ERROR;
        else {
            result = computeAll(datas, true);
        }
    }
    else
        result = MY_ERROR;
    return result;
}