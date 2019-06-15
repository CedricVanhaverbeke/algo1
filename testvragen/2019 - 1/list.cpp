//
// Created by Cedric Vanhaverbeke on 2019-06-15.
//

#include "list.h"
#include <memory>

using std::unique_ptr;

template <class T>
Lijst<T>::Lijst(T element) {
    // Maak een constructor die het eerst element van de lijst instelt
    auto tmp = std::make_unique<Lijstknoop<T>>(element); // Door hier element te schrijven gebruikt je direct de constructor
    (*this) = std::move(tmp);
}

template <class T>
Lijst<T>& Lijst<T>::operator=(Lijstknoopptr<T> other) {
    Lijstknoopptr<T>::operator=(std::move(other)); // Move hier want anders doen we de copy assignment
    return (*this);
}

template<class T>
void Lijst<T>::print() {
    auto loper = this->get();
    while(loper != nullptr){
        std::cout << loper->sleutel << " ";
        loper = loper->volgend.get();
    }
}

template <class T>
void Lijst<T>::voegToe(T element) {
    auto loper = this->get();

    if(loper == nullptr){
        auto nptr = std::make_unique<Lijstknoop<T>>(element);
        (*this) = std::move(nptr);
    } else {
        while(loper->volgend != nullptr){
            loper = loper->volgend.get();
        }

        // We zitten nu bij de laatste knoop
        auto nptr = std::make_unique<Lijstknoop<T>>(element);
        loper->volgend = std::move(nptr); // Move unique pointer
    }
}

template <class T>
bool Lijst<T>::contains(T element){
    auto loper = this->get();
    while(loper != nullptr && loper->sleutel != element){
        loper = loper->volgend.get();
    }

    // ofwel zitten we op het laatste element ofwel hebben we de sleutel gevonden
    if(loper == nullptr){
        return false;
    }
    return true;
}

template <class T>
void Lijst<T>::voegToeNaElement(T na, T element){


    auto loper = this->get();

    // eerst zoeken tot we het element vinden
    while(loper != nullptr && loper->sleutel != na){
        loper = loper->volgend.get();
    }

    // Nu kan in loper ofwel een nullptr zitten ofwel de waarde
    if(loper != nullptr){
        // voeg toe na de waarde
        auto nptr = std::make_unique<Lijstknoop<T>>(element);
        nptr->volgend = move(loper->volgend); // tussenvoegen
        loper->volgend = std::move(nptr);
    }

    // Als de pointer wel de nullptr was dan zit er geen element in
    // de lijst om tussen te voegen
}

template <class T>
void Lijst<T>::opdrachtTest() {

    auto loper = this->get(); // loper maken
        while(loper != nullptr) {
            T huidigElement = loper->sleutel;
            int aantal = 1;

            auto begin = loper; //copy om begin bij te houden

            while (loper->volgend.get() != nullptr && loper->volgend->sleutel == huidigElement) {
                aantal++; // tel het aantal voorkomen
                loper = loper->volgend.get();
            }

            // loper is gestopt op laatste element van de rij elementen
            if (aantal == 1) {
                auto uptr = std::make_unique<Lijstknoop<T>>(huidigElement);
                uptr->volgend = std::move(begin->volgend);
                begin->volgend = std::move(uptr);
            }

            // OPM: dus niets doen wanneer er twee elementen instaan

            if (aantal > 2) {
                // Als we naar de volgende gaan komen we dus op het
                // nieuwe element uit
                begin->volgend->volgend = std::move(loper->volgend); // skip de andere elementen
            }
            loper = begin->volgend->volgend.get(); // loper eentje vooruit zetten
        }
}


