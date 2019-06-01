#include <iostream>
#include "Rekenboom.cpp"
#include "operator.h"
#include <memory>


using std::cin;
using std::cout;
using std::make_unique;
using std::unique_ptr;

// Gestolen van Tim zijn samenvatting
double berekenUitkomst(Rekenboom<RekenData> &boom){

    // Als de sleutel een double bevat mogen we
    // gewoon deze waarde teruggeven
    if(boom->sleutel.tag == boom->sleutel.DOUBLE){
        return boom->sleutel.getal;
    }

    // Anders moeten we de berekening maken van de boom
    // met zijn linker en rechtertak
    int prior = 0;
    switch (boom->sleutel.operatie) {
        case '+': prior = 0; break;
        case '-': prior = 1; break;
        case '/': prior = 2; break;
        case '*': prior = 3; break;
        case '^': prior = 4; break;
    }

    pair<char, function<double (double, double)>> paar = bewerking.at(prior);
    return paar.second(berekenUitkomst(boom->links), berekenUitkomst(boom->rechts));
}


int main() {
    // Boom maken
    Rekenboom<RekenData> b;
    //b = move(make_unique<Binknoop<RekenData>>());

    // Inlezen van de formule
    // note: we gaan ervanuit dat de formule in 1 stuk geschreven wordt
    string formule;
    cin >> formule;

    b.parseFormule(formule);

    // test de output van de boom eens
    b.schrijf(cout);
    cout << berekenUitkomst(b);


    return 0;
}