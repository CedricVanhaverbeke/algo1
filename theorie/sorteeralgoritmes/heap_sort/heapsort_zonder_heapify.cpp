#include <iostream>
#include "stijgendeHeap.cpp"

template <class T>
void heap_sort(vector<T> &vector) {
    // Maken van de heap adhv de vector
    Heap heap(vector);
    int i = 0;
    while (!heap.isEmpty()) {
        vector[vector.size() - i - 1] = heap.verwijderGrootsteElement();
        i++;
    }
}

template <class T>
void print_vector(vector<T> &vector) {
    for (auto t : vector) {
        cout << t << " ";
    }
    cout << endl;
}

int main() {
    vector<int> v = {5, 10, 3, 7, 8, 9, 69, 73, 54, 29};
    print_vector(v);
    heap_sort(v);
    print_vector(v);
    return 0;
}