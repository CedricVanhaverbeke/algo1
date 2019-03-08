#include <stdlib.h>
#include <time.h>
#include "istring.h"
#include "sorteermethode.h"
using namespace std;

int main() {
    srand(time(NULL));

    Sortvector<int> vector{5};

    STLSort<int> stlSort;
    stlSort.operator()(vector);  // Of stlSort(vector)

    Sortvector<int> vector2{10};

    InsertionSort<int> insertionSort;
    insertionSort(vector2);
    cout << vector2 << endl << endl;

    // Testen of de vector ook werkt met ins`trings
    Sortvector<Intstring> vector3{5};
    cout << vector3 << endl << endl;

    // meet testen
    stlSort.meet(10, 10000, cout);
    cout << endl;
    insertionSort.meet(10, 10000, cout);

    cout << endl << endl << "Nu met intstrings" << endl << endl;

    // Testen met Intstring
    STLSort<int> stlSort2;
    InsertionSort<Intstring> insertionSort2;

    stlSort.meet(10, 10000, cout);
    cout << endl;
    insertionSort.meet(10, 10000, cout);

    // Mergesort testen
    Sortvector<int> vector4{6};
    vector4.vul_omgekeerd();

    MergeSort<int> mergeSort;
    mergeSort(vector4);
    cout << vector4;

    return 0;
}