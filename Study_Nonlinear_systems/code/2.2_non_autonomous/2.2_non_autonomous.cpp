/* g(t, x) = xt */
/* compile: g++ 2.2_non_autonomous.cpp */
/* generate data: ./a.out > nonautonomous */
/* gnuplot: plot "./nonautonomous" with vector */
#include <iostream>
#include <cmath>

class Nonautonomous {
    constexpr static double begint = 0.0, endt = 5.0, beginx = -2.5, endx = 2.5, step = 0.2;
    public:
        double funcg(double t, double x);   /* dx/dt */
        double norm(double t, double x);    /* calculate norm */
        void loop();
};

double Nonautonomous::funcg(double t, double x) {
    return x*t;
}

double Nonautonomous::norm(double t, double x) {
    double norm = sqrt(pow(1.0, 2) + pow(Nonautonomous::funcg(t, x), 2));
    return norm;
}

void Nonautonomous::loop() {
    double tl, xl, dt, dx, nrm;
    for(tl = Nonautonomous::begint; tl <= Nonautonomous::endt; tl += Nonautonomous::step) {
        for(xl = Nonautonomous::beginx; xl <= Nonautonomous::endx; xl += Nonautonomous::step) {
            nrm = Nonautonomous::norm(tl, xl);
            dt = 1.0* Nonautonomous::step * 0.25;
            dx = Nonautonomous::funcg(tl, xl) * Nonautonomous::step * 0.25;
            std::cout << tl << " " << xl << " " << dt << " " << dx << std::endl;
        }
    }
}

int main() {
    Nonautonomous n;
    n.loop();
}