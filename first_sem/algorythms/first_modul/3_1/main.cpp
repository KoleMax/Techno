#include <iostream>

#define MINBUFFERSIZE 10
#define POPFRONT 2
#define PUSHBACK 3


template <typename T>
class Queue{
public:
    explicit Queue(size_t size);
    ~Queue();

    void push_back(T el);
    T pop_front();
    void print_queue() const;

private:
    T* arr;
    size_t buffer_size;
    size_t min_buffer_size;
    size_t queue_size;
    size_t head;
    size_t tail;

    void extend_if_needed();
    void shrink_if_needed();
    void resize(size_t new_size);
};
bool check(size_t N);


int main() {
    int N = 0;
    std::cin >> N;
    if (check(N))
        std::cout << "YES" << std::endl;
    else
        std::cout << "NO" << std::endl;
    return 0;
}


bool check(size_t N) {
    int a = 0;
    int b = 0;
    Queue<int> q = Queue<int>(MINBUFFERSIZE);
    while(N--){
        std::cin >> a;
        std::cin >> b;
        switch(a){
            case POPFRONT:
                if (q.pop_front() != b)
                    return false;
                break;
            case PUSHBACK:
                q.push_back(b);
                break;
            default:
                return false;
        }
    }
    return true;
}

template <typename T>
Queue<T>::Queue(size_t size){
    buffer_size = size;
    min_buffer_size = MINBUFFERSIZE;
    queue_size = 0;
    arr = new T[size];
    head = size/2;
    tail = size/2;
}
template <typename T>
Queue<T>::~Queue() {
    delete[] arr;
}

template <typename T>
void Queue<T>::push_back(const T el){
    arr[tail] = el;
    if(tail == 0) {
        tail = buffer_size;
    }
    tail--;
    queue_size++;
    extend_if_needed();
}
template <typename T>
T Queue<T>::pop_front(){
    if (head  == tail and !queue_size) {
        return -1;
    }
    T result = arr[head];
    queue_size--;
    if (head == 0) {
        head = buffer_size;
    }
    head--;
    shrink_if_needed();
    return result;
}
template <typename T>
void Queue<T>::print_queue() const{
    if(head >= tail){
        for (size_t i = 0; i <= tail; i++){
            printf("_\t");
        }
        for (size_t i = tail+1; i <= head; i++){
            printf("%d\t", arr[i]);
        }
        for (size_t i = head+1; i < buffer_size; i++){
            printf("_\t");
        }
    } else {
        for (size_t i = 0; i <= head; i++){
            printf("%d\t", arr[i]);
        }
        for (size_t i = head+1; i <=tail; i++){
            printf("_\t");
        }
        for (size_t i = tail+1; i < buffer_size; i++){
            printf("%d\t", arr[i]);
        }
    }
    printf("\n");
    printf("queue_size: %d\n", queue_size);
    printf("buffer_size: %d\n", buffer_size);
    printf("tail: %d\n", tail);
    printf("head: %d\n", head);
}

template <typename T>
void Queue<T>::extend_if_needed(){
    if(queue_size != buffer_size)
        return;
    resize(buffer_size*2);
}
template <typename T>
void Queue<T>::shrink_if_needed(){
    if(queue_size > buffer_size/4 or buffer_size/2 < min_buffer_size)
        return;
    resize(buffer_size/2);
}
template <typename T>
void Queue<T>::resize(const size_t new_size){

    int* new_arr = new int[new_size];
    size_t index_copy_to = new_size / 4;

    size_t new_tail = index_copy_to - 1;
    if (index_copy_to  == 0)
        new_tail = new_size - 1;

    size_t i = tail + 1;
    if (tail == buffer_size - 1){
        i = 0;
    }

    while(i != head) {
        new_arr[index_copy_to++] = arr[i++];
        if (i >= buffer_size) {
            i = 0;
        }
    }

    new_arr[index_copy_to] = arr[head];
    delete[] arr;
    arr = new_arr;
    buffer_size = new_size;
    tail = new_tail;
    head = index_copy_to;
}