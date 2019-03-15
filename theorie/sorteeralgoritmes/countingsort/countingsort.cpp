#include <iostream>
#include <vector>

using namespace std;

// Shows the operator << how to print the vector
template <typename T>
ostream& operator<<(ostream& os, vector<T>& v) {
    for (int i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    os << endl;
    return os;
}

void print_array(int* tabel, int size) {
    for (int i = 0; i < size; i++) {
        cout << tabel[i] << " ";
    }
}

// countingsort werkt alleen met integers
// Het interval is bekend!
// l = linkergrens interval
// r = rechtergrens interval
void countingsort(vector<int>& v, int l, int r) {
    // frequentietabel aanmaken
    vector<int> frequentietabel(r - l + 1, 0);

    for (int i = 0; i < v.size(); i++) {
        // vb: 5 - 5 ==> 5 komt op 0 terecht in de frequentietabel
        frequentietabel[v[i] - l]++;
    }

    cout << "Bijhorende frequentietabel: " << endl;

    cout << frequentietabel << endl << endl;

    cout << "\n";

    // zonder hulpvector: van achter naar voor werken
    int i = v.size();  // i is de index van de originele vector
    int getal = r;     // het in te vullen getal is r in het begin
    while (i >= 0) {
        // We halen op hoeveel keer we het // getal moeten schrijven
        int aantalKeer = frequentietabel[getal - l];

        // Hier schrijven we het getal zoveel keer uit
        for (int j = aantalKeer; j > 0; j--) {
            v[i] = getal;
            i--;
        }

        // Nu mag het getal verminderen.
        getal--;
    }

    // Met hulpvector
    /*vector<int> sortedVector;
    for (int i = 0; i < r - l + 1; i++) {
        for (int j = 0; j < frequentietabel[i]; j++) {
            sortedVector.push_back(i + l);  // l er terug bij optellen
        }
    }

    v = sortedVector;
    */
}

int main() {
    // countingsort werkt goed met ints die meerdere keren voorkomen
    vector<int> v{5,  6,  5,  7,  8, 9, 10, 11, 11, 13,
                  13, 12, 11, 10, 5, 6, 7,  7,  9,  8};

    cout << "originele vector: " << endl << v << endl << endl;

    countingsort(v, 5, 13);
    cout << "Gesorteerde rij: " << endl << v;
    return 0;
}
