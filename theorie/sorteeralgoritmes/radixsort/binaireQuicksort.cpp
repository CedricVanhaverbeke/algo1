// https://www.csie.ntu.edu.tw/~b5506062/radixsort/RE1.htm
#include <bitset>
#include <iostream>
#include <string>
#include <vector>

using std::bitset;
using std::cout;
using std::endl;
using std::ostream;
using std::size_t;
using std::string;
using std::swap;
using std::vector;

// 1 enkel karakter is blijkbaar altijd 5 bits
const int BIT_SIZE = 5;

void binaireQuickSort(vector<char>& v);

void binaireQuickSort(vector<char>& v, int l, int r, int b);

template <class T>
ostream& operator<<(ostream& os, vector<T>& v);

bool bitIsSet(char el, int bit);

int main() {
    vector<char> v{'A', 'S', 'O', 'R', 'T', 'I', 'N', 'G',
                   'E', 'X', 'A', 'M', 'P', 'L', 'E'};
    cout << v;
    binaireQuickSort(v);
    cout << "vector na sorteren: " << endl << v;

    return 0;
}

/*
    Dit is eigenlijk een aangepaste vorm van quicksort.
    Bij quicksort hebben we een pivot nodig. We kiezen
    op voorhand geen pivot bij deze methode.
    . Het enige wat de methode direct overneemt
    is het swap gebeuren om zo veel mogelijk inversies
    op te lossen. De 'pivot' is dan de scheiding
    tussen het laatste element van de linkse array
    en het eerste element van de rechtse array

    Dit werkt omdat er maar twee mogelijke waarden zijn,
    omdat we binair werken. De enige waarden zijn dus 0 en 1

    We gaan eigenlijk gewoon de array bit voor bit gaan goed zetten
    zodat de nullen vooraan komen en de enen achteraan, we verdelen
    de tabel dus in 2 delen, vandaar binair!

    De methode is links naar rechts omdat ze we met het grootste bit beginnen.
    In ons geval staat de grootste bit helemaal links, op plaats 4

    Ik heb het eens gedaan met een array van chars. Om die te kunnen vergelijken
   heb ik dat omgezet naar bits. Ik had het ook gewoon kunnen tonen ints die
   iets binair voorstellen zoals 1010101010 maar da's niet cool, weetwel.

*/
// 4 is hier de hoogste bit die we kunnen hebben
void binaireQuickSort(vector<char>& v) {
    binaireQuickSort(v, 0, v.size(), BIT_SIZE - 1);
}

/*
    l = linkergrens
    r = rechtergrens
    b = hoeveelste bit we aan het overlopen zijn
*/

void binaireQuickSort(vector<char>& v, int l, int r, int b) {
    int i = l, j = r - 1;
    // De lengte moet groter blijven dan 1 en de bit mag niet onder 0
    if (r - l > 1 && b >= 0) {
        // Zolang de bit niet geset is links gaan we verder
        while (j != i) {
            while (i < j && !bitIsSet(v[i], b)) {
                i++;
            }
            while (j > i && bitIsSet(v[j], b)) {
                j--;
            }
            swap(v[i], v[j]);
        }
        // Na alle swaps te doen weten we dat i & j elkaar gekruisd zijn
        // Ze zijn gekruisd op dezelfde waarde, namelijk de 'pivot'
        int pivot = i;  // of pivot = j
        b--;            // We verlagen hier de bit naar 1 minder beduidende
        binaireQuickSort(v, l, pivot, b);
        binaireQuickSort(v, pivot, r, b);
    }
}

template <class T>
ostream& operator<<(ostream& os, vector<T>& v) {
    for (auto i : v) {
        os << i << " ";
    }
    os << endl;
    return os;
}

// bitset werkt blijkbaar niet goed met strings, dus ik doe het met chars.
// Daarvoor kan je bitset gebruiken blijkbaar en testen op een bit.
bool bitIsSet(char el, int bit) {
    bitset<BIT_SIZE> b(el);
    return b.test(size_t(bit));
}