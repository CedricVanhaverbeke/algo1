#include <math.h>
#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::ostream;
using std::string;
using std::swap;
using std::vector;

template <class T>
ostream& operator<<(ostream& os, vector<T>& v) {
    for (auto i : v) {
        os << i << " ";
    }
    os << endl;
    return os;
}

// Hier halen we uit een getal bv 5679 een cijfer van een bepaalde index
// met een radix.
// radix is meestal 10, toch hier wel
// dus getNumberAtIndex(5679, 3, 10) = 6
// en getNumberAtIndex(5679, 4, 10) = 5
int getNumberAtIndex(int totaalNummer, int index, int radix) {
    return int(totaalNummer / pow(radix, index - 1)) % radix;
}

/*
    STAP 1 is meestal je elementen allemaal even groot
    'padden'. Bv v = { 100 10 1210} ==> {0100 0010 1210}
    Maar 'k heb geen zin om met strings te werken dus ik doe
    dat niet

    Deze methode kiest zoals bij quicksort een spilelement. Hier kies ik ook
    de meest linkse. Dan gaan we quicksorten van een bepaald getal van een
   cijfer we gaan bv eerst sorteren op het eerste getal volgens de manier van
   quicksort. Dus links heb je allemaal getallen die kleiner zijn, rechts
   allemaal getallen die groter zijn

    In het midden staat er nu echter meer dan 1 getal, want ja, je sorteert
   slechts op 1 cijfer. Vandaar dat ik die grenzen bepaal met i & j. Wellicht
   kan het sneller, maar deze methode werkt wel
*/
void ternaireRadixQuicksort(vector<int>& v, int exp, int l, int r) {
    if (r - l > 1 && exp > 0) {
        int pivot = getNumberAtIndex(v[l], exp, 10);
        int hl = l, hr = r - 1;

        while (getNumberAtIndex(v[hr], exp, 10) > pivot) {
            hr--;
        }
        while (getNumberAtIndex(v[hl], exp, 10) < pivot) {
            hl++;
        }
        while (hl < hr) {
            swap(v[hl], v[hr]);
            hl++;
            hr--;

            while (getNumberAtIndex(v[hl], exp, 10) < pivot) {
                hl++;
            }
            while (getNumberAtIndex(v[hr], exp, 10) > pivot) {
                hr--;
            }
        }

        // Pivot op de juiste plaats terugzetten, die staat sowieso op v[0]
        // Voorlopig geen betere manier gevonden
        // i is begin van de middenstrook
        // j is het einde van de middenstrook
        int i = l;
        while (getNumberAtIndex(v[i], exp, 10) >
               getNumberAtIndex(v[i + 1], exp, 10)) {
            swap(v[i], v[i + 1]);
            i++;
        }

        int j = i;
        while (getNumberAtIndex(v[j], exp, 10) == pivot) {
            j++;
        }
        // Drie subvectoren opnieuw sorteren
        ternaireRadixQuicksort(v, exp, l, i);
        ternaireRadixQuicksort(v, exp - 1, i, j);
        ternaireRadixQuicksort(v, exp, j, r);
    }
}

int main() {
    vector<int> v = {466, 308, 228, 221, 537, 551, 433, 422, 437, 825};
    int exp = 3;
    int teller = 0;
    ternaireRadixQuicksort(v, 3, 0, v.size());
    cout << v;

    return 0;
}