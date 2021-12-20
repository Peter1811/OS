#include <iostream>
float Pi (int x);
float Square (float A, float B);
float Square(int A, int B);

int main () {
    int choice;
    std::cout << "Enter the number of function: 1 - pi, 2 - square" << std::endl;
    while (std::cin >> choice) {
        
        
        if (choice == 1) {
            std::cout << "The calculation of Pi" << std::endl;
            int x;
            std::cin >> x;
            float pi = Pi(x);
            if (pi == -1) {
                std::cout << "Wrong input" << std::endl;
                exit(-1);
            }
            std::cout << pi << std::endl;
        } else if (choice == 2) {
            std::cout << "The calculation of square" << std::endl;
            float a, b;
            std::cin >> a >> b;
            float s = Square((int)a, (int)b);
            if (s == -1) {
                std::cout << "Wrong input" << std::endl;
                exit(-1);
            }
            std::cout << s << std::endl;
        } else {
            std::cout << "No such choice" << std::endl;
            exit(-1);
        }
        std::cout << "Enter the number of function: 1 - pi, 2 - square" << std::endl;
    }

    return 0;
}