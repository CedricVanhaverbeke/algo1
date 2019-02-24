#include "lijstknoop.h"

template <class T>
int Lijstknoop<T>::aantalGemaakt = 0;
template <class T>
int Lijstknoop<T>::aantalVerwijderd = 0;

template <class T>
Lijstknoop<T>::Lijstknoop(const T& _sl) : sleutel(_sl) {
    //    std::cerr<<"Knoop met sleutel "<<sleutel<<" wordt gemaakt\n";
    aantalGemaakt++;
}

template <class T>
Lijstknoop<T>::~Lijstknoop() {
    //    std::cerr<<"Knoop met sleutel "<<sleutel<<" wordt verwijderd\n";
    aantalVerwijderd++;
}

template <class T>
bool Lijstknoop<T>::controle(int gemaakt, int verwijderd) {
    if (aantalGemaakt == gemaakt && aantalVerwijderd == verwijderd)
        return true;
    else {
        std::cerr << "Fout bij controle:\n";
        std::cerr << "Aantal gemaakte knopen   : " << aantalGemaakt
                  << " (moet zijn: " << gemaakt << ")\n";
        std::cerr << "Aantal verwijderde knopen: " << aantalVerwijderd
                  << " (moet zijn: " << verwijderd << ")\n";
        throw "Mislukte controle";
    };
};