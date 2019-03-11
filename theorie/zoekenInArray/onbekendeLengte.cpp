// zie p 48

#include <iostream>
#include <vector>

using namespace std;

// Functie om de elementen te berekenen
int berekenElementInSequetie(int index) { return index * 16 - 3; }

// Aangepaste vorm van binair zoeken
int binairZoeken(int el, int l, int r) {
    while (r - l > 1) {  // When size of the vector keeps being bigger than 1
        int m = l + (r - l) / 2;  // Gets the middle of the vector
        if (el < berekenElementInSequetie(m)) {
            r = m;
        } else {
            l = m;
        }
    }
    return el == berekenElementInSequetie(l) ? l : -1;
}

// De sequentie kennen we niet op voorhand
// Ze wordt berekend aan de hand van de functie
int vindInSequentie(int el) {
    int xi = 1;
    while (berekenElementInSequetie(xi - 1) < el) {
        xi *= 2;
    }

    // We weten nu zeker dat xi/2 < el <= xi

    // Nu gaan we binair zoeken in de juiste range van elementen
    return binairZoeken(el, xi / 2, xi);
}

int main(int argc, char** argv) {
    // Eerste 10 element van de sequentie worden geprint
    // Gewoon ter illustratie. Om snel te zien dat 77 index 5 heeft
    for (int i = 0; i < 10; i++) {
        cout << berekenElementInSequetie(i) << " ";
    }

    cout << endl;

    int element = 77;

    cout << "Element " << element << " heeft index " << vindInSequentie(element)
         << " in de array." << endl;

    return 0;
}