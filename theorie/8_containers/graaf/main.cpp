#include <stdlib.h>
#include <iostream>
#include "DiGraph.cpp"

void fillDiGraph(int aantal, DiGraph<int>& d) {
    for (int i = 0; i < aantal; i++) {
        d.addNode(i + 1);
    }

    // Voeg een beetje buren toe
    for (int i = 0; i < aantal; i++) {
        for (int j = 0; j < 2; j++) {
            int random = rand() % 10;
            if (random != i) {
                d.addNeighbourToNode(i, d.nodes[random].get());
            }
        }
    }
}

using std::cout;
int main() {
    srand(10);
    DiGraph<int> d;

    fillDiGraph(10, d);
    cout << d;
    cout << endl << endl;

    cout << "Diepte eerst:" << endl;
    d.DEPrint(cout);
    cout << endl;

    cout << "Breedte eerst:" << endl;
    d.BEPrint(cout);

    return 0;
}