#include "Binboom.h"
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
    vector<unique_ptr<Binknoop<T>> * > ptrs(aantal);
    vector<pair<int, int>> kinderen(aantal);

    for (int i = 0; i < aantal; i++) {
        // Als je een lijst maakt met unique pointers is het niet genoeg
        knopen[i] = move(make_unique<Binknoop<T>>());
    }

    // Nadat alle adressen opgehaald zijn kunnen we de kinderen linken
    for (int i = 0; i < aantal; i++) {
        // Alle pointers vullen
        is >> knopen[i]->sleutel >> linkerkind >> rechterkind;

        // Pointers naar de unique pointers maken
        ptrs[i] = &knopen[i];

        // Per index hou je hier de kinderen bij
        kinderen[i] = make_pair(linkerkind, rechterkind);
    }

    // Nu gaan we de unique pointers in de eerste lijst gaan verplaatsen
    // Vanaf we ze toevoegen als kinderen gaan ze dus weg zijn
    // Daarom gaan we de tweede lijst gebruiken
    for(int i = 0; i < aantal; i++){
        if(kinderen[i].first != -1){
            (*(ptrs[i]))->links = move(*(ptrs[kinderen[i].first]));

            // Als je de pointer van het linkerkind verplaatst moet je die dus wel
            // opnieuw instellen
            ptrs[kinderen[i].first] = &((*(ptrs[i]))->links);

        }
        if(kinderen[i].second != -1){
            (*(ptrs[i]))->rechts = move(*(ptrs[kinderen[i].second]));
            ptrs[kinderen[i].second] = &((*(ptrs[i]))->rechts);
        }
    }

    // Nu zou de enige pointer die niet verplaatst is in de originele array de
    // root van de boom moeten zijn
    int i = 0;
    // Hier lopen we verder tot we de root gevonden hebben
    while(knopen[i] == nullptr){i++;}

    // root moven naar de binboom
    *this = move(knopen[i]);

    return is;
}