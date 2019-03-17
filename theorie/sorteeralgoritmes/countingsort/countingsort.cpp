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

    // van achter naar voor werken.
    // in i houden we de index bij van de vector die moet gesorteerd worden
    int i = v.size() - 1; 

    // het in te vullen getal is r = rechtergrens in het begin
    int getal = r;     
    while (i >= 0) {
        // Hier schrijven we het getal het aantal keer uit
        // dat het in de frequentietabel staat
        // let op de -l zodat we zeker op de juiste index zitten
        for (int j = 0; j < frequentietabel[getal - l]; j++) {
            v[i] = getal;
            i--;
        }
        getal--;     // Nu mag het getal verminderen.
    }
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
