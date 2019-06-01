#include <cassert>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <stack>
#include "RekenData.cpp"
using namespace std;

template <class T>
class Rekenboom;

template <class T>
class Binknoop;

template <class T>
using Binknoopptr = std::unique_ptr<Binknoop<T>>;

template <class T>
class Rekenboom : public Binknoopptr<T> {
   public:
    using Binknoopptr<T>::Binknoopptr;

    friend istream& operator>>(istream& is, Rekenboom<T>& bb) {
        return bb.lees(is);
    }
    friend ostream& operator<<(ostream& os, const Rekenboom<T>& bb) {
        return bb.schrijflevelorder(os);
    }

    void parseFormule(string formule);

    double berekenOplossing();

    // overlead move operator
    Rekenboom& operator=(Binknoopptr<T>&&);

    // schrijf schrijft uit in een vorm die min of meer menselijk leesbaar is
    ostream& schrijf(ostream&);

   private:
    void maakBoom(int, int, vector<pair<std::function<bool(char)>, bool>>&,
                  vector<pair<RekenData, int>>&);
};

template <class T>
class Binknoop {
    friend class Rekenboom<T>;

   public:
    T sleutel;
    Rekenboom<T> links, rechts;
};

template <class T>
ostream& Rekenboom<T>::schrijf(ostream& os) {
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
