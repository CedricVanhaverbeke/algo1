#include "BinBoom.h"
#include <ostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::make_pair;
using std::make_unique;
using std::move;
using std::pair;
using std::string;
using std::unique_ptr;
using std::vector;

template <class T>
ostream& operator<<(ostream& os, vector<T> v) {
    for (int i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    return os;
}

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

    vector<unique_ptr<Binknoop<T>>> knopen(aantal);
    vector<pair<int, int>> kinderen(aantal);

    for (int i = 0; i < aantal; i++) {
        knopen[i] = move(make_unique<Binknoop<T>>());
    }

    // Nadat alle adressen opgehaald zijn kunnen we de kinderen linken
    for (int i = 0; i < aantal; i++) {
        // Alle pointers vullen
        is >> knopen[i]->sleutel >> linkerkind >> rechterkind;
        kinderen[i] = make_pair(linkerkind, rechterkind);
    }

    int knopenBezocht = aantal;
    int wortelIndex = -1;
    while (knopenBezocht > 0) {
        // knopen zonder kinderen vinden
        vector<int> geenKinderen;
        for (int i = 0; i < aantal; i++) {
            if (kinderen[i].first == -1 && kinderen[i].second == -1) {
                geenKinderen.push_back(i);
                kinderen[i].first = -2;
                kinderen[i].second = -2;
            }
        }

        // Nu bottom up werken zodat de kinderen in de boom terechtkomen

        // Zoeken naar ouders die die kinderen hebben
        for (int index : geenKinderen) {
            for (int j = 0; j < aantal; j++) {
                if (kinderen[j].first == index) {
                    knopen[j]->links = move(knopen[index]);
                    kinderen[j].first =
                        -1;  // Doen alsof ze geen kind meer hebben
                }
                if (kinderen[j].second == index) {
                    knopen[j]->rechts = move(knopen[index]);
                    kinderen[j].second =
                        -1;  // Doen alsof ze geen kind meer hebben
                }
            }
        }

        // Als er nog 1 knoop overblijft weten we dat het de wortel is
        if (knopenBezocht == 1) {
            wortelIndex = geenKinderen[0];
        }
        knopenBezocht -= geenKinderen.size();
        geenKinderen.clear();
    }

    (*this) = move(knopen[wortelIndex]);

    return is;
}