/* 
    execute: ./a.out 1 > 3.6_flow_1
    gnuplot:
        set xrange [0:20]
        set yrange [-2:2]
        set zrange [-2:2]
        set xlabel "x"
        set ylabel "y"
        set zlabel "z"
        splot "./3.6_flow_1" with lines
*/

#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include "../RungeKutta.hpp"
#define MAXITER 1000
#define ARRAY_LENGTH(array) (sizeof(array)) / sizeof(array[0])

/* Ex.1 */
float _f0(float t, float *x) {
    return 1.0;
}

float _f1(float t, float *x) {
    return x[2];
}

float _f2(float t, float *x) {
    return (-1)*x[1];
}

/* Ex.2 */
float _g0(float t, float *x) {
    return x[0];
}

float _g1(float t, float *x) {
    return x[2]*x[0];
}

float _g2(float t, float *x) {
    return 2*x[2] - 2*x[1]/x[0];
}


/* execute Runge Kutta */
void execute_rk (int dimension, float (*f[])(float t, float *x), float begint, float maxtime, float init[]) {
    RungeKutta rk = RungeKutta(f, begint, maxtime, init, MAXITER, dimension);
    for (int i = 0; i < MAXITER; ++i) {
        std::cout << rk.getValue(i, 0) << " " << rk.getValue(i, 1) << " " << rk.getValue(i, 2) << std::endl;
    }
}

int main(int argc, char *argv[]) {
    /* output error message */
    if (argc != 2) {
        std::cerr << "Out of range! Please input 1 values." << std::endl;
        return -1;
    }

    int choice_dynamics;
    choice_dynamics = std::stoi(argv[1]);

    if (choice_dynamics >= 3 || choice_dynamics <= 0) {
        std::cerr << "Out of range! Choose 1 or 2!" << std::endl;
        return -1;
    }

    /* define function */
    float (*f[3])(float, float*);
    f[0] = _f0;
    f[1] = _f1;
    f[2] = _f2;

    float (*g[3])(float, float*);
    g[0] = _g0;
    g[1] = _g1;
    g[2] = _g2;

    int dim = 3;

    if (choice_dynamics == 1) {
        float init[3] = {0.0, 1.0, 0.0};
        float maxt = 20.0;
        execute_rk(dim, f, 0.0, maxt, init);
    }
    else {
        float init[3] = {-2.0, -5.0, 5.0};
        float maxt = 5.0;
        execute_rk(dim, g, 0, maxt, init);
    }
}