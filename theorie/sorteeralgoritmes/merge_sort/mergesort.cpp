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
    h(ulp)l: gaan we instellen op l zodat we de originele waarde van l nog kennen
    h(ulp)m: gaan we instellen op m zodat we de originele waarde van m nog kennen

    We doen zolang 1 van de 2 subarrays doorlopen is:
        - check welk element het kleinste van de eerste 2 niet gekozen elementen uit beide subarrays
        - plaats dit element op plaats k in de hulparray.
        - verhoog de juiste tellers, en zeker ook k
    
    Wanneer 1 van de 2 subarrays doorlopen is kan het zijn dat de andere nog niet volledig leeg is.
    Dus we gaan ze volledig leeg maken met 2 simpele while loops

    Daarna doorlopen we de hulparray en plaatsen we de elementen (op de juiste plaats) terug
    in de originele array

*/

template <class T>
void merge(vector<T> &vector, int l, int m, int r, std::vector<T> &hulp) {
    int k = 0;  // k dient om de hulparray in te vullen
    int hl = l;
    int hm = m;
    while (hl < m && hm < r) {
        int kleinste = -1;
        if (vector[hm] < vector[hl]) {
            kleinste = vector[hm];
            hm++; // verschuif hm
        } else {
            kleinste = vector[hl];
            hl++; // verschuif hl
        }
        hulp[k] = kleinste;
        k++;
    }

    // Ontbrekende zaken toevoegen
    while (hl < m) {
        hulp[k] = vector[hl];
        hl++;
        k++;
    }
    while (hm < r) {
        hulp[k] = vector[hm];
        hm++;
        k++;
    }

    // Hulparray op de juiste plaats in de originele vector steken
    for (int i = 0; i < k; i++) {
        vector[l + i] = hulp[i];
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
    // Als l kleiner is dan r
    if (l < r - 1) {
        int m = l + (r - l) / 2;  // Veiliger dan (l+r) / 2. Bepaalt het midden
        merge_sort(vector, l, m, hulp);  // Links deel
        merge_sort(vector, m, r, hulp);  // Rechts deel
        merge(vector, l, m, r, hulp);    // Samenvoegen met hulpvector
    }
}

template <class T>
void merge_sort(vector<T> &vector) {
    // De hulpvector kan je in elke stap hergebruiken en is maximaal de helft zo groot als de
    // originele array
    std::vector<T> h(vector.size() / 2);      // Hulpvector
    merge_sort(vector, 0, vector.size(), h);  // Andere functie aanroepen
}

int main() {
    cout << "Before sorting: " << endl;
    std::vector<int> vector{38,27,43,3,9,82,10};
    print_vector(vector);

    cout << endl;

    cout << "After sorting: " << endl;
    merge_sort(vector);
    print_vector(vector);
    return 0;
}