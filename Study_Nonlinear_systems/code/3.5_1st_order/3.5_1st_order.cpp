#include <iostream>
#include <cmath>
#include <bits/stdc++.h>
#include "../RungeKutta.hpp"
#define MAXITER 1000
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
            dx = f_0(0, x) * Dynamics::step * 0.25;
            dv = f_1(0, x) * Dynamics::step * 0.25;
            std::cout << xl << " " << vl << " " << dx << " " << dv << std::endl;
        }
    }
}

/* dynamics */
/* 1. Separation variables */
float _f10(float t, float *x) {
    return (1 - x[1])*x[0];
}

float _f11(float t, float *x) {
    return -(1 - x[0])*x[1];
}

/* 2. Homogeneous */
float _f20(float t, float *x) {
    return x[0]*(x[0] - x[1]);
}

float _f21(float t, float *x) {
    return (-1)*pow(x[1], 2);
}

/* 3. Linear */
float _f30(float t, float *x) {
    return cos(x[0]);
}

float _f31(float t, float *x) {
    return pow(cos(x[0]), 2) + x[1]*sin(x[0]);
}

/* 4. Bernoulli */
float _f40(float t, float *x) {
    return x[0];
}

float _f41(float t, float *x) {
    return (-1)*x[1] + pow(x[0], 3)*pow(x[1], 3);
}

/* 5. exact */
float _f50(float t, float *x) {
    return pow(x[1], 3) + pow(x[0], 2) + x[0];
}

float _f51(float t, float *x) {
    return (-1)*pow(x[0], 3) - 2*x[0]*x[1] - x[1];
}

/* execute Runge Kutta */
void execute_rk (int dimension, float (*f[])(float t, float *x), float maxtime, float init[]) {
    RungeKutta rk = RungeKutta(f, 0, maxtime, init, MAXITER, dimension);
    for (int i = 0; i < MAXITER; ++i) {
        std::cout << rk.getValue(i, 0) << " " << rk.getValue(i, 1) << std::endl;
    }
}

int main(int argc, char *argv[]) {
    /* output error message */
    if (argc != 3) {
        std::cerr << "Out of range! Please input 2 values." << std::endl;
        return(-1);
    }

    int choice_dynamics, choice_process;
    choice_dynamics = std::stoi(argv[1]);
    choice_process = std::stoi(argv[2]);

    if (choice_dynamics >= 6 || choice_dynamics <= 0) {
        std::cerr << "Out of range! (1: Separation variables, 2: Homogeneous, 3: Linear, 4: Berinoulli, 5: exact)" << std::endl;
        return(-1);
    }

    if (choice_process >= 3 || choice_process <= 0) {
        std::cerr << "Out of range! (1: vector field, 2: numerical integration)" << std::endl;
        return(-1);
    }

    /* define function */
    float (*f1[2])(float, float*);
    f1[0] = _f10;
    f1[1] = _f11;

    float (*f2[2])(float, float*);
    f2[0] = _f20;
    f2[1] = _f21;

    float (*f3[2])(float, float*);
    f3[0] = _f30;
    f3[1] = _f31;

    float (*f4[2])(float, float*);
    f4[0] = _f40;
    f4[1] = _f41;

    float (*f5[2])(float, float*);
    f5[0] = _f50;
    f5[1] = _f51;

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
        {-5.0, -4.0},
        {-5.0, -3.0},
        {-5.0, -2.0},
        {-5.0, -1.0},
        {-5.0, 1.0},
        {-4.0, -5.0},
        {-3.0, -5.0},
        {-2.0, -5.0},
        {-1.0, -5.0},
        {0.1, -0.1},
        {0.2, -0.2},
        {0.0, -5.0},
        {0.1, -3.0},
        {0.1, -2.0},
        {0.1, -1.0},
        {0.1, -0.5},
        {0.5, 0.5},
        {1.0, 1.0},
        {1.5, 1.5},
        {2.0, 2.0},
        {2.5, 2.5},
        {3.0, 3.0},
        {3.5, 3.5},
        {4.0, 4.0},
    };

    /* Parameters */
    int set_size = ARRAY_LENGTH(InitialValuesset);
    float maxt = 20.0;
    int dim = 2;

    if (choice_process == 1) {
        /* 
            Vector field of Dynamical system
            execute: ./a.out 1 1 > vector_field_1
            gnuplot: (nonresistance)
                set xrange [-5.5:5.5]
                set yrange [-5.5:5.5]
                set xlabel "x"
                set ylabel "y"
                plot "./vector_field_1" with vector
        */
        Dynamics n = Dynamics();
        if (choice_dynamics == 1) {
            n.vector_field(_f10, _f11);
        }
        else if (choice_dynamics == 2) {
            n.vector_field(_f20, _f21);
        }
        else if (choice_dynamics == 3) {
            n.vector_field(_f30, _f31);
        }
        else if (choice_dynamics == 4) {
            n.vector_field(_f40, _f41);
        }
        else {
            n.vector_field(_f50, _f51);
        }        
    }
    else {
        /*
            Runge-Kutta
            execute: ./a.out 1 2 > flow_1
            gnuplot:
                set xrange [-5:5]
                set yrange [-5:5]
                set xlabel "x"
                set ylabel "y"
                plot "./flow_1" with line
        */
        if (choice_dynamics == 1) {
            for (int k = 0; k < set_size; k++) {
                execute_rk(dim, f1, maxt, InitialValuesset[k]);
                std::cout << std::endl;
                std::cout << std::endl;
            }
        }
        else if (choice_dynamics == 2) {
            for (int k = 0; k < set_size; k++) {
                execute_rk(dim, f2, maxt, InitialValuesset[k]);
                std::cout << std::endl;
                std::cout << std::endl;
            }
        }
        else if (choice_dynamics == 3) {
            for (int k = 0; k < set_size; k++) {
                execute_rk(dim, f3, maxt, InitialValuesset[k]);
                std::cout << std::endl;
                std::cout << std::endl;
            }
        }
        else if (choice_dynamics == 4) {
            for (int k = 0; k < set_size; k++) {
                execute_rk(dim, f4, maxt, InitialValuesset[k]);
                std::cout << std::endl;
                std::cout << std::endl;
            }
        }
        else {
            for (int k = 0; k < set_size; k++) {
                execute_rk(dim, f5, maxt, InitialValuesset[k]);
                std::cout << std::endl;
                std::cout << std::endl;
            }
        }
    }
}