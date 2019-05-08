#include <iostream>
#include "getallen.cpp"

using std::cin;
using std::cout;
using std::string;

int main() {
    // Hier doen we voorlopig nog niets mee
    // int n;
    // cout << "Voer een niet te groot positief getal in." << endl;
    // cout << "Ter controle: 14 geeft als somwaarde 43 en 28 geef als somwaarde
    // "
    //        "81"
    //     << endl;
    // cin >> n;
    BacktrackflexGetallen bt(14);
    bt.losOp(true);
}