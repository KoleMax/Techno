/*Даны неотрицательные целые числа n, k и массив целых чисел из диапазона [0..109] размера n.
Требуется найти k-ю порядковую статистику. т.е. напечатать число, которое бы стояло на позиции с индексом k ∈[0..n-1] в отсортированном массиве.
Напишите нерекурсивный алгоритм.
Требования к дополнительной памяти: O(n).
Требуемое среднее время работы: O(n).
Функцию Partition следует реализовывать методом прохода двумя итераторами в одном направлении.
Описание для случая прохода от начала массива к концу:
Выбирается опорный элемент.
Опорный элемент меняется с последним элементом массива.
Во время работы Partition в начале массива содержатся элементы, не бОльшие опорного. Затем располагаются элементы, строго бОльшие опорного. В конце массива лежат нерассмотренные элементы. 
Последним элементом лежит опорный.
Итератор (индекс) i указывает на начало группы элементов, строго бОльших опорного.
Итератор j больше i, итератор j указывает на первый нерассмотренный элемент.
Шаг алгоритма. Рассматривается элемент, на который указывает j. Если он больше опорного, то сдвигаем j. Если он не больше опорного, то меняем a[i] и a[j] местами, сдвигаем i и сдвигаем j.
В конце работы алгоритма меняем опорный и элемент, на который указывает итератор i.*/


#include <iostream>
#include <unistd.h>

template <typename T>
size_t choose_pivot(const T* arr, size_t first_index, size_t last_index);
template <typename T>
size_t partition(T* arr, size_t first_index, size_t last_index);
template <typename T>
int quick_search(T* arr, const size_t arr_size, const size_t k) {

    size_t first_index = 0;
    size_t last_index = arr_size - 1;
    size_t pivot_pos = partition(arr, first_index, last_index);

    while(pivot_pos != k) {
        if(pivot_pos > k){
            last_index = pivot_pos;
            pivot_pos = partition(arr, first_index, last_index);
        } else {
            first_index = pivot_pos + 1;
            pivot_pos = partition(arr, first_index, last_index);
        }
    }

    return arr[pivot_pos];
}


int main(){

    size_t n = 0;
    size_t pos = 0;
    std::cin >> n;
    std::cin >> pos;

    int* arr = new int[n];
    int el = 0;

    for(size_t i = 0; i < n; i++){
        std::cin >> el;
        arr[i] = el;
    }

    std::cout << quick_search(arr, n, pos) << std::endl;
    delete[] arr;

    return 0;
}

template <typename T>
size_t choose_pivot(const T* arr, const size_t first_index, const size_t last_index){
    size_t middle_index = (last_index + first_index) / 2;
    return arr[middle_index] > arr[last_index]
           ? arr[first_index] > arr[middle_index]
             ? middle_index
             : arr[first_index] > arr[last_index]
               ? first_index
               : last_index
           : arr[first_index] < arr[middle_index]
             ? middle_index
             : arr[first_index] > arr[last_index]
               ? last_index : first_index;
}
template <typename T>
size_t partition(T* arr, const size_t first_index, const size_t last_index){

    size_t pivot_index = choose_pivot(arr, first_index, last_index);
    T pivot = arr[pivot_index];
    std::swap(arr[last_index], arr[pivot_index]);

    size_t i = last_index;
    size_t j = last_index;
    while(i > 0) {
        i--;
        if(arr[i] > pivot)
            std::swap(arr[i], arr[--j]);
    }

    std::swap(arr[last_index], arr[j]);
    return j;
}
