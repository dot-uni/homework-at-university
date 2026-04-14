#include <iostream>


float FastInvSqrt(float x) {
    float xhalf = 0.5f * x;
    int i = *(int*)&x;
    i = 0x5f3759df - (i >> 1);
    x = *(float*)&i;
    x = x*(1.5f-(xhalf*x*x));
    return x;
}


int main() {
    float x1, x2;
    float mxdelta = -1;
    for (float x = 0.001; x < 10; x+=0.025) {
        x1 = 1 / std::sqrt(x);
        x2 = FastInvSqrt(x);
        mxdelta = std::max(mxdelta, abs(x1 - x2)/x1);
    } 
    std::cout << "Ответ: " << mxdelta << "\n";
}