/*Дан массив неотрицательных целых 64-битных чисел. Количество чисел не больше 1000000. Отсортировать массив методом поразрядной сортировки LSD по байтам.*/


#include <iostream>
#define BYTEDIFFERENTVALUES 256

template <typename T>
unsigned int* count_bytes(const T* arr, size_t size, int byte_to_extract);
template <typename T>
T* rearrange(const T* arr, size_t size, int byte_to_extract, unsigned int* bytes_numbers);
template <typename T>
T* lsd(T* arr, size_t size, int bytes_left){
    if (bytes_left == 0)
        return arr;

    int byte_to_extract = (8 - bytes_left);
    auto* bytes_numbers = count_bytes(arr, size, byte_to_extract);
    auto* result = rearrange(arr, size, byte_to_extract, bytes_numbers);

    delete[] arr;
    return lsd(result, size, bytes_left - 1);
}


int main() {

    size_t N = 0;
    std::cin >> N;

    auto* arr = new unsigned long long [N];
    unsigned long long el = 0;
    for(size_t i = 0; i < N; i++) {
        std::cin >> el;
        arr[i] = el;
    }

    arr = lsd(arr, N, sizeof(unsigned long long));
    for(size_t i = 0; i < N; i++)
        std::cout << arr[i] << " ";

    return 0;
}


template <typename T>
unsigned int* count_bytes(const T* arr, size_t size, int byte_to_extract){

    auto* bytes_numbers = new unsigned int[256];
    for(size_t i = 0; i < 256; i++) {
        bytes_numbers[i] = 0;
    }

    for(size_t i = 0; i < size; i++) {
        unsigned char byte = (arr[i] >> (8 * byte_to_extract)) & 0xFF;
        bytes_numbers[byte]++;
    }

    return bytes_numbers;
}
template <typename T>
T* rearrange(const T* arr, const size_t size, const int byte_to_extract, unsigned int* bytes_numbers){

    auto* result = new T[size];
    size_t index = 0;
    size_t result_index = 0;

    for(size_t i = 0; i < BYTEDIFFERENTVALUES; i++) {
        index = 0;
        while(bytes_numbers[i]){
            unsigned char byte = (arr[index] >> (8 * byte_to_extract)) & 0xFF;

            if(byte == i){
                result[result_index++] = arr[index++];
                bytes_numbers[i]--;
            } else {
                index++;
            }

        }
    }
    return result;
}
