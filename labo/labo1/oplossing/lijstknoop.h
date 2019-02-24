#include "includes.h"

template <class T>
class Lijstknoop {
    friend class Lijst<T>;

   public:
    Lijst<T> volgend;
    Lijstknoop(const T&);

    ~Lijstknoop();

   protected:
    T sleutel;

   public:
    static bool controle(int gemaakt, int verwijderd);

   protected:
    static int aantalGemaakt;
    static int aantalVerwijderd;
};