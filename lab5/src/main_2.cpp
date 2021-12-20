#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <dlfcn.h>

int main () {
    void* handle = NULL; //адрес, в будущем нужный нам для получения доступа к библиотеке
    float (*Pi)(int x); //объявление указателей на функции
    float (*Square)(int A, int B);
    float (*Square1)(float A, float B); // объявление указателей на функции
    const char* lib_array[] = {"libd1.so", "libd2.so"};
    int start_library;
    int current = start_library - 1;
    std:: cout << "Enter start library: " << std:: endl;
    std:: cout << '\t' << "1 - first realization" << std:: endl;
    std:: cout << '\t' << "2 - second realization" << std:: endl;
    std:: cin >> start_library;
    if (start_library != 1 && start_library != 2) {
        std:: cout << "Wrong input" << std:: endl;
        exit(-1);
    }
    handle = dlopen(lib_array[current], RTLD_LAZY); //rtld lazy выполняется поиск только тех символов, на которые есть ссылки из кода
    if (!handle) {
        std:: cout << "An error while opening library" << std:: endl;
        exit(EXIT_FAILURE);
    }
    Pi = (float(*)(int))dlsym(handle, "Pi"); //возвращаем адрес функции из памяти библиотеки
    Square1 = (float(*)(float, float))dlsym(handle, "Square"); //dlsym присваивает указателю на функцию, объявленному в начале, ее адрес в библиотеке
    Square = (float(*)(int, int))dlsym(handle, "Square");
    int command;
    std:: cout << '\t' << "0 - change the contract" << std:: endl;
    std:: cout << '\t' << "1 - calculate the pi " << std:: endl;
    std:: cout << '\t' << "2 - calculate the square " << std:: endl; 
    while (std::cin >> command){
        if (command == 0) {
            dlclose(handle); //освобождает указатель на библиотеку и программа перестает ей пользоваться
            current = 1 - current;
            handle = dlopen(lib_array[current], RTLD_LAZY);
            if (!handle) {
                std:: cout << "An error while opening library has been detected" << std:: endl;
                exit(EXIT_FAILURE);
            }
            Pi = (float(*)(int))dlsym(handle, "Pi");
            Square = (float(*)(int, int))dlsym(handle, "Square"); 
            std:: cout << "You have changed contracts!" << std:: endl;
        }
        else if (command == 1) {
            int x;
            std:: cin >> x;
            float exp = Pi(x);
            if (exp == -1) {
                std:: cout << "Wrong input" << std:: endl;
                dlclose(handle);
                exit(-1);
            }
            else {
                std:: cout << "Result: " << exp << std:: endl;
            }
        }
        else if (command == 2) {
            float A, B, square;
            std:: cin >> A >> B;
            square = Square(A, B);
            if (square == -1) {
                std:: cout << "Wrong input" << std:: endl;
                dlclose(handle);
                exit(-1);
            }
            else {
                std:: cout << "Result: " << square << std:: endl;
            }
        }
        else {
            std:: cout << "Wrong input2" << std:: endl;
            dlclose(handle);
            exit(-1);
        }
    }   
    
    dlclose(handle);
    return 0;
}