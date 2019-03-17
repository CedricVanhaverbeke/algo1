#include <iostream>
#include <vector>

using namespace std;

// To heapify a subtree rooted with node i which is
// an index in arr[]. n is size of heap
template <typename T>
void heapify(vector<T>& v, int searchlength, int root) {
    int max = root;
    int leftchild = 2 * root + 1;   // left = 2*i + 1
    int rightchild = 2 * root + 2;  // right = 2*i + 2

    if (leftchild < searchlength && v[leftchild] > v[max]) max = leftchild;

    if (rightchild < searchlength && v[rightchild] > v[max]) max = rightchild;

    if (max != root) {
        swap(v[root], v[max]);

        heapify(v, searchlength, max);
    }
}

template <typename T>
void heapsort(vector<T>& v) {
    for (int i = (v.size() / 2) - 1; i >= 0; i--) {
        heapify(v, v.size(), i);
    }

    for (int i = v.size() - 1; i >= 0; i--) {
        // heapify zet de root altijd vooraan. Daarom gaan moven we ze 1 per 1
        // naar achteren.
        swap(v[0], v[i]);
        // het kleinste getal komt hierdoor vanvoor te staan. We moeten dus de
        // nieuwe verkleinde array opnieuw ordenen.
        heapify(v, i, 0);
    }
}

template <class T>
ostream& operator<<(ostream& os, vector<T>& v) {
    for (int i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    os << endl;
    return os;
}

int main() {
    cout << "Before sorting: " << endl;
    vector<int> vector{4, 10, 3, 5, 1};
    cout << vector;
    heapsort(vector);
    cout << "Na sorteren\n" << vector;
    return 0;
}
