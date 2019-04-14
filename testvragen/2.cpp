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
    if (v.size() > 1) {
        swap(v[index], v[0]);
        T pivot = v[index];
        int i = 0, j = v.size() - 1;

        while (v[i] < pivot) {
            i++;
        }

        while (v[j] > pivot) {
            j--;
        }

        while (i < j) {
            swap(v[i], v[j]);
            i++;
            j--;

            while (v[i] < pivot) {
                i++;
            }

            while (v[j] > pivot) {
                j--;
            }
        }
    }

    return 0;
}

int main() {
    vector<int> v{33, 11, 7, 9, 24, 54};
    cout << v;
    int plaats = vindGesorteerdePlaats(v, 3);
    // cout << "Plaats is " << plaats << endl;
    cout << v;
    return 0;
}
