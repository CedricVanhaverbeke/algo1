#ifndef __SORTEERMETHODE
#define __SORTEERMETHODE
#include <iomanip>
#include <iostream>
#include "chrono.h"
#include "sortvector.cpp"
using std::cout;
using std::endl;
using std::left;
using std::move;
using std::right;
using std::setw;
using std::swap;
#include <algorithm>  // voor sort()-methode uit STL

/** class Sorteermethode
    \brief abstracte klasse van methodes die een vector sorteren
*/
template <typename T>
class Sorteermethode {
   public:
    /// \fn operator() sorteert de vector gegeven door het argument
    virtual void operator()(vector<T>& v) const = 0;

    /// \fn meet(int kortste, int langste, ostream& os) schrijft naar os een
    /// overzicht (met de nodige ornamenten) met de snelheid van de opgegeven
    /// sorteermethode *this. Er wordt 1 lijn uitgedrukt voor elke mogelijke
    /// grootte. Deze groottes zijn kleinste, 10*kleinste, 100*kleinste,
    /// enzovoorts, tot aan grootste.
    /// Op een lijn staat de snelheid van de methode toegepast op
    /// (1) een random tabel
    /// (2) een al gesorteerde tabel.
    /// (3) een omgekeerd gesorteerde tabel.

    /// Deze functie werkt alleen als T een toekenning van een int toelaat,
    /// zodat bv.
    ///    T a=5;
    /// geldig is.
    void meet(int kortste, int langste, ostream& os) {
        os << setw(20) << left << "lengte" << setw(20) << left << "random"
           << setw(20) << left << "gesorteerd" << setw(20) << left
           << "omgekeerd" << endl;
        for (int i = kortste; i <= langste; i *= 10) {
            // nieuwe vector maken van de juiste lengte
            Sortvector<int> vector{i};

            // Nieuwe chrono maken
            Chrono chrono;

            // Bereken tijd om te randomizen
            vector.shuffle();  // randomize vector
            auto shuffle = berekenTijdOmTeSorteren(vector, chrono);

            // Bereken tijd om te sorteren als hij al gesorteerd is
            vector.vul_range();
            auto gesorteerd = berekenTijdOmTeSorteren(vector, chrono);

            // Berkeen tijd om een omgekeerd gesorteerde tabel te sorteren
            vector.vul_omgekeerd();
            auto omgekeerd = berekenTijdOmTeSorteren(vector, chrono);

            os << setw(20) << i << setw(20) << shuffle << setw(20) << gesorteerd
               << setw(20) << omgekeerd << endl;
        }
    }

   private:
    double berekenTijdOmTeSorteren(vector<T>& vector, Chrono& chrono) {
        chrono.start();
        this->operator()(vector);
        chrono.stop();
        return chrono.tijd();
    }
};

/** \class STLSort
   \brief STANDARD TEMPLATE LIBRARY SORT
*/
template <typename T>
class STLSort : public Sorteermethode<T> {
   public:
    void operator()(vector<T>& v) const;
};

template <typename T>
void STLSort<T>::operator()(vector<T>& v) const {
    sort(v.begin(), v.end());
}

/** \class InsertionSort
 */
template <typename T>
class InsertionSort : public Sorteermethode<T> {
   public:
    void operator()(vector<T>& v) const;
};

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

/** \class Shellsort
 */

template <typename T>
class ShellSort : public Sorteermethode<T> {
   public:
    void operator()(vector<T>& v) const;
};

/** \class Mergesort
 */

template <typename T>
class MergeSort : public Sorteermethode<T> {
   public:
    void operator()(
        vector<T>& v) const;  // const want MergeSort object verandert niet

   private:
    void mergesort(vector<T>& v, int l, int r, vector<T>& hulp) const;
    void merge(vector<T>& v, int l, int m, int r, vector<T>& hulp) const;
};

template <typename T>
void MergeSort<T>::operator()(vector<T>& v) const {
    vector<T> hulp(v.size() / 2);  // Hulpvector heeft maximum v / 2 plaatsen
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

#endif