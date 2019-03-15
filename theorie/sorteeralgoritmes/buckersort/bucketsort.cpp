#include <cstdlib>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::move;
using std::ostream;
using std::vector;

// printing function of vector
template <class T>
ostream& operator<<(ostream& os, vector<T>& v) {
    for (auto i : v) {
        os << i << " ";
    }
    os << endl;
    return os;
}

template <class T>
void insertion_sort(vector<T>& v) {
    for (int i = 1; i < v.size(); i++) {
        T h = move(v[i]);
        int j = i - 1;
        while (j >= 0 && h < v[j]) {
            v[j + 1] = move(v[j]);
            j--;
        }
        v[j + 1] = move(h);
    }
}

// Geeft het eerste getal na de komma terug
int getFirstDigit(double v) { return int(v * 10); }

// Implementatie met gewone vectoren en wanneer ze gevuld zijn insertion sort
// The good way zou met LinkedLists zijn
// maar daar had ik voorlopig nog geen zin in
void bucketSort(vector<double>& v) {
    vector<vector<double>> buckets(10);

    // Plaats alles in de buckets
    for (int i = 0; i < v.size(); i++) {
        int digit = getFirstDigit(v[i]);
        buckets[digit].push_back(v[i]);
    }

    // Aangezien er maar zeer wenig waarden zijn in de buckets
    // Kunnen we die insertion sorten
    // Met linkedlist zou je ze kunnen toevoegen in gesorteerde
    // volgorde, maar da's voor later
    for (int i = 0; i < buckets.size(); i++) {
        insertion_sort(buckets[i]);
    }

    // .. En dan alles terugplaatsen
    int k = 0;  // k is de index van v
    for (int i = 0; i < buckets.size(); i++) {
        for (int j = 0; j < buckets[i].size(); j++) {
            v[k] = buckets[i][j];
            k++;
        }
    }
}

int main() {
    vector<double> v = {0.78, 0.17, 0.39, 0.26, 0.72,
                        0.94, 0.21, 0.12, 0.23, 0.68};

    cout << v;

    bucketSort(v);

    cout << "Na sorteren: " << endl << v;
    return 0;
}