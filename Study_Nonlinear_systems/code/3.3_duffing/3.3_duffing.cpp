/* Duffing equation */
/* 
    reference:
        http://www.rain.hyarc.nagoya-u.ac.jp/~satoki/main/calc/Fortran/ODE/index.html
    execute: ./a.out choice_initial_value choice_process > time_response_[choice_initial_value]
    - choice_initial_value: 1 or 2
    - choice_process: 1, 2, or 3
        1. time response of x
        2. x-v space
        3. t-x-v space
    gnuplot:
        set xrange [0:250]
        set yrange [-2:2]
        set xlabel "t"
        set ylabel "x"
        plot "./time_response_[choice_initial_value]" with line
*/
#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include "../RungeKutta.hpp"
#define MAXITER 10000
#define DELTA 0.2  /* delta */
#define ALPHA -1.0  /* alpha */
#define BETA 1.0  /* beta */
#define GAMMA 1.0   /* gamma */
#define OMEGA 2*M_PI*0.2   /* Omega */
#define ARRAY_LENGTH(array) (sizeof(array)) / sizeof(array[0])

/* dynamics */
float _f0(float t, float *x) {
    return x[1];
}

float _f1(float t, float *x) {
    return (-1)*ALPHA*x[0] - BETA*pow(x[0], 3) - DELTA*x[1] + GAMMA*cos(OMEGA*t);
}

int main(int argc, char *argv[]) {
    /* output error message */
    if (argc != 3) {
        std::cerr << "Out of range! Please input 1 values." << std::endl;
        return(-1);
    }

    int choice_initial_value, choice_process;
    choice_initial_value = std::stoi(argv[1]);
    choice_process = std::stoi(argv[2]);

    if (choice_initial_value >= 3 || choice_initial_value <= 0) {
        std::cerr << "Out of range! (1: initial value (1), 2: initial value (2))" << std::endl;
        return(-1);
    }

    if (choice_process >= 4 || choice_process <= 0) {
        std::cerr << "Out of range! (1: plot t-x, 2: plot x-v, 3: plot t-x-v)" << std::endl;
        return(-1);
    }

    /* function f */
    float (*f[2])(float, float*);
    f[0] = _f0;
    f[1] = _f1;

    /* Parameters */
    float maxt = 250.0;
    int dim = 2;
    float dt = maxt/MAXITER;

    /* Initial value */
    float InitialValue[2];
    if (choice_initial_value == 1) {
        InitialValue[0] = 0.0;
        InitialValue[1] = 0.05;
    }
    else {
        InitialValue[0] = 0.0;
        InitialValue[1] = 0.06;
    }
    
    RungeKutta rk = RungeKutta(f, 0, maxt, InitialValue, MAXITER, dim);
    if (choice_process == 1) {
        /* t-x */
        for (int i = 0; i < MAXITER; ++i) {
            std::cout << dt*i << " " << rk.getValue(i, 0) << std::endl;
        }
    }
    else if (choice_process == 2) {
        /* x-v */
        for (int i = 0; i < MAXITER; ++i) {
            std::cout << rk.getValue(i, 0) << " " << rk.getValue(i, 1) << std::endl;
        }
    }
    else {
        /* t-x-v */
        for (int i = 0; i < MAXITER; ++i) {
            std::cout << dt*i << " " << rk.getValue(i, 0) << " " << rk.getValue(i, 1) << std::endl;
        }
    }
}