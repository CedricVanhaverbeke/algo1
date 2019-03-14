#include "sorteermethode.h"
#include <vector>

using namespace std;

template <typename T>
void STLSort<T>::operator()(vector<T>& v) const {
    sort(v.begin(), v.end());
}

template <typename T>
void InsertionSort<T>::operator()(vector<T>& v) const {
    for (int i = 1; i < v.size(); i++) {
        T h;
        h = move(v[i]);
        int j = i - 1;
        while (j >= 0 && h < v[j]) {
            v[j + 1] = move(v[j]);
            j--;
        }
        v[j + 1] = move(h);
    }
}

template <typename T>
void MergeSort<T>::operator()(vector<T>& v) const {
    vector<T> hulp(v.size());  // Hulpvector heeft maximum v / 2 plaatsen
    mergesort(v, 0, v.size(), hulp);
}

template <typename T>
void MergeSort<T>::mergesort(vector<T>& v, int l, int r,
                             vector<T>& hulp) const {
    // Enkel doen als de array groter is dan 1
    // Dus als l links zit van r gaan we splitsen
    if (l < r - 1) {
        // Midden is gelijk aan de lengte (r -l) plus de locatie van l
        int m = l + ((r - l) / 2);

        // Splits links deel op
        mergesort(v, l, m, hulp);

        // Splits rechts deel op
        mergesort(v, m, r, hulp);

        // Voeg de delen samen
        merge(v, l, m, r, hulp);
    }
}

template <typename T>
void MergeSort<T>::merge(vector<T>& v, int l, int m, int r,
                         vector<T>& hulp) const {
    int k = 0, i = l, j = m, kleinste_index;
    while (i < m && j < r) {
        if (v[j] < v[i]) {
            kleinste_index = j;
            j++;
        } else {
            kleinste_index = i;
            i++;
        }
        hulp[k] = move(v[kleinste_index]);
        k++;
    }

    while (i < m) {
        hulp[k] = move(v[i]);
        k++;
        i++;
    }

    while (j < r) {
        hulp[k] = move(v[j]);
        k++;
        j++;
    }

    for (int i = 0; i < k; i++) {
        v[l + i] = move(hulp[i]);
    }
}

template <class T>
int MergeSort<T>::berekeInversies(vector<T>& v) {
    vector<T> hulp(v.size());
    int aantalInversies = 0;
    return berekenInversies(v, 0, v.size(), hulp, aantalInversies);
}

template <class T>
int MergeSort<T>::berekenInversies(vector<T>& v, int l, int r, vector<T>& hulp,
                                   int& aantalInversies) const {
    if (l < r - 1) {
        // Midden is gelijk aan de lengte (r -l) plus de locatie van l
        int m = l + ((r - l) / 2);

        // Splits links deel op
        berekenInversies(v, l, m, hulp, aantalInversies);

        // Splits rechts deel op
        berekenInversies(v, m, r, hulp, aantalInversies);

        // Voeg de delen samen
        merge(v, l, m, r, hulp, aantalInversies);
    }

    // Hier pas wanneer alle mergestappen gedaan zijn
    return aantalInversies;
}

template <typename T>
void MergeSort<T>::merge(vector<T>& v, int l, int m, int r, vector<T>& hulp,
                         int& aantalInversies) const {
    int k = 0, i = l, j = m, kleinste_index;
    while (i < m && j < r) {
        if (v[j] < v[i]) {
            kleinste_index = j;
            aantalInversies += (m - i);
            j++;
        } else {
            kleinste_index = i;
            i++;
        }
        hulp[k] = move(v[kleinste_index]);
        k++;
    }

    while (i < m) {
        hulp[k] = move(v[i]);
        k++;
        i++;
    }

    while (j < r) {
        hulp[k] = move(v[j]);
        k++;
        j++;
    }

    for (int i = 0; i < k; i++) {
        v[l + i] = move(hulp[i]);
    }
}