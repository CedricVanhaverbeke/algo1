
#include <math.h>
#include <iostream>
#include <vector>
#include "Knoop.cpp"

using namespace std;

template <class T>
class Heap {
   public:
    // default constructor
    Heap(){};

    // Constructor adhv vector
    Heap(vector<T>&);

    // Constructor adhv een array
    Heap(int*);

    // public methodes
    void voegToe(T sleutel) { 
        Knoop<T> knoop(sleutel, this->vector.size());
        vector.push_back(knoop); 
        sorteer_stijgende_heap();
    }

   private:
    friend ostream& operator<<(ostream& os, Heap<T>& heap) {
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
                i++; // niveau verhogen
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

    // nog implementeren
    void sorteer_stijgende_heap() {}

    vector<Knoop<T>> vector;
};