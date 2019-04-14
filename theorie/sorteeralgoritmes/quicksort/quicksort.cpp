#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, vector<T>& v) {
    for (int i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    os << endl;
    return os;
}

/*
    ALS PIVOT LINKS IS:

    STAP 1: variabelen klaarzetten
    pivot = element links ervan moeten kleiner worden, rechts ervan groter
    De pivot staat op de juiste plaats na 1 keer recursieve deelstap
    hl = hulp links
    hr = hulp rechts (eentje kleiner dan de tabel)

    STAP 2: Rechts beginnen zoeken naar een element dat kleiner is

    STAP 3:
    a. We swappen de elementen zodat het element gevonden in stap 2 voor de
   pivot staat b. we laten hl en hr vergroten / verkleinen tot een nieuw element
   gevonden is om te kunnen swappen
*/

template <typename T>
void quick_sort(vector<T>& vector, int l, int r) {
    if (l < r - 1) {
        T pivot = vector[l];
        int hl = l, hr = r - 1;

        // Dit is om ervoor te zorgen dat we zowel
        // l kunnen kiezen als begin als r

        // Vinden van een waarde kleiner dan de pivot achteraan
        while (vector[hr] > pivot) {
            hr--;
        }

        // Vinden van een waarde groter dan de pivot vooraan
        while (vector[hl] < pivot) {
            hl++;
        }

        // Hier beginnen we effectief te sorteren
        while (hl < hr) {
            swap(vector[hl], vector[hr]);
            hl++;
            hr--;

            // Hier weer hetzelfde doen als ervoor
            while (vector[hl] < pivot) {
                hl++;
            }
            while (vector[hr] > pivot) {
                hr--;
            }
        }

        // Recursief alles sorteren
        quick_sort(vector, l, hr + 1);
        quick_sort(vector, hr + 1, r);
    }
}

template <class T>
void quick_sort(vector<T>& vector) {
    quick_sort(vector, 0, vector.size());
}

int main() {
    srand(time(NULL));
    cout << "Before sorting: " << endl;
    std::vector<int> vector{
        10, 38, 27, 43, 3, 9, 82, 9,
    };
    cout << vector;

    cout << "After sorting: " << endl;
    quick_sort(vector);
    cout << vector;
    return 0;
}