// Implementatie voor de lijst

#include "lijst17.h"

// Copy constructor
// is volgens mij basically hetzelfde als de copy assignment operator
// Een copy constructor returnt ook niets
template <class T>
Lijst<T>::Lijst(const Lijst<T>& other) {
    auto tmp = std::make_unique<Lijstknoop<T>>(other->sleutel);
    (*this) = std::move(tmp);
    this->get()->volgend = other->volgend;
}

// assignment operator
// In this zit nu het linkerlid
template <class T>
Lijst<T>& Lijst<T>::operator=(const Lijst<T>& other) {
    // Als de lijsten naar hetzelfde pointen
    if (other == *this) {
        return *this;
    }

    // We gaan enkel de eerste knoop kopiëren
    // Zodat het begin van de lijst wel verschillend
    // is maar de rest niet
    if (other.get() != nullptr) {
        auto tmp = std::make_unique<Lijstknoop<T>>(other->sleutel);
        (*this) = std::move(tmp);
        this->get()->volgend = other->volgend;
    }

    return *this;
}

template <class T>
ostream& operator<<(ostream& os, const Lijst<T>& l) {
    if (l.get()) {
        os << l.get()->sleutel << ", ";
        os << l.get()->volgend;
    }
    return os;
}

template <class T>
void Lijst<T>::schrijf(ostream& os) const {
    if (this->get() != 0) {
        os << this->get()->sleutel;
        std::for_each(++begin(), end(),
                      [&](const T& sleutel) { os << " . " << sleutel; });
    }
}

// oplossing:

// Default constructor gebruikt de constructor van een lijstknooppointer
template <class T>
Lijst<T>::Lijst() : Lijstknoopptr<T>(){};

// Move operator overloaden
template <class T>
Lijst<T>& Lijst<T>::operator=(Lijstknoopptr<T>&& other) {
    // Not sure wat deze lijn doet
    // Je roept de move operator op van lijstknoopptr, wat gewoon een unique
    // pointer is, en dan doe je nog eens die move, maar waarom moet dat?
    // Je zou verwachten dat je gewoon other kan schrijven vind ik.
    // Dat gaat dus niet. Waarom move(other) ? Omdat je een && meekrijgt?
    Lijstknoopptr<T>::operator=(move(other));
    return *this;
}

template <class T>
bool Lijst<T>::isClone(const Lijst<T>& ander) const {
    const Lijst<T>*l1 = this, *l2 = &ander;  // twee lopers
    while (*l1 && *l2 && (*l1)->sleutel == (*l2)->sleutel) {
        l1 = &((*l1)->volgend);
        l2 = &((*l2)->volgend);
    };
    return (!(*l1) && !(*l2));
};

template <class T>
const Lijst<T>* Lijst<T>::zoek(const T& sleutel) const {
    const Lijst<T>* pl = this;
    while (*pl && pl->get()->sleutel != sleutel) pl = &(pl->get()->volgend);
    return pl;
}

template <class T>
int Lijst<T>::geefAantal(const T& sleutel) const {
    int aantal = 0;
    const Lijst<T>* pl = this;
    while (*pl) {
        if ((sleutel = (*pl)->sleutel)) ++aantal;
        pl = &(pl->get()->volgend);
    };
    return aantal;
};

template <class T>
int Lijst<T>::geefAantal() const {
    int aantal = 0;
    const Lijst<T>* pl = this;
    while (*pl) {
        ++aantal;
        pl = &(pl->get()->volgend);
    };
    return aantal;
};

template <class T>
Lijst<T>* Lijst<T>::zoek(const T& sleutel) {
    Lijst* pl = this;
    while (*pl && pl->get()->sleutel != sleutel) pl = &(pl->get()->volgend);
    return pl;
}

