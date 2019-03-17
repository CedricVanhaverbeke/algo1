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
    HOE WERKT HET MERGEN?
    we houden 3 tellertjes bij
    k: is er louter om de index te bepalen van de hulparray
    h(ulp)l: gaan we instellen op l zodat we de originele waarde van l nog
   kennen h(ulp)m: gaan we instellen op m zodat we de originele waarde van m nog
   kennen

    We doen zolang 1 van de 2 subarrays doorlopen is:
        - check welk element het kleinste van de eerste 2 niet gekozen elementen
   uit beide subarrays
        - plaats dit element op plaats k in de hulparray.
        - verhoog de juiste tellers, en zeker ook k

    Wanneer 1 van de 2 subarrays doorlopen is kan het zijn dat de andere nog
   niet volledig leeg is. Dus we gaan ze volledig leeg maken met 2 simpele while
   loops

    Daarna doorlopen we de hulparray en plaatsen we de elementen (op de juiste
   plaats) terug in de originele array

*/

template <class T>
void merge(vector<T> &vector, int l, int m, int r, std::vector<T> &hulp) {
    int k = 0;  // k dient om de hulparray in te vullen
    int hl = l;
    int hm = m;
    while (hl < m && hm < r) {
        int kleinste_index = -1;
        if (vector[hm] < vector[hl]) {
            kleinste_index = hm;
            hm++;  // verschuif hm
        } else {
            kleinste_index = hl;
            hl++;  // verschuif hl
        }
        hulp[k] = move(vector[kleinste_index]);
        k++;
    }

    // Ontbrekende zaken toevoegen
    while (hl < m) {
        hulp[k] = move(vector[hl]);
        hl++;
        k++;
    }
    while (hm < r) {
        hulp[k] = move(vector[hm]);
        hm++;
        k++;
    }

    // Hulparray op de juiste plaats in de originele vector steken
    for (int i = 0; i < k; i++) {
        vector[l + i] = move(hulp[i]);
    }
}

/*
    Basically bestaat merge sort uit 4 stappen
    1. Bepaal het midden
    2. Roep recursief merge_sort aan voor de linker deelrij
    3. Roep recursief merge_sort aan voor de rechter deelrij
    4. Merge beide rijen
*/

template <class T>
void merge_sort(vector<T> &vector, int l, int r, std::vector<T> &hulp) {
    // Als de grootte van de array groter is dan 1
    if (r - l > 1) {
        // Veiliger dan (l+r) / 2. Bepaalt het midden,
        // r-l is de grootte van de array
        int m = l + (r - l) / 2;
        merge_sort(vector, l, m, hulp);  // Links deel
        merge_sort(vector, m, r, hulp);  // Rechts deel
        merge(vector, l, m, r, hulp);    // Samenvoegen met hulpvector
    }
}

template <class T>
void merge_sort(vector<T> &vector) {
    std::vector<T> h(vector.size());          // Hulpvector
    merge_sort(vector, 0, vector.size(), h);  // Andere functie aanroepen
}

int main() {
    cout << "Before sorting: " << endl;
    std::vector<int> vector{5, 4, 3, 2, 1, 0};
    print_vector(vector);

    cout << endl;

    cout << "After sorting: " << endl;
    merge_sort(vector);
    print_vector(vector);
    return 0;
}