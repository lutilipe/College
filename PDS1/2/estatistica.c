#include "estatistica.h"
#include <math.h>

float cauchy(float x) {
    return 1 / (M_PI * (1 + pow(x, 2)));
}

float getZInGumbelDistribution(float x, float mi, float beta) {
    return (x - mi) / beta;
}

float gumbel(float x, float mi, float beta) {
    float z = getZInGumbelDistribution(x, mi, beta);
    return (1 / beta) * exp(-(z + exp(-z)));
}

float laplace(float x, float mi, float beta) {
    return (1 / (2 * beta)) * exp(-fabs(x - mi) / beta);
}