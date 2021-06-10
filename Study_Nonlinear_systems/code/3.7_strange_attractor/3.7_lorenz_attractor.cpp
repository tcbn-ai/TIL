#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include "../RungeKutta.hpp"
#define MAXITER 1000
#define SIGMA 10
#define R 28
#define B 8/3

/* Lorenz */
float _f0(float t, float *x) {
    return (-1)*SIGMA*(x[0] - x[1]);
}

float _f1(float t, float *x) {
    return (-1)*x[1] - x[0]*x[2] + R*x[0];
}

float _f2(float t, float *x) {
    return x[0]*x[1] - B*x[2];
}

/* execute Runge Kutta */
void execute_rk (int dimension, float (*f[])(float t, float *x), float begint, float maxtime, float init[]) {
    RungeKutta rk = RungeKutta(f, begint, maxtime, init, MAXITER, dimension);
    for (int i = 0; i < MAXITER; ++i) {
        std::cout << rk.getValue(i, 0) << " " << rk.getValue(i, 1) << " " << rk.getValue(i, 2) << std::endl;
    }
}

int main() {
    /* define dynamics */
    float (*f[3])(float, float*);
    f[0] = _f0;
    f[1] = _f1;
    f[2] = _f2;

    /* Parameters */
    float init[] = {0.0, 4.0, 28.0};
    int dim = 3;
    float maxt = 10.0;

    execute_rk(dim, f, 0.0, maxt, init);
}