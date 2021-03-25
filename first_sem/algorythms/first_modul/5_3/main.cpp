/*На числовой прямой окрасили N отрезков.
Известны координаты левого и правого концов каждого отрезка [Li, Ri]. Найти длину окрашенной части числовой прямой.
N ≤ 10000. Li, Ri — целые числа в диапазоне [0, 109].
Формат ввода
В первой строке записано количество отрезков.
В каждой последующей строке через пробел записаны координаты левого и правого концов отрезка.
Формат вывода
Выведите целое число — длину окрашенной части.*/


#include <iostream>

template <typename T>
struct Segment{
    T start;
    T ending;
};
template <typename T>
bool compare(Segment<T>, Segment<T>);
template <typename T>
Segment<T>* merge_sort(Segment<T>* segments, Segment<T>* buffer, size_t first_index, size_t last_index, bool (* compare)(Segment<T>, Segment<T>));
template <typename T>
size_t find_segment_len(Segment<T>* segments, size_t size, bool (* compare)(Segment<T>, Segment<T>));


int main() {

    size_t N = 0;
    std::cin >> N;

    auto* a = new Segment<size_t >[N];
    size_t start = 0;
    size_t ending = 0;
    for(size_t i = 0; i < N; i++){
        std::cin >> start;
        std::cin >> ending;
        a[i] = Segment<size_t >{start, ending};
    }

    std::cout << find_segment_len(a, N, compare) << std::endl;
    delete[] a;

    return 0;
}


template <typename T>
bool compare(Segment<T> a, Segment<T> b){
    return a.start > b.start;
}
template <typename T>
Segment<T>* merge_sort(Segment<T>* segments, Segment<T>* buffer, size_t first_index, size_t last_index, bool (* compare)(Segment<T>, Segment<T>)){
    if(first_index == last_index) {
        buffer[first_index] = segments[first_index];
        return buffer;
    }

    size_t middle_index = (last_index + first_index) / 2;
    merge_sort(segments, buffer, first_index, middle_index, compare);
    merge_sort(segments, buffer, middle_index + 1, last_index, compare);

    size_t i = first_index;
    size_t j = middle_index + 1;
    size_t k =  first_index;

    while(i <= middle_index and j <= last_index) {
        if(compare(buffer[i], buffer[j])){
            segments[k++] = buffer[j++];
        } else {
            segments[k++] = buffer[i++];
        }
    }
    while(i <= middle_index){
        segments[k++] = buffer[i++];
    }
    while(j <= last_index){
        segments[k++] = buffer[j++];
    }

    for(size_t m = first_index; m <= last_index; m++)
        buffer[m] = segments[m];
    return buffer;
}
template <typename T>
size_t find_segment_len(Segment<T>* segments, size_t size, bool (* compare)(Segment<T>, Segment<T>)){

    size_t segment_sum_length = 0;
    Segment<T>* result = merge_sort(segments, new Segment<T>[size], 0, size - 1, compare);
    Segment<T> prev_farthest_segment = result[0];
    segment_sum_length += prev_farthest_segment.ending - prev_farthest_segment.start;
    Segment<T> current_segment;

    for(size_t i = 1; i < size; i++){
        current_segment = result[i];
        if(current_segment.ending <= prev_farthest_segment.ending)
            continue;
        if(current_segment.start < prev_farthest_segment.ending)
            segment_sum_length += (current_segment.ending - prev_farthest_segment.ending);
        else
            segment_sum_length += (current_segment.ending - current_segment.start);
        prev_farthest_segment = current_segment;
    }

    delete result;
    return segment_sum_length;
}