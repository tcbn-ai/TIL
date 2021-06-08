/* fall mass */
#include <iostream>
#include <cmath>
#include "RungeKutta.hpp"
#define MAXITER 1000
#define G 9.8
#define GAMMA 5.0
#define ARRAY_LENGTH(array) (sizeof(array)) / sizeof(array[0])

class Dynamics {
    constexpr static float beginx = -5.0, endx = 5.0, beginv = -5.0, endv = 5.0, begint = 0.0, endt = 5.0, step = 0.2;
    public:
        Dynamics(){};
        void vector_field(float f_0(float t, float *x), float f_1(float t, float *x));
};


void Dynamics::vector_field(float f_0(float t, float *x), float f_1(float t, float *x)) {
    float xl, vl, dx, dv;
    for(xl = Dynamics::beginx; xl <= Dynamics::endx; xl += Dynamics::step) {
        for(vl = Dynamics::beginv; vl <= Dynamics::endv; vl += Dynamics::step) {
            float x[2] = {xl, vl};
            dx = f_0(0, x) * Dynamics::step * 0.1;
            dv = f_1(0, x) * Dynamics::step * 0.1;
            std::cout << xl << " " << vl << " " << dx << " " << dv << std::endl;
        }
    }
}


float _f0(float t, float * x) {
    return x[1];
}

float _f1(float t, float *x) {
    return (-1) * G;
}

float _g0(float t, float *x) {
    return x[1];
}

float _g1(float t, float *x) {
    return (-1)*G - GAMMA*x[1];
}

int main(int argc, char *argv[]) {

    /* output error message */
    if (argc != 3) {
        std::cerr << "Out of range! Please input 2 values." << std::endl;
        return(-1);
    }

    /* function f */
    float (*f[2])(float, float*);
    f[0] = _f0;
    f[1] = _f1;

    /* function g */
    float (*g[2])(float, float*);
    g[0] = _g0;
    g[1] = _g1;

    /* Initial values */
    float InitialValuesset[][2] = {
        {-5.0, 5.0},
        {-4.0, 5.0},
        {-3.0, 5.0},
        {-2.0, 5.0},
        {-1.0, 5.0},
        {0.0, 5.0},
        {1.0, 5.0},
        {2.0, 5.0},
        {3.0, 5.0},
        {-5.0, -5.0},
        {-4.0, -5.0},
        {-3.0, -5.0},
        {-2.0, -5.0},
        {-1.0, -5.0},
        {0.0, -5.0},
        {1.0, -5.0},
        {2.0, -5.0},
        {3.0, -5.0},
    };

    /* Parameters */
    int set_size = ARRAY_LENGTH(InitialValuesset);
    float maxt = 5.0;
    int dim = 2;

    int choice_dynamics, choice_process;
    choice_dynamics = std::stoi(argv[1]);
    choice_process = std::stoi(argv[2]);

    if (choice_dynamics >= 3 || choice_dynamics <= 0) {
        std::cerr << "Out of range! (1: non-resistance, 2: resistance)" << std::endl;
        return(-1);
    }

    if (choice_process >= 3 || choice_process <= 0) {
        std::cerr << "Out of range! (1: vector field, 2: numerical integration)" << std::endl;
        return(-1);
    }

    if (choice_process == 1) {
        /* 
            Vector field of Dynamics system
            execute: ./a.out 1 1 > nonresistane or ./a.out 2 1 > resistance
            gnuplot: (nonresistance)
                set xrange [-5.5:5.5]
                set yrange [-5.5:5.5]
                set xlabel "x"
                set ylabel "v"
                plot "./nonresistance" with vector
        */
        Dynamics n = Dynamics();
        if (choice_dynamics == 1) {
            n.vector_field(_f0, _f1);
        }
        else {
            n.vector_field(_g0, _g1);
        }
    }
    else {
        /*
            Runge-Kutta
            execute: ./a.out 1 2 > flow_nonresistance
            gnuplot:
                set xrange [-5:5]
                set yrange [-5:5]
                set xlabel "x"
                set ylabel "v"
                plot "./flow_nonresistance" with line
        */
        if (choice_dynamics == 1) {
            for (int k = 0; k < set_size; k++) {
                RungeKutta rk = RungeKutta(f, 0, maxt, InitialValuesset[k], MAXITER, dim);
                for (int i = 0; i < MAXITER; ++i) {
                    std::cout << rk.getValue(i, 0) << " " << rk.getValue(i, 1) << std::endl;
                }
                std::cout << std::endl;
                std::cout << std::endl;
            }
        }
        else {
            for (int k = 0; k < set_size; k++) {
                RungeKutta rk = RungeKutta(g, 0, maxt, InitialValuesset[k], MAXITER, dim);
                for (int i = 0; i < MAXITER; ++i) {
                    std::cout << rk.getValue(i, 0) << " " << rk.getValue(i, 1) << std::endl;
                }
                std::cout << std::endl;
                std::cout << std::endl;
            }
        }
    }
}