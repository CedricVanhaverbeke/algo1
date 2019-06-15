#include <iostream>
#include "list.cpp"
#include "testOpdracht.cpp"

using std::cout;

int main() {
    Lijst<int> l;

    // toevoegen testen
    l.voegToe(1);
    l.voegToe(2);
    l.voegToe(2);
    l.voegToe(2);
    l.voegToe(2);
    l.voegToe(5);
    l.voegToe(5);
    l.voegToe(6);
    l.voegToe(6);
    l.voegToe(6);



    l.print();

    std::cout << std::endl;

    l.opdrachtTest();

    l.print();



    return 0;
}