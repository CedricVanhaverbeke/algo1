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
using Binknoopptr = std::unique_ptr<Binknoop<T>>;

template <class T>
class Binboom : public Binknoopptr<T> {
   public:
    using Binknoopptr<T>::Binknoopptr;

    Binboom(T sleutel) {
        (*this) = std::make_unique<Binknoop<T>>(Binknoop<T>(sleutel));
    }

    friend ostream& operator<<(ostream& os, Binboom<T>& bb) {
        return bb.schrijf(os);
    }

    // Maakt een binboom van n niveau's
    Binboom<T>& maakBinBoom();

    // overlead move operator
    Binboom& operator=(Binknoopptr<T>&&);

    // schrijf schrijft uit in een vorm die min of meer menselijk leesbaar is
    ostream& schrijf(ostream&);
    int aantalSleutels() const;

    // Diepte eerst recursief printen
    ostream& DEZPrintRec(ostream& os);

    // Niet recursieve versie
    ostream& DEZPrint(ostream& os);

    // Deze kan niet recursief werken
    ostream& BEZPrint(ostream& os);
};

template <class T>
class Binknoop {
    friend class Binboom<T>;

   public:
    T sleutel;
    Binknoop() = delete;
    Binknoop(T sleutel) : sleutel{sleutel} {}
    void changeLeftChild(T sleutel);
    void changeRightChild(T sleutel);

   public:
    Binboom<T> links, rechts;
};
