#include <iostream>


template<typename T>
struct Player{
    T payload;
    struct Player<T>* next;
};

template <typename T>
Player<T>* add(const T payload) {
    auto* p = new Player<T>;
    p->next = nullptr;
    p->payload = payload;
    return p;
}
template <typename T>
Player<T>* create_circle(const size_t N, T init_element){
    Player<T>* players = add(size_t(init_element++));
    Player<T>* next = players;
    for (size_t i = 2; i <= N; i++) {
        next->next = add(init_element++);
        next = next->next;
    }
    next->next = players;
    return players;
}
template <typename T>
void pop(Player<T>* p){
    Player<T>* next = p->next;
    p->payload = next->payload;
    p->next = next->next;
    next->next = nullptr;
    delete next;
}
template <typename T>
int find_survivor(const size_t N, const int k, const T& init_element) {
    int count = 1;
    int survivor = 0;

    Player<T>* current_player = create_circle(N, init_element);
    while(current_player->next != current_player) {
        while(count++ != k){
            current_player = current_player->next;
        }
        pop(current_player);
        count = 1;
    }
    survivor = current_player->payload;
    delete current_player;
    return survivor;
}


int main() {
    size_t init_element = 1;
    size_t N = 0;
    int k = 0;

    std:: cin >> N;
    std::cin >> k;

    std::cout << find_survivor(N, k, init_element) << std::endl;
    return 0;
}

