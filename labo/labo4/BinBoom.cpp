#include "BinBoom.h"
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::make_unique;
using std::move;
using std::pair;
using std::string;
using std::unique_ptr;
using std::vector;

// overschrijven move operator
template <class T>
Binboom<T>& Binboom<T>::operator=(Binknoopptr<T>&& other) {
    Binknoopptr<T>::operator=(move(other));
    return *this;
}

template <class T>
istream& Binboom<T>::lees(istream& is) {
    int linkerkind;
    int rechterkind;
    int aantal;

    is >> aantal;

    vector<Binboom<T>> knopen(aantal);

    vector<unique_ptr<Binboom<T>>> pointers(aantal);

    // Vullen met knopen
    for (int i = 0; i < aantal; i++) {
        knopen[i] = make_unique<Binknoop<T>>();

    }

    for (int i = 0; i < aantal; i++) {
        // sleutels instellen
        is >> knopen[i]->sleutel >> linkerkind >> rechterkind;

        // Probleem is nu om de kinderen in te stellen
        // als we knopen[i] = move(...) schrijven dan is de sleutel op plaats i
        // verdwenen en kunnen we geen kinderen meer instellen.
        if (linkerkind > -1) {
            // Kind toevoegen maar dit werkt niet want sommige
            // kinderen staan niet meer in de lijst
        }
        

        if (rechterkind > -1) {
            // Kind toevoegen maar dit werkt niet
            // want kinderen staan niet meer in de lijst
        }
    }

    // Zoek naar wortel
    // Nu nog niet gedaan omdat dit gaat
    // Afhangen van implementatie
    // wortel is 4
    *this = move(knopen[4]);

    return is;
}