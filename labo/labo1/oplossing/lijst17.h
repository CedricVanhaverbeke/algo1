// C++17-compatibele lijst. Ontbrekende elementen: move en copy, iterator
#include "includes.h"

using std::endl;
using std::ofstream;
using std::ostream;
using std::string;

// Moet er staan om de << en >> operator te kunnen implementeren
// Als een friend functie
template <class T>
ostream& operator<<(ostream& os, const Lijst<T>& l);

template <class T>
class Lijst : private Lijstknoopptr<T> {
   public:
    // Copy constructor
    Lijst(const Lijst&);

    // assignment operator
    Lijst& operator=(const Lijst&);

    // Move operator met een lijstknoopptr
    Lijst& operator=(Lijstknoopptr<T>&&);

    // Move operator met een lijst
    Lijst& operator=(Lijst&&);

    // Move constructor
    Lijst(Lijst&&);

    // Default constructor
    Lijst();

    void voegToe(const T&);

    // geefaantal geeft het aantal keer dat de sleutel voorkomt.
    // gebruikt de zoekfunctie om door de lijst te lopen!
    // zonder argument: geef lengte lijst
    int geefAantal(const T&) const;
    void teken(const char* bestandsnaam) const;
    int geefAantal() const;

    // verwijder verwijdert slechts het eerste exemplaar met de gegeven
    // T, en geeft geen fout als de T niet gevonden wordt.
    // gebruik de zoekfunctie om door de lijst te lopen!
    void verwijder(const T&);

    // verwijder eerste knoop.
    void verwijderEerste();

    void insertionsort();

    bool isClone(const Lijst<T>&) const;

    // uitschrijven: voor elke knoop de T-waarde, gescheiden door komma's
    // Als je ook de >> operator wil implementeren kan je operator<<>> schrijven
    friend ostream& operator<<(ostream& os, const Lijst& l);

   public:
    void schrijf(ostream& os) const;

    // iterator; gaat ervan uit dat alles const is
   public:
    class iterator {
       public:
        iterator(Lijstknoop<T>* l = 0) : huidig(l) {}
        const T& operator*() const;
        const iterator& operator++();
        bool operator!=(const iterator& i);

       private:
        // Anders kan je niet bijhouden bij welke lijstknoop je zit
        Lijstknoop<T>* huidig;
    };
    iterator begin() const;
    iterator end() const;

   protected:
    // zoek geeft een pointer naar de Lijst die de sleutelwaarde bevat,
    // en geeft een pointer naar de lege lijst op het einde als de sleutel niet
    // voorkomt.
    const Lijst* zoek(const T&) const;

    Lijst* zoek(const T&);
    // preconditie zoekgesorteerd: lijst is gesorteerd
    // teruggeefwaarde: wijst naar Lijst waar sleutel staat/zou moeten staan.

    Lijst<T>* zoekGesorteerd(const T& sleutel);
};

// Niet de waaren vergelijken, wel de lijstknopen zelf
template <class T>
bool Lijst<T>::iterator::operator!=(const iterator& other) {
    return (this->huidig != other.huidig);
}

// Naar het volgende element gaan
template <class T>
const typename Lijst<T>::iterator& Lijst<T>::iterator::operator++() {
    if (this->huidig) {
        this->huidig = this->huidig->volgend.get();
    }
    return *this;
}

// De dereferentie-operator
template <class T>
const T& Lijst<T>::iterator::operator*() const {
    return this->huidig->sleutel;
}

// Code voor de iterator
// begin en end zijn eigenlijk functies van de lijst. Daarom dat this een lijst
// teruggeeft
template <class T>
typename Lijst<T>::iterator Lijst<T>::begin() const {
    // this is hier de lijst
    // this = De lijst = Lijstknooppointer
    // this-> = Lijstknoop
    // this->get() = de waarde van de lijstknoop
    return iterator(this->get());
}

template <class T>
typename Lijst<T>::iterator Lijst<T>::end() const {
    // Een gelinkte lijst eindigt op een nullpointer.
    return nullptr;
}