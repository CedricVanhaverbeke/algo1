#include <iostream>
#include "stijgendeHeap.cpp"

int main() {
    vector<int> v = {5, 10, 3, 7, 8, 9, 69, 73, 54, 29};
    Heap heap(v);

    cout << heap << endl;
    return 0;
}