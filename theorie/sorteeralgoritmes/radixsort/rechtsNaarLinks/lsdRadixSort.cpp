// zie p 57 cursus
#include <math.h>
#include <iostream>
#include <vector>

using std::cout;
using std::ostream;
using std::vector;
using std::endl;

template <class T>
ostream& operator<<(ostream& os, vector<T>& v) {
    for (auto i : v) {
        os << i << " ";
    }
    os << endl;
    return os;
}

int getNumberAtIndex(int totaalNummer, int index, int radix) {
    return int(totaalNummer / pow(radix, index)) % radix;
}

void countSort(vector<int>& v, int exp, int m, vector<int>& help) {
    vector<int> frequentietabel(m, 0);

    // Hier maken we de frequentietabel aan
    for (int i = 0; i < v.size(); i++) {
        frequentietabel[getNumberAtIndex(v[i], exp, m)]++;
    }

    // Waarden in de frequentietabel cummulatief maken
    for (int i = 1; i < frequentietabel.size(); i++) {
        frequentietabel[i] += frequentietabel[i - 1];
    }

    // Hulptabel vullen
    for (int i = v.size() - 1; i >= 0; i--) {
        help[--frequentietabel[getNumberAtIndex(v[i], exp, m)]] = v[i];
    }

    v = help;  // Waarden in de gewone tabel steken
}

// m = radix
/*
    Lowest Significant Digit Radix sort werkt zeer eenvoudig.
    We doen eigenlijk hetzelfde als van links naar rechts
    alleen hoeven we hier geen deeltabellen te gebruiken

    zolang dat de sorteermethode die gebruikt wordt voor elk
    deel van het getal stabiel is zal radix sort in zijn totaliteit
    correct werken.

    Voor getallen is countSort een stabiel sorteeralgoritme. Daarom
    kunnen we countSort gebruiken. We hebben hiervoor wel een hulptabel
    nodig en een frequentietabel

    De radix is hier 10
*/
void lsdRadixSort(vector<int>& v, int m, int maxExpo) {
    vector<int> help(v.size(), 0);
    for (int i = 0; i <= maxExpo; i++) {
        countSort(v, i, 10, help);
    }
}

int main() {
    vector<int> v = {317, 992, 170, 627, 309, 852, 691, 753, 380, 261};
    cout << v;
    lsdRadixSort(v, 10, 3);
    cout << "Na sorteren:" << endl << v;
    return 0;
}