
#include <math.h>
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Heap {
   public:
    // default constructor
    Heap(){};

    // Constructor adhv vector
    Heap(vector<T> v) {
        for (auto i : v) {
            voegToe(i);
        }
    }

    // public methodes
    void voegToe(T sleutel) {
        this->vector.push_back(sleutel);
        sorteer_stijgende_heap();
    }

   private:
    friend ostream& operator<<(ostream& os, Heap<T>& heap) {
        os << "Print vector:" << endl;
        for (int i = 0; i < heap.vector.size(); i++) {
            os << heap.vector[i] << " ";
        }

        os << endl << endl;
        os << "Print bijhorende heap" << endl;
        if (heap.vector.size() > 1) {
            int i = 0;

            // Loopt de lijst door, door te kijken naar het aantal niveaus
            while (i <= log2(heap.vector.size())) {
                // Het begin van het i'de niveau
                int begin = pow(2, i) - 1;

                // Het einde van het i'de niveau
                int einde = 2 * begin;

                // j gaat effectief van begin tot einde printen
                int j = 0;
                for (j = begin; j <= einde && j < heap.vector.size(); j++) {
                    os << heap.vector[j] << " ";
                }

                os << endl;
                i++;  // niveau verhogen
            }
            return os;
        }

        else if (heap.vector.size() == 1) {
            os << heap.vector[0];
        } else if (heap.vector.size() == 0) {
            os << "heap is leeg";
        }
        return os;
    }

    int getVolgNrOuder(int volgnr) {
        // Als we bij de root zitten
        if (volgnr == 0) {
            return -1;
        }

        return ((volgnr - 1) / 2);
    }

    void sorteer_stijgende_heap() {
        int volgnr = this->vector.size() - 1;
        while (volgnr > 0 && this->vector[volgnr] >
                                 this->vector[this->getVolgNrOuder(volgnr)]) {
            // knoop wisselen
            swap(this->vector[volgnr],
                 this->vector[this->getVolgNrOuder(volgnr)]);

            volgnr = this->getVolgNrOuder(volgnr);
        }
    }

    vector<T> vector;
};