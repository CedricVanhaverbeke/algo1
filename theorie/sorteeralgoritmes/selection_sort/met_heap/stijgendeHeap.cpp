
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

    void vervangWortelelement(T nieuw) {
        if (nieuw > this->vector[0]) {
            this->vector[0] = move(nieuw);
        } else {
            // nieuw element is kleiner, dus het kan de heapvolgorde verstoren
            int volgnr = 0;

            // We gaan kijken of de kinderen een groter element bevatten.
            // Zolang dat zo is gaan we het grootste element naar boven swappen
            // Met zijn ouder
            while (kinderenBevattenGroterElement(volgnr, nieuw)) {
                std::vector<T> kinderen = getKinderen(volgnr);
                T grootste = kinderen[0];
                volgnr = 2 * volgnr + 1;
                if (kinderen.size() == 2) {
                    if (grootste < kinderen[1]) {
                        // Want volgnr is al veranderd
                        volgnr = volgnr + 1;
                        grootste = kinderen[1];
                    }
                }
                std::swap(this->vector[getVolgNrOuder(volgnr)],
                          this->vector[volgnr]);
            }

            // Wanneer de lus afgelopen is kennen we de plaats van het nieuw
            // element
            std::swap(this->vector[volgnr], nieuw);
        }
    }

    bool isEmpty() { return (vector.size() == 0); }

    T verwijderGrootsteElement() {
        T wortel = vector[0];

        // Nu gaan we het laatste element verwijderen
        // Eerst opslaan
        T laatsteElement = vector[vector.size() - 1];
        vector.pop_back();

        vervangWortelelement(laatsteElement);

        return wortel;
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

    // returnt de array van kinderen van een bepaald volgnr
    // Enkel toevoegen aan de kinderen als de size van de array
    // niet overschreden wordt
    vector<T> getKinderen(int volgnr) {
        // De locatie van de kinderen staat in de cursus!
        std::vector<T> kinderen;
        if (2 * volgnr + 1 < this->vector.size()) {
            kinderen.push_back(this->vector[2 * volgnr + 1]);
        }
        if (2 * volgnr + 2 < this->vector.size()) {
            kinderen.push_back(this->vector[2 * volgnr + 2]);
        }
        return kinderen;
    }

    bool kinderenBevattenGroterElement(int volgnr, T nieuw) {
        // Haal kinderen op
        std::vector<T> kinderen = getKinderen(volgnr);

        // Sowieso false als hij geen kinderen meer heeft
        if (kinderen.size() == 0) {
            return false;
        }
        T grootste = kinderen[0];
        if (kinderen.size() == 2) {
            if (grootste < kinderen[1]) {
                grootste = kinderen[1];
            }
        }
        return (nieuw < grootste);
    }

    vector<T> vector;
};