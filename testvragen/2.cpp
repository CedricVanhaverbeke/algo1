#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::move;
using std::ostream;
using std::swap;
using std::vector;

template <class T>
ostream& operator<<(ostream& os, vector<T>& v) {
    for (auto i : v) {
        os << i << " ";
    }
    os << endl;
    return os;
}

// Methode zoekt de gesorteerde plaats
// van een element in een vector met een bepaalde index
// Dit doet dus 1 stap van quicksort
template <class T>
int vindGesorteerdePlaats(vector<T>& v, int index) {
    swap(v[index], v[0]);
    T pivot = move(v[0]);
    int hl = 0, hr = v.size() - 1;

    while (v[hr] > pivot) {
        hr--;
    }
    while (v[hl] < pivot) {
        hl++;
    }

    while (hl < hr) {
        swap(v[hl], v[hr]);
        hl++;
        hr--;

        while (v[hl] < pivot) {
            hl++;
        }
        while (v[hr] > pivot) {
            hr--;
        }
    }

    cout << "hr: " << hr << endl << "hl" << hl << endl << v;
    return hr;
}

int main() {
    vector<int> v{33, 11, 7, 9, 24, 54};
    int plaats = vindGesorteerdePlaats(v, 0);
    // cout << "Plaats is " << plaats << endl;

    return 0;
}
