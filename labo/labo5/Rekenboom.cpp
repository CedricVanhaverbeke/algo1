#include "Rekenboom.h"
#include <ostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::make_pair;
using std::make_unique;
using std::move;
using std::pair;
using std::stoi;
using std::string;
using std::unique_ptr;
using std::vector;

template <class T>
ostream& operator<<(ostream& os, vector<T> v) {
    for (int i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    return os;
}

// overschrijven move operator
template <class T>
Rekenboom<T>& Rekenboom<T>::operator=(Binknoopptr<T>&& other) {
    Binknoopptr<T>::operator=(move(other));
    return *this;
}

template <class T>
void Rekenboom<T>::parseFormule(string formule) {
    vector<pair<RekenData, int>> volgordeVector;
    // Plaats alle karakters in de vector
    int i = 0;
    while (i < formule.length()) {
        RekenData data;
        if (isOperator(formule.at(i))) {
            data.tag = data.CHAR;
            data.operatie = formule.at(i);
            volgordeVector.emplace_back(std::make_pair(data, 0));
            i++;
        } else {
            string getal;
            // Volledig getal proberen uitlezen, zoals bv 10 en niet apart 1 en
            // 0
            while (i < formule.length() && !isOperator(formule.at(i))) {
                getal += formule.at(i);
                i++;
            }
            data.tag = data.DOUBLE;
            data.getal = stoi(getal);  // Het getal erin steken
            volgordeVector.emplace_back(
                std::make_pair(data, -1));  // We steken hier -1 om te tonen dat
                                            // hier geen Volgorde nodig is
        }
    }

    // Bewerkingen gaan we hier in een lijst steken zodat we alle bewerkingen
    // (met hun volgorde van overlopen, van links naar rechts of rechts naar
    // links)
    vector<pair<std::function<bool(char)>, bool>> bewerkingsFuncties;
    // De power functie moet als enige van rechts naar links behandeld worden
    // volgens het internet
    bewerkingsFuncties.emplace_back(make_pair(isPower, false));
    bewerkingsFuncties.emplace_back(make_pair(isTimesDevided, true));
    bewerkingsFuncties.emplace_back(make_pair(isPlusMinus, true));

    maakBoom(0, volgordeVector.size(), bewerkingsFuncties, volgordeVector);
};

template <class T>
void Rekenboom<T>::maakBoom(
    int l, int r, vector<pair<std::function<bool(char)>, bool>>& functies,
    vector<pair<RekenData, int>>& volgorde) {
    // Hier zorg je ervoor dat de RekenData plaats effectief voorzien wordt.
    (*this) = move(make_unique<Binknoop<RekenData>>());

    // Als er zowel haakjes vooraan als achteraan staan in de deelbewerking
    // mogen ze weg, omdat we in de vorige stappen al rekening hebben gehouden
    // met de volgorde van bewerkingen
    if (volgorde[l].first.tag == volgorde[l].first.CHAR &&
        volgorde[r - 1].first.tag == volgorde[r - 1].first.CHAR &&
        isHaak(volgorde[l].first.operatie) &&
        isHaak(volgorde[r - 1].first.operatie)) {
        l += 1;
        r -= 1;
    }

    if (l != r - 1) {
        // plaats resetten, deze variabele dient om de plaats bij te houden
        // van elke operator
        int plaats = 0;

        // Hier overlopen we alle bewerkingen om de volgorde te kennen van de
        // uit te voeren bewerkingen
        for (auto f : functies) {
            geefVolgorde(volgorde, plaats, f.second, f.first);
        }

        // De lijst bevat nu de volgorde voor alle bewerkingen.
        // We gaan op zoek naar de laatste bewerking die uitgevoerd moet worden
        // want die is sowieso de root van de boom
        int maximumIndex = l;
        for (int i = l + 1; i < r; i++) {
            // Enkel doen als het om operatoren gaat en wanneer de volgorde het
            // grootst is
            if (volgorde[i].first.tag == volgorde[i].first.CHAR &&
                volgorde[i].second > volgorde[maximumIndex].second) {
                maximumIndex = i;
            }
        }

        // Nu we de operator gevonden hebben met de grootste volgorde moet deze
        // in de wortel van de boom
        (*this)->sleutel = volgorde[maximumIndex].first;

        // Nu gaan we de overige deelbomen recursief laten genereren
        (*this)->links.maakBoom(l, maximumIndex, functies, volgorde);
        (*this)->rechts.maakBoom(maximumIndex + 1, r, functies, volgorde);

    } else {
        // We zijn aan bladelementen gekomen, bladelementen zijn gewoon getallen
        (*this)->sleutel = volgorde[l].first;
    }
}
