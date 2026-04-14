#include <iostream>

double FastInvSqrt(double x) {
    double xhalf = 0.5f * x;
    long long i = *(long long*)&x;
    i = 0x5FE6EB3BFB58D152 - (i >> 1);
    x = *(double*)&i;
    x = x*(1.5f-(xhalf*x*x));
    return x;
}

int main() {
    double x1, x2;
    double mxdelta = -1;
    for (double x = 0.001; x < 10; x+=0.025) {
        x1 = 1 / std::sqrt(x);
        x2 = FastInvSqrt(x);
        mxdelta = std::max(mxdelta, abs(x1 - x2)/x1);
    } 
    std::cout << "Ответ: " << mxdelta << "\n";
}
