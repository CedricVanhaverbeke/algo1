// https://www.cs.usfca.edu/~galles/visualization/RadixSort.html
#include <math.h>
#include <iostream>
#include <vector>

using std::cout;
using std::endl;
using std::move;
using std::ostream;
using std::vector;

template <class T>
ostream& operator<<(ostream& os, vector<T>& v);

// Hier halen we uit een getal bv 5679 een cijfer van een bepaalde index
// met een radix.
// radix is meestal 10, toch hier wel
// dus getNumberAtIndex(5679, 3, 10) = 6
// en getNumberAtIndex(5679, 4, 10) = 5
int getNumberAtIndex(int totaalNummer, int index, int radix) {
    return int(totaalNummer / pow(radix, index - 1)) % radix;
}

/*
    Counting sort toegepast op een bepaalde exponent van 10 in van een getal
    v = de originele vector
    exp = de exponent waarover we praten. bv 3'e exp van 368 wil zeggen: het
    getal 3
    m = de radix, hier het getal 10. We rekenen in een tientallig stelsel
    l = de linkerpositie van de deelrij van v
    r = de rechterpositie van de deelrij van v
    help = een hulpvector van de grootte r - l die dient voor de sortering
    Nadat gesorteerd is binnen de grenzen op de exponent wordt alles terug in v
   geplaatst.
*/

void countSort(vector<int>& v, int exp, int m, int l, int r,
               vector<int>& help) {
    vector<int> frequentietabel(m, 0);

    // Hier maken we de frequentietabel aan
    for (int i = l; i < r; i++) {
        frequentietabel[getNumberAtIndex(v[i], exp, m)]++;
    }

    // Waarden in de frequentietabel cummulatief maken
    for (int i = 1; i < frequentietabel.size(); i++) {
        frequentietabel[i] += frequentietabel[i - 1];
    }

    /* Om de plaats van de elementen te weten te komen in de hulparray
     gebruiken we de frequentietabel. De plaats waar het moet
     terechtkomen is eentje kleiner dan hetgeen in de frequentietabel staat
     voor het getal op die plaats.

     bv: frequentietabel = 1 0 0 0 0 0 0 0 0 0
     Dit wil zeggen: in de vector met bepaalde grenzen komt het getal 0 op een
     bepaalde exp van het getal, 1 keer voor. Zo'n getal kan bv 350 zijn. 0 komt
     voor op de 1e exp

     Als we nu de plaats willen weten van het getal dat daarbij hoort trekken we
     1 af van de waarde van de locatie van frequentietabel[0]

     In de hulptabel staat 0 dus op de 0'de plaats

     Ik verwijs graag naar de link om het algoritme uit te visualiseren voor een
     makkelijkere uitleg

    */

    for (int i = r - 1; i >= l; i--) {
        // Waarde verkleinen in de frequentietabel en dan opvragen
        help[--frequentietabel[getNumberAtIndex(v[i], exp, m)]] = v[i];
    }

    // Waarden terug in de originele vector plaatsen
    for (int i = l; i < r; i++) {
        v[i] = move(help[i - l]);
    }

    exp--;  // Exponent verminderen
    for (int i = 1; i <= frequentietabel.size(); i++) {
        // Enkel nieuwe sorteer doen als de waarden groter zijn dan 1
        if (frequentietabel[i] - frequentietabel[i - 1] > 1 && exp > 0) {
            // Hier wordt een nieuwe hulpvector gemaakt van de juiste grootte
            vector<int> help2(frequentietabel[i] - frequentietabel[i - 1], 0);

            // Doe hier de sortering voor de nieuwe range
            countSort(v, exp, m, frequentietabel[i - 1] + l,
                      frequentietabel[i] + l, help2);
        }
    }
}

/*
    Het principe van MSDradixsort is volledig analoog aan binaire quicksort.
    Alleen gaan we hier sorteren op grotere m (of dus de radix) waarden. Bij
   binair was dat 2.

    Het ligt dus voor de hand om gebruik te maken van countingsort om de
    onderlinge waarden te gaan sorteren

    Het nadeel aan deze methode is dat we met deeltabellen moeten werken omdat
    we van links naar rechts gaan (van meest beduidende naar minst).
*/

void radixsort(vector<int>& v, int m) {
    // Maximum aantal getallen in een cijfer
    // normaal moet je dat berekenen, ik heb ervoor gekozen om het hard te
    // coderen
    int max = 3;

    // Help vector
    vector<int> help(v.size(), 0);

    // Pas nu countingsort toe voor een bepaald
    // getal in het cijfer. We beginnen logischerwijs
    // op de grootste exponent, namelijk max.
    countSort(v, max, 10, 0, v.size(), help);
}

int main() {
    vector<int> v{696, 658, 759, 654, 457};
    cout << v << endl;

    // We gaan sorteren in een tientallig stelsel
    radixsort(v, 10);
    cout << "vector na sorteren: " << endl << v;

    return 0;
}

template <class T>
ostream& operator<<(ostream& os, vector<T>& v) {
    for (auto i : v) {
        os << i << " ";
    }
    os << endl;
    return os;
}