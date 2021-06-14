#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include "../RungeKutta.hpp"
#define MU 2.0
#define MAXITER 1000
#define ARRAY_LENGTH(array) (sizeof(array)) / sizeof(array[0])

float _f0(float t, float *x) {
    return x[1] + MU*x[0] - pow(x[0], 3);
}

float _f1(float t, float *x) {
    return (-1)*x[0];
}

/* execute Runge Kutta */
void execute_rk (int dimension, float (*f[])(float t, float *x), float begint, float maxtime, float init[]) {
    RungeKutta rk = RungeKutta(f, begint, maxtime, init, MAXITER, dimension);
    for (int i = 0; i < MAXITER; ++i) {
        std::cout << rk.getValue(i, 0) << " " << rk.getValue(i, 1) << std::endl;
    }
}

int main() {
    /* define dynamics */
    float (*f[2])(float, float*);
    f[0] = _f0;
    f[1] = _f1;

    /* Parameters */
    float InitialValuesset[][2] = {
        {-3.0, -2.5},
        {-3.0, -2.0},
        {-3.0, -1.5},
        {-3.0, -1.0},
        {-3.0, -0.5},
        {-3.0, 0.5},
        {-3.0, 1.0},
        {-3.0, 2.0},
        {-3.0, 2.5},
        {1.0, 3.0},
        {-1.0, -3.0},
        {3.0, -2.5},
        {3.0, -2.0},
        {3.0, -1.5},
        {3.0, -1.0},
        {3.0, -0.5},
        {3.0, 0.5},
        {3.0, 1.0},
        {3.0, 1.5},
        {3.0, 2.0},
        {3.0, 2.5},
        {0.1, 0.1},
        {-0.1, -0.1},
        {0.1, -0.1},
        {-0.1, 0.1},
    };

    int set_size = ARRAY_LENGTH(InitialValuesset);
    float maxt = 20.0;
    int dim = 2;

    for (int k = 0; k < set_size; k++) {
        execute_rk(dim, f, 0.0, maxt, InitialValuesset[k]);
        std::cout << std::endl;
        std::cout << std::endl;
    }
}