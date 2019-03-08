#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <utility>
#include <vector>

using std::cout;
using std::endl;
using std::ostream;
using std::rand;
using std::srand;
using std::swap;
using std::vector;

template <typename T>
void quicksort(vector<T> &v, int l, int r);

template <typename T>
void quicksort(vector<T> &v);

template <typename T>
ostream &operator<<(ostream &os, vector<T> &v);

int getRandomPivotIndex(int l, int r);

int main() {
    // initialize the random seed
    srand(time(NULL));

    // create the vector of items
    vector<int> v = {10, 38, 27, 43, 3, 9, 82};  // print the unsorted vector
    cout << "Unsorted: \n";
    cout << v;
    cout << "\n";
    // sort the vector
    quicksort(v);
    // print the sorted vector
    cout << "Sorted: \n";
    cout << v;

    return 0;
}

// Sorts the subvector v[l..r]
// l = left index
// r = right index
template <typename T>
void quicksort(vector<T> &vector, int l, int r) {
    if (l < r - 1) {
        // Partition with the median of 3 as pivot
        T pivot = vector[getRandomPivotIndex(l, r - 1)];
        int hl = l, hr = r - 1;

        while (vector[hr] > pivot) {
            hr--;
        }
        while (vector[hl] < pivot) {
            hl++;
        }
        while (hl < hr) {
            swap(vector[hl], vector[hr]);
            hl++;
            hr--;

            while (vector[hl] < pivot) {
                hl++;
            }
            while (vector[hr] > pivot) {
                hr--;
            }
        }

        // sort both subvectors recursively
        quicksort(vector, l, hr + 1);
        quicksort(vector, hr + 1, r);
    }
}

template <typename T>
void quicksort(vector<T> &vector) {
    quicksort(vector, 0, vector.size());
}

// Shows the operator << how to print the vector
template <typename T>
ostream &operator<<(ostream &os, vector<T> &v) {
    for (int i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    os << endl;
    return os;
}

int getRandomPivotIndex(int l, int r) {
    int length = r - l;

    int pivot_index = l + rand() % (length + 1);

    return pivot_index;
}