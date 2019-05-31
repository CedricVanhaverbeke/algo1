#include <cassert>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <stack>
using namespace std;

template <class T>
class Binboom;

template <class T>
class Binknoop;

template <class T>
using Binknoopptr = std::unique_ptr<Binknoop<T> >;

template <class T>
class Binboom : public Binknoopptr<T> {
public:
    using Binknoopptr<T>::Binknoopptr;

    // De inleesoperator sturen we door naar de leesfunctie
    friend istream& operator>>(istream& is, Binboom<T>& bb) {
        return bb.lees(is);
    }
    friend ostream& operator<<(ostream& os, const Binboom<T>& bb) {
        return bb.schrijflevelorder(os);
    }

    // overlead move operator
    Binboom& operator=(Binknoopptr<T>&&);

    // schrijf schrijft uit in een vorm die min of meer menselijk leesbaar is
    ostream& schrijf(ostream&);
    int aantalSleutels() const;
    istream& lees(istream&);
    // schrijflevelorder schrijft uit in een vorm die door lees(...) kan gelezen
    // worden.
    ostream& schrijflevelorder(ostream& os) const;
    void DEbezoek(function<void(T&&)> preorder, function<void(T&&)> inorder,
                  function<void(T&&)> postorder);
    void teken(const char* bestandsnaam);
    string tekenrec(ostream& uit, int& knoopteller);

private:
};

template <class T>
class Binknoop {
    friend class Binboom<T>;

public:
    T sleutel;

private:
    Binboom<T> links, rechts;
};

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

/*template <class T>
void Binboom<T>::teken(const char* bestandsnaam) {
    ofstream uit(bestandsnaam);
    assert(uit);
    int knoopteller = 0;  // knopen moeten een eigen nummer krijgen.
    uit << "digraph {\n";
    this->tekenrec(uit, knoopteller);
    uit << "}";
};
*/

template <class T>
string Binboom<T>::tekenrec(ostream& uit, int& knoopteller) {
    ostringstream wortelstring;
    wortelstring << '"' << ++knoopteller << '"';
    if (!*this) {
        uit << wortelstring.str() << " [shape=point][color=white];\n";
    } else {
        uit << wortelstring.str() << " [label=\"" << (*this)->sleutel << "\"]";
        uit << ";\n";
        string linkskind = (*this)->links.tekenrec(uit, knoopteller);
        ++knoopteller;
        uit << "\"" << knoopteller << "b\""
            << "[label=\"\"][color=white];\n";
        uit << wortelstring.str() << " -> \"" << knoopteller
            << "b\" [color=white];\n";
        if (!(((*this)->links) && ((*this)->rechts)) &&
            (((*this)->links) || ((*this)->rechts))) {
            uit << "\"" << knoopteller << "c\""
                << "[label=\"\"][color=white];\n";
            uit << wortelstring.str() << " -> \"" << knoopteller
                << "c\" [color=white];\n";
        };
        string rechtskind = (*this)->rechts.tekenrec(uit, knoopteller);
        uit << wortelstring.str() << " -> " << linkskind;
        if (!(*this)->links) uit << "[color=white]";
        uit << ";\n";
        uit << wortelstring.str() << " -> " << rechtskind;
        if (!(*this)->rechts) uit << "[color=white]";
        uit << ";\n";
    };
    return wortelstring.str();
};

template <class T>
void Binboom<T>::DEbezoek(function<void(T&&)> preorder,
                          function<void(T&&)> inorder,
                          function<void(T&&)> postorder) {
    stack<pair<Binknoop<T>*, int> > ATW;  // ATW: Af Te Werken
    if ((*this) != 0) {
        ATW.emplace((*this).get(), 1);
        while (!ATW.empty()) {
            Binknoop<T>* nuknoop = ATW.top().first;
            int pass = ATW.top().second;
            ATW.top().second++;
            switch (pass) {
                case 1:
                    preorder(move(nuknoop->sleutel));
                    if (nuknoop->links) ATW.emplace(nuknoop->links.get(), 1);
                    break;
                case 2:
                    inorder(move(nuknoop->sleutel));
                    if (nuknoop->rechts) ATW.emplace(nuknoop->rechts.get(), 1);
                    break;
                case 3:
                    postorder(move(nuknoop->sleutel));
                    ATW.pop();
            }
        };
    };
};