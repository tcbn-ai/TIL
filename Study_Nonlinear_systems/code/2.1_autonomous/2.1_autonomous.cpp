/* geometrics.cpp */
/* vector field */
/* dx/dt = y, dy/dt = -x */
/* compile: g++ 2.1_autonomous.cpp */
/* generate data: ./a.out > autonomous */
/* gnuplot: plot "./autonomous" with vector */
#include <iostream>
#include <cmath>

class Vectorfield {
    constexpr static double beginx = -2.5, endx = 2.5, beginy = -2.5, endy = 2.5, step = 0.2;
    public:
        double funcx(double x, double y);  /* dx/dt */
        double funcy(double x, double y);  /* dy/dt */
        double norm(double x, double y);   /* calculate norm */
        void loop();
};

double Vectorfield::funcx(double x, double y) {
    return -y;  /* dx/dt */
}

double Vectorfield::funcy(double x, double y) {
    return x;   /* dy/dt */
}

double Vectorfield::norm(double x, double y) {
    double norm = sqrt(pow(Vectorfield::funcx(x, y), 2) + pow(Vectorfield::funcy(x, y), 2));
    return norm;
}

void Vectorfield::loop() {
    double xl, yl, dx, dy, nrm;
    for(xl = Vectorfield::beginx; xl <= Vectorfield::endx; xl = xl + Vectorfield::step) {
        for (yl = Vectorfield::beginy; yl <= Vectorfield::endy; yl = yl + Vectorfield::step) {
            nrm = Vectorfield::norm(xl, yl);
            dx = Vectorfield::funcx(xl, yl) / (1.0 + nrm) * Vectorfield::step;
            dy = Vectorfield::funcy(xl, yl) / (1.0 + nrm) * Vectorfield::step;
            /* 空白を入れたくてこのようにしたけど，もっといい方法あるはず */
            std::cout << xl << " " << yl << " " << dx << " " << dy << std::endl;
        }
    }
}



int main() {
    Vectorfield v;
    v.loop();
}
