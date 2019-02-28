// testprogramma voor de move- en copy van een een lijst volgens de
// C++17-standaard.
#include <cstdlib>
#include <iostream>
#include <string>
#include "lijst17.cpp"
#include "lijstknoop.cpp"

using std::cerr;
using std::string;
int gemaakt = 0;  // aantallen gemaakte en verwijderde knopen.
int verwijderd = 0;

// Wat volgt is een toepassing;
// deze wordt normaal door de gebruiker geschreven.
// class Lijstknoop:public string{
//    int a;
// public:
//    Lijstknoop(){};
//};
Lijst<int> maak() {
    Lijst<int> l;
    l.voegToe(int(7));
    l.voegToe(int(45));
    l.voegToe(int(15));
    l.voegToe(int(45));
    l.voegToe(int(25));
    l.voegToe(int(35));
    l.voegToe(int(45));
    l.voegToe(int(55));
    gemaakt += 8;
    return l;
};

int main() {
    {
        cerr << "maak met transfer\n";

        // default constructor implementeren voor deze lijn
        Lijst<int> l;
        Lijstknoop<int>::controle(gemaakt, verwijderd);

        // move operator implementeren voor deze lijn, want in maak wordt de
        // gebruikt. Hij gebruikt de standaard move operator om l in te stellen
        // denk ik

        l = maak();
        Lijstknoop<int>::controle(gemaakt, verwijderd);

        std::cout << l << endl;

        Lijstknoop<int>::controle(gemaakt, verwijderd);
        cerr << "verwijderen\n";
        l.verwijder(45);
        verwijderd++;

        // Eerste 45 wordt verwijderd
        std::cout << l << endl;
        l.verwijder(123);

        // 123 zit er niet in dus wordt niet verwijderd
        std::cout << l << endl;

        Lijstknoop<int>::controle(gemaakt, verwijderd);

        for (auto s : l) cerr << s << "\n";
        l.schrijf(cerr);

        // Wat maakt die losse oproep van maak nog uit?
        cerr << "Losse oproep maak\n";
        maak();
        verwijderd += 8;
        Lijstknoop<int>::controle(gemaakt, verwijderd);
        cerr << "maak() in constructor\n";

        std::cout << l << endl;

        Lijst<int> l2(maak());

        Lijstknoop<int>::controle(gemaakt, verwijderd);

        cerr << "duplicaat 1\n";

        l2 = l;

        if (!l2.isClone(l)) throw("copy levert andere lijst op.");
        verwijderd += 8;
        gemaakt += 7;
        Lijstknoop<int>::controle(gemaakt, verwijderd);
        cerr << "duplicaat 2\n";
        l2 = l;
        gemaakt += 7;
        verwijderd += 7;
        Lijstknoop<int>::controle(gemaakt, verwijderd);
        cerr << "duplicaat 3\n";
        l2 = l2;
        Lijstknoop<int>::controle(gemaakt, verwijderd);
        l2.schrijf(cerr);
        cerr << "\n";
        cerr << "duplicaat 4\n";
        Lijst<int> l3;
        l3.voegToe(int(99));
        gemaakt++;
        Lijstknoop<int>::controle(gemaakt, verwijderd);
        l3 = l2 = l;
        verwijderd += 8;
        gemaakt += 14;
        Lijstknoop<int>::controle(gemaakt, verwijderd);
        cerr << "insertion sort\n";
        l2.insertionsort();
        Lijstknoop<int>::controle(gemaakt, verwijderd);
        cerr << "verwijderen\n";
        l.verwijder(45);
        l.verwijder(45);
        l.verwijder(45);
        l.verwijder(45);
        verwijderd += 2;
        Lijstknoop<int>::controle(gemaakt, verwijderd);
        cerr << "swappen\n";
        swap(l2, l);
        Lijstknoop<int>::controle(gemaakt, verwijderd);
        l2.schrijf(cerr);
        cerr << "\n";
    };

    verwijderd += 19;
    Lijstknoop<int>::controle(gemaakt, verwijderd);
    return 0;
}
