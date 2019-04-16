#include "BinBoom.h"
#include <queue>
#include <stack>
#include <string>
#include <utility>
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
// overschrijven move operator
template <class T>
Binboom<T>& Binboom<T>::operator=(Binknoopptr<T>&& other) {
    Binknoopptr<T>::operator=(move(other));
    return *this;
}

template <class T>
int Binboom<T>::aantalSleutels() const {
    if (!*this)
        return 0;
    else
        return (*this)->links.aantalSleutels() +
               (*this)->rechts.aantalSleutels() + 1;
}

template <class T>
ostream& Binboom<T>::schrijf(ostream& os) {
    if ((*this) != 0) {
        os << "sleutel: " << (*this)->sleutel << " linkerkind: ";
        if ((*this)->links)
            os << (*this)->links->sleutel;
        else
            os << "(geen)";
        os << " rechterkind: ";
        if ((*this)->rechts)
            os << (*this)->rechts->sleutel;
        else
            os << "(geen)";
        os << endl;
        (*this)->links.schrijf(os);
        (*this)->rechts.schrijf(os);
    }
    return os;
}

template <class T>
void Binknoop<T>::changeLeftChild(T sleutel) {
    if (links) {
        links->sleutel = sleutel;
    } else {
        links = std::make_unique<Binknoop<T>>(Binknoop<T>(sleutel));
    }
}
template <class T>
void Binknoop<T>::changeRightChild(T sleutel) {
    if (rechts) {
        rechts->sleutel = sleutel;
    } else {
        rechts = std::make_unique<Binknoop<T>>(Binknoop<T>(sleutel));
    }
}

// Gebruikt de recursieve eigenschappen van een boom
template <class T>
ostream& Binboom<T>::DEZPrintRec(ostream& os) {
    // Als de boom niet de nullptr is
    // preorder, als we dit anders willen draaien we gewoon alles om
    if ((*this)) {
        os << (*this)->sleutel << " ";
        (*this)->links.DEZPrintRec(os);
        (*this)->rechts.DEZPrintRec(os);
    }

    return os;
}

// Deze functie zoekt gaat niet recursief overlopen
// Ze moet dus controleren de hoeveelste keer de knoop
// gepasseerd wordt om de stack op te vullen
// De stack hier is eigenlijk de compile stack bij een recursieve functie
template <class T>
ostream& Binboom<T>::DEZPrint(ostream& os) {
    // Let op: het gaat hier dus over pointers naar knopen
    // de int van het pair slaat op de hoeveelste keer de knoop bekeken wordt
    // door het algoritme.
    stack<pair<Binknoop<T>*, int>> ATW;

    // Zet een pointer op de stack naar de knoop van de wortel
    // De 1 slaat op de eerste keer dat hij bekeken zal worden
    ATW.emplace(make_pair((*this).get(), 1));

    // Zolang de stapel niet leeg is
    while (!ATW.empty()) {
        auto nuKnoop = ATW.top().first;
        int pass = ATW.top().second;  // Hoeveelste keer passeer ik?
        switch (pass) {
            case 1:
                // preorder: we schrijven de knoop uit
                os << nuKnoop->sleutel << " ";
                ATW.top().second++;
                if (nuKnoop->links != nullptr) {
                    ATW.emplace(make_pair(nuKnoop->links.get(), 1));
                }
                break;
            case 2:
                // Hier kunnen we
                // os << nuKnoop->sleutel << " ";
                // schrijven om inorder te werken
                ATW.top().second++;
                if (nuKnoop->rechts != nullptr) {
                    ATW.emplace(make_pair(nuKnoop->rechts.get(), 1));
                }
                break;
            case 3:
                // Hier kunnen we
                // os << nuKnoop->sleutel << " ";
                // schrijven om postorder te werken
                ATW.pop();
        }
    }
    return os;
}

// Deze functie gebruikt een queue
template <class T>
ostream& Binboom<T>::BEZPrint(ostream& os) {
    queue<Binknoop<T>*> ATW;
    ATW.emplace((*this).get());

    while (!ATW.empty()) {
        auto nuKnoop = ATW.front();
        os << nuKnoop->sleutel << " ";
        ATW.pop();

        // verwerkingsstap
        if (nuKnoop->links) {
            ATW.emplace(nuKnoop->links.get());
        }

        if (nuKnoop->rechts) {
            ATW.emplace(nuKnoop->rechts.get());
        }
    }
    return os;
}
