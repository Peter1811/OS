#include <cmath>

float Pi(int K) {
    if (K < 0) return -1;
    float pi = 1.0;
    for (int i = 1; i <= K; i++) {
        pi *= 4 * pow(i, 2) / (4 * pow(i, 2) - 1);
    }
    return pi * 2;
}

float Square(float A, float B) {

    //if (A > B) {
    //  float C = pow(A * A - B * B, 1/2);
    //  return 0.5 * B * C;
    //} else {
    //  float C = pow(B * B - A * A, 1/2);
    //  return 0.5 * A * C;
    // }
   // if ((A < 0) or (B < 0)) return -1;

   // return 0.5 * A * B;
    return 1;

}

