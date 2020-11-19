/*
** EPITECH PROJECT, 2020
** hotline
** File description:
** hotline.hpp
*/

#include <vector>

#ifndef HOTLINE_HPP_
#define HOTLINE_HPP_

#define MY_ERROR 84
#define MY_SUCCESS 0

int hotline(int ac, char **args);

class Datas {
    public:
    int n;
    int k;
    int d;
    std::vector<double> tab[5];
};

#endif /* HOTLINE_HPP_ */
