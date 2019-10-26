#include <iostream>


template <typename T>
size_t find_k(const T* A, size_t a_size, T element){
    size_t k = 0;
    while(k < a_size){
        if(A[k] > element) {
            return k;
        }
        if(k) {
            k *= 2;
        } else {
            k += 1;
        }
    }
    return k;
}
template <typename T>
size_t binary_search(const T* A, size_t k, T element){
    size_t lower_border = 0;
    size_t upper_border = k;
    size_t middle = 0;
    while(lower_border < upper_border){
        middle = (lower_border + upper_border) / 2;
        if(A[middle] >= element){
            upper_border = middle;
        } else {
            lower_border = middle + 1;
        }
    }
    return upper_border;
}
template <typename T>
T* next_item(const T* A, const T* B, const size_t a_size, const size_t b_size){
    T* C = new T[b_size];
    T current_element = 0;
    size_t k = 0;
    for(size_t i = 0; i < b_size; i++) {
        current_element = B[i];
        k = find_k(A, a_size, current_element);
        if(k >= a_size){
            k = a_size;
        }
        C[i] = binary_search(A, k, current_element);
    }
    return C;
}


int main() {
    size_t size_a = 0;
    size_t size_b = 0;

    std::cin >> size_a;
    std::cin >> size_b;

    auto* A = new int[size_a];
    auto* B = new int[size_b];

    int element = 0;
    for(size_t i = 0; i < size_a; i++){
        std::cin >> element;
        A[i] = element;
    }
    for(size_t i = 0; i < size_b; i++){
        std::cin >> element;
        B[i] = element;
    }

    auto* C = next_item(A, B, size_a, size_b);
    for(size_t i = 0; i < size_b; i++){
        std::cout << C[i] << ' ' << std::endl;
    }
    std::cout << std::endl;
    delete[] A;
    delete[] B;
    delete[] C;
    return 0;
}

