#include <cmath>

// extern "C" float Pi (int K);
// extern "C" float Square (float A, float B);

float Pi(int K) {
    
    if (K < 0) return -1;
    float pi = 0;
    for (int i = 0; i < K; i++) {
        pi += 4 * pow(-1, i)/(2 * i + 1);
    }
    return pi;

}

float Square(float A, float B) {
    if ((A < 0) or (B < 0)) return -1;
    return A * B;
}

float Square(int A, int B) {
    // if ((A < 0) or (B < 0)) return -1;
    return 2;
}

