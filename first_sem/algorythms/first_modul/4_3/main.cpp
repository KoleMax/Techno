#include <iostream>

#define TRAINSCHEDULELEN 2


template <typename T>
class Heap{
public:
    explicit Heap(size_t size, bool (* compare_func)(T , T ));
    ~Heap();
    void insert(T item);
    T pop_max();
    T peek_max() const;
    size_t get_heap_size() const;

private:
    T* array;
    size_t heap_size;
    bool (*compare)(T , T );
    void sift_down(size_t index);
    void sift_up(size_t index);

};

template <typename T>
size_t impasses_num(T** trains_schedule, size_t trains_num, bool (*compare)(T a, T b));
template <typename T>
bool compare(T a, T b);
template <typename T>
T** get_schedule(size_t n);

int main() {
    size_t n;
    std::cin >> n;
    int** trains_schedule = get_schedule<int>(n);

    std::cout << impasses_num(trains_schedule, n, &compare) << std::endl;

    for (size_t i = 0; i < n; i++) {
        delete trains_schedule[i];
    }
    delete[] trains_schedule;
    return 0;
}

template <typename T>
size_t impasses_num(T** trains_schedule, const size_t trains_num, bool (*compare)(T , T )){

    Heap<T> heap = Heap<T>(trains_num, compare);
    T arrival_time;
    T departure_time;
    size_t max_heap_size = 0;

    for(size_t i = 0; i < trains_num; i++) {

        arrival_time = trains_schedule[i][0];
        departure_time = trains_schedule[i][1];
        heap.insert(departure_time);

        while (heap.get_heap_size() > 0 && heap.peek_max() < arrival_time){
            heap.pop_max();
        }

        if (max_heap_size < heap.get_heap_size()){
            max_heap_size = heap.get_heap_size();
        }
    }
    return max_heap_size;
}
template <typename T>
bool compare(const T a,  const T b){
    return a < b;
}
template <typename T>
T** get_schedule(const size_t n){
    auto** trains_schedule = new T*[n];

    T arrival_time = 0;
    T departure_time = 0;
    for (size_t i = 0; i < n; i++){
        trains_schedule[i] = new T[TRAINSCHEDULELEN];
        std::cin >> arrival_time;
        std::cin >> departure_time;
        trains_schedule[i][0] = arrival_time;
        trains_schedule[i][1] = departure_time;
    }
    return trains_schedule;
}

template <typename T>
Heap<T>::Heap(const size_t size, bool (* compare_func)(T , T )){
    array = new T[size];
    compare = compare_func;
    heap_size = 0;
}
template <typename T>
Heap<T>::~Heap(){
    delete[] array;
}

template <typename T>
void Heap<T>::insert(const T item){
    array[heap_size] = item;
    if (heap_size > 0) {
        sift_up(heap_size++);
    } else {
        heap_size++;
    }
}
template <typename T>
T Heap<T>::pop_max(){
    T result = array[0];
    array[0] = array[--heap_size];
    sift_down(0);
    return result;
}
template <typename T>
T Heap<T>::peek_max() const{
    return array[0];
}
template <typename T>
size_t Heap<T>::get_heap_size() const{
    return heap_size;
}

template <typename T>
void Heap<T>::sift_down(const size_t index){

    size_t left_child = index * 2 + 1;
    size_t right_child = index * 2 + 2;
    size_t highest_priority = index;

    if (heap_size > left_child && (* compare)(array[left_child], array[index])){
        highest_priority = left_child;
    }
    if (heap_size > right_child && (*compare)(array[right_child], array[highest_priority])){
        highest_priority = right_child;
    }
    if (highest_priority != index){
        std::swap(array[highest_priority], array[index]);
        sift_down(highest_priority);
    }
}
template <typename T>
void Heap<T>::sift_up(size_t index){
    size_t parent = (index - 1) / 2;
    while(index > 0){
        if ((* compare)(array[parent], array[index])){
            return;
        }
        std::swap(array[index], array[parent]);
        index = parent;
        parent = (index - 1) / 2;
    }
}
