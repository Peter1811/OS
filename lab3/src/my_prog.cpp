#include <iostream>
#include <vector>
#include <pthread.h>
#include <algorithm>

using namespace std;
int *A;

struct my_struct {
    int left;
    int right;
};

void Merge(int first, int last) {
    int* mas = new int[last - first + 1];

    int start = first;
    int middle = (first + last) / 2;
    int final = middle + 1;
    for (int j = first; j <= last; j++) {
        if ((start <= middle) and ((final > last) or ((final <= last) and (A[start] < A[final])))) {
            mas[j] = A[start];
            start ++;
        } else {
            mas[j] = A[final];
            final ++;
        }
    }

    for (int j = first; j <= last; j ++) {
        A[j] = mas[j];
    }

    delete [] mas;
}

void MergeSort(int first, int last) {

    if (first < last) {
        MergeSort(first, (first + last) / 2);
        MergeSort((first + last) / 2 + 1, last);
        Merge(first, last);
    }
}

void* Merge_thread(void* args) {
    auto *arg = (my_struct*) args;
    if (arg->left < arg->right) {
        MergeSort(arg->left, (arg->left + arg->right) / 2);
        MergeSort((arg->left + arg->right) / 2 + 1, arg->right);
        Merge(arg->left, arg->right);
    }
    return arg;
}

int main(int argc, char* argv []) {

    int number_of_threads = stoi(argv[1]);
    cout << "Enter the size of array: ";
    int size_of_array; cin >> size_of_array;
    A = new int[size_of_array];
    cout << "Enter elements of array:" << endl;
    for (int i = 0; i < size_of_array; i++) {
        cin >> A[i];
    }

    if (number_of_threads > size_of_array) 
        number_of_threads = size_of_array;


    int size = size_of_array;
    vector <int> threads(number_of_threads, 0);

    while (size > 0){
        for (int i = 0; i < number_of_threads; i++) {
            if (size == 0) {
                break;
            }
            threads[i] ++;
            size --;
        }
    }

    auto thrs = new pthread_t[number_of_threads];

    // my_struct task_list[number_of_threads];
    auto *task_list = new my_struct[number_of_threads];

    int begin = 0;
    for (int i = 0; i < number_of_threads; begin += threads[i], i++) {
        task_list[i].left = begin;
        task_list[i].right = begin + threads[i] - 1;
    }

    for (int i = 0; i < number_of_threads; i++) {
       pthread_create(&thrs[i], nullptr, Merge_thread, &task_list[i]);
    }

    for (int j = 0; j < number_of_threads; j++) {
        pthread_join(thrs[j], nullptr);
    }

    vector <int> my_array(0);
    for (int i = 0; i < size_of_array; i++) {
        my_array.push_back(A[i]);
    }
    sort(my_array.begin(), my_array.end());

    cout << "Sorted array: ";
    for (auto i: my_array) {
        cout << i << " ";
    }

    delete [] task_list;
    delete [] thrs;
    return 0;
}
