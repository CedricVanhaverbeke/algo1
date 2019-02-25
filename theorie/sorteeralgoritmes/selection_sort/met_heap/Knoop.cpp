#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Knoop {
   public:
    // default constructor
    Knoop() {}
    // Knoop initialiseren met zijn sleutel
    Knoop(T sl, int volgnr) : sleutel(sl), volgnr(volgnr) {}

    int getVolgNrOuder() {

        // Als we bij de root zitten
        if(this->volgnr == 0){
            return -1;
        }

        return ((this->volgnr - 1) / 2);
    }



   private:
    friend ostream& operator<<(ostream& os, Knoop<T>& knoop) {
        os << knoop.sleutel << "(" << knoop.volgnr << ")" << "met ouder met index " << knoop.getVolgNrOuder() << "       ";
        return os;
    }

    T sleutel = -1;
    int volgnr = -1;
};