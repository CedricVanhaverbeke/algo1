//
// Created by Cedric Vanhaverbeke on 2019-06-15.
//
#include <memory>
#include <iostream>


using std::unique_ptr;
using std::ostream;

template <class T>
class Lijstknoop;

template<class T>
using Lijstknoopptr = unique_ptr<Lijstknoop<T>>;

template <class T>
class Lijst: public Lijstknoopptr<T> {
public:
    Lijst() = default;
    Lijst(T);

    Lijst& operator=(Lijstknoopptr<T>); // move operator voor een Lijstknoopptr
    void print();
    void voegToe(T element);
    bool contains(T element);
    void voegToeNaElement(T na, T element);

    // Opdracht van de test:
    // Een gelinkte lijst is stijgend gesorteerd
    // Zorg dat er van elk element twee knopen zijn
    // Drie gevallen dus:
    // 1) Ofwel is er 1 element: we moeten een knoop bijmaken
    // 2) Ofwel zijn er 2: We moeten geen knoop bijmaken
    // 3) Ofwel zijn er meer dan 2: We moeten knopen verwijderen
    void opdrachtTest();


};

template <class T>
class Lijstknoop {
public:
    Lijstknoop<T>(T sleutel): sleutel{sleutel} {};

    Lijst<T> volgend;
public:
    T sleutel;
};
