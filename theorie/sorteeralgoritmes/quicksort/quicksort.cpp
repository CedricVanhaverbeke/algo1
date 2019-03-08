#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>

using namespace std;

template <class T>
void print_vector(vector<T> &vector) {
    for (auto t : vector) {
        cout << t << " ";
    }
    cout << endl;
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

template <class T>
void quick_sort(vector<T> &vector, int l, int r) {
    // Enkel doen als de array groter is dan 1
    if (l < r - 1) {
        T pivot = vector[l];  // De spil wordt links gekozen
        int hl = l;
        int hr = r - 1;  // instellen op eentje minder dan r

        // Zoek naar een element kleiner dan de pivot
        while (vector[hr] > pivot) {
            hr--;
        }

        // Gevonden elementen links van de pivot plaatsen
        // STAP 3A
        while (hl < hr) {
            swap(vector[hl], vector[hr]);
            hl++;  // Eerste keer vergroten
            hr--;  // En verkleinen

            // STAP 3B
            while (vector[hl] < pivot) {
                hl++;
            }

            while (vector[hr] > pivot) {
                hr--;
            }
        }

        // Recursief aanroepen
        quick_sort(vector, l, hr + 1);
        quick_sort(vector, hr + 1, r);
    }
}

template <class T>
void quick_sort(vector<T> &vector) {
    quick_sort(vector, 0, vector.size());
}

int main() {
    srand(time(NULL));
    cout << "Before sorting: " << endl;
    std::vector<int> vector{10, 38, 27, 43, 3, 9, 82};
    print_vector(vector);

    cout << endl;

    cout << "After sorting: " << endl;
    quick_sort(vector);
    print_vector(vector);
    return 0;
}