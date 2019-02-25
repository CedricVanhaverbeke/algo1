#include <iostream>
#include "stijgendeHeap.cpp"

int main() {
    Heap<int> heap;
    cout << heap << endl;
    cout << "Element toevoegen aan de heap" << endl;

    heap.voegToe(5);
    heap.voegToe(10);
    heap.voegToe(3);
    heap.voegToe(7);
    heap.voegToe(8);
    heap.voegToe(9);
    heap.voegToe(69);
    heap.voegToe(73);
    heap.voegToe(54);
    heap.voegToe(29);

    

    cout << heap << endl;
}