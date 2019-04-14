#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::ostream;
using std::swap;
using std::vector;
/*
    Basically doet quickselect het volgende:
    Het probleem is dus om het k'de-kleinste element te zoeken in een vector:

    Stel, we willen van volgende vector het 4e kleinste element vinden
    9 8 4 2 10 1

    We gaan quicksort stappen doen tot het element dat we als spil gekozen
   hebben terecht komt op de k'de plaats. Bij ons begint quicksort vanaf links

   Stap 1) 9 op zijn plaats zetten, door quicksort weten wz dat alle elementen
   kleiner dan 9 links staan en alle elementen groter rechts. Hoeft niet per se
   in juiste volgorde te zijn 8 4 2 1 9 10

   9 staat op de 4e plaats en is dus het 5e kleinste element (arrays beginnen op
   0) Nu doen we dus weer quickosrt, dit keer op de linkertabel op de meest
   linkse waarde,  2 1 4 8 9 10

    8 op de 3e plaats en is dus het 4e kleinte element. Het k'de element is dus
   gevonden
*/

template <typename T>
ostream& operator<<(ostream& os, vector<T>& v) {
    for (int i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    os << endl;
    return os;
}

template <typename T>
T quickselect(vector<T>& v, int l, int r, int k) {
    l++;
    if (l < r - 1) {
        T pivot = v[l - 1];
        int i = l, j = r - 1;

        // Dit is om ervoor te zorgen dat we zowel
        // l kunnen kiezen als begin als r

        // Vinden van een waarde kleiner dan de pivot achteraan
        while (v[j] > pivot) {
            j--;
        }

        // Hier beginnen we effectief te sorteren
        while (i < j) {
            swap(v[i], v[j]);
            i++;
            j--;

            // Hier weer hetzelfde doen als ervoor
            // i op tijd laten stoppen
            while (v[i] < pivot && i < r - 1) {
                i++;
            }
            while (v[j] > pivot) {
                j--;
            }
        }

        // Vind juiste plaats van pivot
        int z = r - 1;
        while (v[z] > pivot) {
            z--;
        }

        // swap als het element waarop we terecht gekomen zijn niet de pivot is
        if (v[z] != pivot) {
            swap(v[0], v[z]);
        }

        if (k == z) {
            // element gevonden
            return v[z];
        }

        if (k > z) {
            // rechts zoeken
            return quickselect(v, 0, z - 1, k - z);
        }

        if (k < z) {
            return quickselect(v, 0, z + 1, k);
        }

    } else {
        // We hebben het element gevonden
        return v[l];
    }
}

template <class T>
T quickselect(vector<T>& v, int k) {
    vector<T> copy(v);
    int value = quickselect(copy, 0, copy.size(), k);
    return value;
}

template <class T>
T geefKdeKleinsteElement(vector<T>& v, int k) {
    // k - 1 want array indices gebruiken
    int value = quickselect(v, k - 1);
    return value;
}

int main() {
    vector<int> v = {98, 33, 1, 2, 3};
    cout << geefKdeKleinsteElement(v, 2);

    return 0;
}