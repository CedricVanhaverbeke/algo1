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
    Mediaan berekenen van 3 elmenten
    bereken de mediaan door het grootste element te nemen en het kleinste en dat
   dan af te trekken van de totale som Aangezien het maar om 3 elementen gaat,
   is dat best snel.
*/

template <class T>
int getIndexOfMedianOfThreeValues(vector<T> &vector, int l, int r) {
    int a = vector[l], b = vector[(r - l) / 2], c = vector[r - 1];

    int index;

    // b is mediaan
    if ((a < b && b < c) || (c < b && a < c)) {
        index = l + (r - l) / 2;

        // a is mediaan
    } else if ((b < a && a < c) || (c < a && a < b)) {
        index = l;

        // c is mediaan
    } else {
        // For some reason werkt het algoritme niet
        // met waarden in de array die helemaal rechts staan
        // Daarom doe ik het met de voorlaatste
        index = r - 1;
    }

    return (index);
}

/*

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
void quick_sort(vector<T> &vector, int l, int r) {
    if (r - l > 1) {
        int index = getIndexOfMedianOfThreeValues(vector, l, r);

        // mediaan swappen
        // swap(vector[index], vector[0]);

        int hl = l, hr = r - 1;

        while (vector[hr] > vector[index]) {
            hr--;
        }
        while (vector[hl] < vector[index]) {
            hl++;
        }
        while (hl < hr) {
            swap(vector[hl], vector[hr]);
            hl++;
            hr--;

            while (vector[hl] < vector[index]) {
                hl++;
            }
            while (vector[hr] > vector[index]) {
                hr--;
            }
        }

        // sort both subvectors recursively
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