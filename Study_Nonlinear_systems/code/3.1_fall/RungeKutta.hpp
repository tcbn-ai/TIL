#ifndef RungeKutta_hpp
#define RungeKutta_hpp
/*
Reference: https://qiita.com/nmbakfm/items/e81744ff544f3552278f
*/

/* define RungeKutta class */
class RungeKutta {
    float * result;
    int num;
    void calculateNextStep(float (*f[])(float t, float *x), float t0, float *x, float tn, int num); /* RK4th */

    public:
        RungeKutta(){};
        RungeKutta(float (*f[])(float t, float *x), float t0, float tn, float *x, int maxiter, int _num);
        float getValue(int step, int index);
};


/* get value */
inline float RungeKutta::getValue(int step, int index) {
    return result[step*num + index];
}


/* execute Runge-Kutta */
inline RungeKutta::RungeKutta(float (*f[])(float t, float *x), float t0, float tn, float *x, int maxiter, int _num) {
    num = _num;
    result = new float[maxiter*num];
    float h = (tn - t0)/maxiter;
    for (int i = 0; i < maxiter; ++i) {
        calculateNextStep(f, t0, x, t0+h, num);
        for (int j = 0; j < num; ++j) {
            result[i*num + j] = x[j];
            t0 += h;
        }
    }
}

/* Runge-Kutta 4th */
inline void RungeKutta::calculateNextStep(float (*f[])(float t, float *x), float t0, float *x, float tn, int num) {
    float k1[num], k2[num], k3[num], k4[num], tmp[num];
    float h = tn - t0;
    float t = t0;

    for (int j = 0; j < num; j++) {
        k1[j] = (*f[j])(t, x);
        
        tmp[j] = x[j] + h*k1[j]/2;
        k2[j] = (*f[j])(t + h/2, tmp);

        tmp[j] = x[j] + h*k2[j]/2;
        k3[j] = (*f[j])(t + h/2, tmp);

        tmp[j] = x[j] + h*k3[j];
        k4[j] = (*f[j])(t + h, tmp);

        x[j] += (k1[j] + 2*k2[j] + 2*k3[j] + k4[j])*h/6;
    }
}

#endif /* RungeKutta_hpp */