/**
 * Initieel bevat de eerste knoop geen waarde, en dus ook geen volgend
 * Lijstknoop object
 *
 * Wanneer we een knoop toevoegen met een bepaalde waarde (de sleutel), dan
 * maken we eerst een nieuwe Lijstknoop aan. Deze nieuwe lijstknoop heeft nu een
 * attribuut sleutel met de waarde, en waarbij 'volgend' op null staat.
 *
 * Nu willen we deze 2 knopen aan elkaar gaan linken (linked list, jwz)
 *
 * L = Lijst, A = Lijstknoop, B = Lijstknoop
 *
 * Lijst -> A
 * A { sleutel: 0, volgend: nullptr_1 }
 * B { sleutel: X, volgend: nullptr_2 }
 *
 * De volgend van het nieuwe object moet wijzen naar het huidige object.
 * Lijst->swap(B->volgend) Lijst bevat momenteel A. Wanneer we een swap doen,
 * dan gaan we B->volgend gaan wisselen met A in de Lijst:
 *
 * Lijst -> nullptr_2
 * A { sleutel: 0, volgend: nullptr_1 }
 * B { sleutel: X, volgend: A }
 *
 * Daarna gaan we B gelijk stellen aan A. *this = B. Echter kan dit niet zomaar.
 * *this is een Lijst, B is een Lijstknoop Daarom dat we volgende overloading
 * hebben moeten definiëren: Lijst operator=(Lijstknoopptr<T> other)
 *
 * Het resultaat:
 * Lijst -> B
 * A { sleutel: 0, volgend: nullptr_1 }
 * B { sleutel: X, volgend: A }
 */
template <class T>
void Lijst<T>::voegToe(const T& sleutel) {
    Lijstknoopptr<T> nieuw = std::make_unique<Lijstknoop<T>>(sleutel);

    // Deze code is identiek aan de volgende lijn code
    // Lijstknoopptr<T>::swap(nieuw->volgend);
    // Aangezien een Lijst eigenlijk gewoon een lijstknoopptr is zou dit ook
    // moeten lukken

    // We zorgen dat de volgende van de nieuwe wijst naar het begin van de lijst
    this->swap(nieuw->volgend);

    // Het begin van de lijst verplaatsen we nu naar nieuw. Aangezien de
    // rest bij volgende staat is de nieuwe knoop nu dus vooraan ingevoegd

    // We moeten dus een move operator schrijven met een lijstknoopptr als
    // argument
    *this = std::move(nieuw);
}

template <class T>
void Lijst<T>::verwijderEerste() {
    if (this->get() != 0) {
        Lijstknoopptr<T> staart(std::move(this->get()->volgend));
        this->reset();
        Lijstknoopptr<T>::swap(staart);
    }
}

template <class T>
void Lijst<T>::verwijder(const T& sleutel) {
    zoek(sleutel)->verwijderEerste();
}

template <class T>
Lijst<T>* Lijst<T>::zoekGesorteerd(const T& sleutel) {
    Lijst* plaats = this;
    while (*plaats && plaats->get()->sleutel < sleutel)
        plaats = &plaats->get()->volgend;
    return plaats;
};

template <class T>
void Lijst<T>::insertionsort() {
    Lijstknoopptr<T> ongesorteerd = std::move(*this);
    while (ongesorteerd) {
        Lijst* plaats = zoekGesorteerd(ongesorteerd.get()->sleutel);
        Lijstknoopptr<T> dummy = std::move(ongesorteerd);
        // vermits ongesorteerd een nullpointer is, is het equivalent van
        // volgende lijnen ongeveer
        // ongesorteerd=std::move(dummy.get()->volgend);
        // std::swap(*plaats,dummy.get()->volgend);
        std::swap(ongesorteerd, dummy.get()->volgend);
        dummy.get()->volgend = std::move(*plaats);
        *plaats = std::move(dummy);
    };
};

template <class T>
void Lijst<T>::teken(const char* bestandsnaam) const {
    ofstream uit(bestandsnaam);
    assert(uit);
    uit << "digraph "
           "{\nrankdir=\"LR\";\n\"0\"[label=\"\",shape=diamond];\n\"0\" -> "
           "\"1\";\n";
    int knoopteller = 1;  // knopen moeten een eigen nummer krijgen.
    const Lijst<T>* loper = this;
    while (*loper) {
        uit << "subgraph cluster_" << knoopteller << " {\nrankdir=\"LR\";\n";
        uit << "\"" << knoopteller << "\" [label=\"" << (*loper)->sleutel
            << "\",color=white];\n";
        uit << "\"" << knoopteller << "v\" [shape=diamond,label=\"\"];\n";
        uit << "\"" << knoopteller << "\" -> \"" << knoopteller
            << "v\" [color=white];\n";

        uit << "}\n";
        uit << "\"" << knoopteller << "v\" -> \"" << knoopteller + 1
            << "\" [lhead=cluster_" << knoopteller << " ltail=cluster_"
            << knoopteller + 1 << "];\n";
        loper = &((*loper)->volgend);
        knoopteller++;
    };
    uit << "\"" << knoopteller << "\" [shape=point];\n";
    uit << "}";
};
