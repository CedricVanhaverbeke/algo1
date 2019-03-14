#include "sortvector.h"
#include "sorteermethode.h"

template <class T>
void Sortvector<T>::vul_random_zonder_dubbels() {
    vul_range();
    shuffle();
}

// zie wikipedia hier:
// https://en.wikipedia.org/wiki/Fisher%E2%80%93Yates_shuffle
template <class T>
void Sortvector<T>::shuffle() {
    for (int i = this->size() - 1; i >= 1; i--) {
        int random = rand() % (this->size());
        swap((*this)[i], (*this)[random]);
    }
}

template <class T>
void Sortvector<T>::vul_omgekeerd() {
    for (int i = this->size() - 1; i >= 0; i--) {
        // Deze code gebruikt de constructor van T
        auto element = T(i);
        this->operator[](this->size() - i - 1) = move(element);
        // Je zou ook kunnen schrijven this->operator[](this->size() - i - 1) =
        // T(i) want die gebruikt impliciet een move
    }
}

// Vul de vector met elementen van T
template <class T>
void Sortvector<T>::vul_range() {
    for (int i = 0; i < this->size(); i++) {
        // Deze code gebruikt de constructor van T
        auto element = T(i);
        (*this)[i] = move(element);
    }
}

// Overloop tot de helft van de array en swap plaatsen
template <class T>
void Sortvector<T>::draai_om() {
    for (int i = 0; i < this->size() / 2; i++) {
        swap((*this)[i], (*this)[this->size() - i - 1]);
    }
}

// Default constructor
template <class T>
Sortvector<T>::Sortvector(int l) {  // l is lengte
    this->reserve(l);
    for (int i = 0; i < l; i++) {
        // blijkbaar gebruikt hij hier de constructor van T
        this->emplace_back(i);
    }
    shuffle();
};

template <class T>
void Sortvector<T>::schrijf(ostream& os) const {
    for (auto&& t : *this) {
        os << t << " ";
    }
    os << "\n";
}

// Geen return doen in een for-loop. Cnops vindt dat niet leuk
template <class T>
bool Sortvector<T>::is_gesorteerd() const {
    bool gesorteerd = true;
    for (int i = 1; i < this->size(); i++) {
        if (this->operator[](i) < this->operator[](i - 1)) {
            gesorteerd = false;
        }
    }
    return gesorteerd;
}

template <class T>
bool Sortvector<T>::is_range() const {
    bool gesorteerd = true;
    for (int i = 0; i < this->size(); i++) {
        if (this->operator[](i) != i) {
            gesorteerd = false;
        }
    }
    return gesorteerd;
}

template <class T>
int Sortvector<T>::geefaantalinversieskwadratisch() const {
    int aantalInversies = 0;
    for (int i = 0; i < this->size(); i++) {
        for (int j = i + 1; j < this->size(); j++) {
            if (this->operator[](i) > this->operator[](j)) {
                aantalInversies++;
            }
        }
    }
    return aantalInversies;
}