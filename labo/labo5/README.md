# Labo 5: Een rekenmachine

In dit labo is het de bedoeling om een binary expression tree te maken. In het begin krijg je een expression in de vorm van een string
zonder spaties. Uiteindelijk willen we iets bekomen zoals op p85 in de cursus

## Stap 0: understanding the struct:

Dit wordt gebruikt wanneer, in dit geval, slechts 1 van de mogelijkheden mogelijk is. Instanties van de structs hebben dus ofwel een getal ofwel een operatie maar nooit een van beide. Deze ‘opties’ worden in een union geplaatst om geheugen te besparen, ze nemen namelijk dezelfde plaats in op die manier. We houden op die manier geen onnodige attributen bij voor de structs.

De enum staat volledig los van de union maar kan gebruikt worden om aan te geven welk type struct we vast hebben. Het oproepen van het gebruikte attribuut in de union gebeurt namelijk als elk ander attribuut van de struct. Indien we een attribuut proberen oproepen dat de struct niet heeft krijgen we fouten. Daarom gebruiken we deze enum als een controle. We roepen dan bv de operatie als volgt op:

```cpp
typedef struct  {
    enum{CHAR, DOUBLE} tag;
    union {
        double getal;
        char operatie;
    };
} RekenData;
```

## Stap 1: Boom bouwen adhv de string

## Deelstap 1: String parsen

Om cijfers en operatoren door elkaar te kunnen houden zijn er enkele zaken in `RekenData.cpp` gemaakt:

```c++
bool isPlusMinus(char teken){
    return teken == '+' || teken == '-';
}

bool isTimesDevided(char teken){
    return teken == '*' || teken == '/';
}

bool isPower(char teken){
    return teken == '^';
}

bool isHaak(char teken){
    return teken == '(' || teken == ')';
}

bool isOperator(char teken){
    return isPlusMinus(teken) || isTimesDevided(teken) || isPower(teken) || isHaak(teken);
}
```

Niet dat het parsen moeilijk moeilijk is, alleen moet je rekening houden dat getallen met meerdere cijfers tesamen moeten gehouden worden.
Deze functionaliteit is volledig geprogrammeerd in `Rekenboom.cpp` in `parseFormule`.

Ik maak hier een volgordevector. Deze bevat een pair van de `RekenData` en zijn int met zijn volgorde. Voorlopig doen we nog niets met de volgorde.

```cpp
template<class T>
void Rekenboom<T>::parseFormule(string formule) {

    vector<pair<RekenData, int>> volgordeVector;
    // Plaats alle karakters in de vector
    int i = 0;
    while(i < formule.length()){
        RekenData data;
        if(isOperator(formule.at(i))){
            data.tag = data.CHAR;
            data.operatie = formule.at(i);
            volgordeVector.emplace_back(std::make_pair(data, 0));
            i++;
        } else {
            string getal;
            // Volledig getal proberen uitlezen, zoals bv 10 en niet apart 1 en 0
            while(i < formule.length() && !isOperator(formule.at(i))){
                getal += formule.at(i);
                i++;
            }
            data.tag = data.DOUBLE;
            data.getal = stoi(getal); // Het getal erin steken
            volgordeVector.emplace_back(std::make_pair(data, -1)); // We steken hier -1 om te tonen dat hier geen
                                                                    // Volgorde nodig is
        }

    }

/// ... WORDT VERVOLGD
```

## Deelstap 2: Volgorde bepalen

De volgende stap is het bepalen van de volgorde van de bewerkingen. Het algoritme is eigenlijk zeer simpel.
(Met stap 3 van intranet) zijn er 5 bewerkingen waar we rekening mee moeten houden.

- en +, \* en / en ^.

De volgorde is gewoon hetzelfde zoals we ze kennen in wiskunde. Eerst willen we ^, daarna \* en / en daarna + en \-.
We gaan per bewerking opzoek naar zijn teken in de formulestring. Dit komt neer op 3 keer overlopen omdat er 3 verschillende
prioriteiten zijn. (+ en - hebben bijvoorbeeld dezelfde prioriteit qua bewerking). We houden een volgorde bij. Bv:

```
4 + 5 + 6

Deze waarden hebben allemaal dezelfde prioriteit, ons algoritme gaat van links naar rechts gaan
om het op te lossen. De eerste plus krijgt dus volgorde 1 en de tweede plus volgorde 2. Dit geldt ook
gewoon nog altijd als we een - erbij betrekken

Hetzelfde kan gezegd worden voor * en /, dit is net hetzelfde als het vb hierboven.

Stel nu dat we ze mengen:
4 + 5 + 6  * 3

De volgorde zou nu eerst de maal moeten zijn. Daarom overlopen we eerst de maal en gedeeld door en daarna pas de plus en minnen.
Opnieuw, als er meerdere tekens zijn van hetzelfde moeten we van links naar rechts kijken

4 ^ 2 ^ 3

Deze situatie is iets anders. In plaats van naar links en rechts willen we deze operator van rechts naar links evalueren, anders klopt onze
rekenmachine niet meer. (check het maar eens)

Het algoritme gaat dus een volgorde (gewoon een cijfertje) geven per operatie. De grootste operatie is altijd de operatie die in de node van de boom
waarmee we nu bezig zijn moet terechtkomen.

Als laatste: wat doen we met haakjes. Haakjes hebben altijd voorrang, ik skip haakjes gewoon altijd volledig in mijn oplossing, tot er een deelbewerking
is waar zowel een haakje helemaal vanvoor en helemaal achteraan staat. Dan kunnen we ze weglaten

EEN UITGEWERKT VB:
10 * 7 + (8-50)

1. Zoeken naar operator met laagste prio
    - * : prio 1
    - + : prio 2
    - haakjes worden geskipt

De wortel van de boom krijgt dus als sleutel +

2. We krijgen nu 2 deelbewerkingen
10 * 7 en (8-50)

3. 10 * 7
    - zelfde systeem, maal wordt de nodesleutel
    - deelbomen zijn 10 en 7
    - omdat dit gewoon getallen zijn kunnen we ze rechtstreeks als linker- en rechterkind opnemen

4. (8-50)
    - haakjes staan helemaal vooraan en helemaal achteraan
    - we kunnen ze weglaten
    - zelfde principe

==> Dit algoritme kunnen we dus recursief maken
```

Om makkelijk bewerking per bewerking te kunnen checken heb ik een vector gemaakt met alle bewerkingsfuncties van hierboven, met als extra zaak
of ze van links naar rechts moeten gecontroleerd worden of van rechts naar links (true = links->rechts, false = rechts->links)

```cpp
vector<pair<std::function<bool(char)>, bool>> bewerkingsFuncties;

bewerkingsFuncties.emplace_back(make_pair(isPower, false));
bewerkingsFuncties.emplace_back(make_pair(isTimesDevided, true));
bewerkingsFuncties.emplace_back(make_pair(isPlusMinus, true));
```

Daarna maken we de boom

```cpp
maakBoom(0, volgordeVector.size(), bewerkingsFuncties, volgordeVector);
```

Deze functie gaat dus recursief alle deelbomen gaan maken:

```cpp
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
```

## Stap 2: Berekenen van de waarde in de boom

Dit kan opnieuw recursief met volgende functie

```cpp
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
```

## Stap 3: ^

Als je deze operator wil laten werken moet je juist nog zorgen dat hij ook bij operator gedefinieerd is, want in Cnops zijn origineel bestand
staat hij niet

```cpp
// operator.h

#include <cassert>
#include <vector>
#include <math.h>
using std::vector;

vector<pair<char,std::function<double(double,double)>>> bewerking={
        {'+',[](double a,double b)->double{
            return a + b;
        }},
        {'-',[](double a,double b)->double{
            return a - b;
        }},
        {'/',[](double a,double b)->double{
            return a / b;
        }},
        {'*',[](double a,double b)->double{
            return a * b;
        }},
        {'^',[](double a,double b)->double{
            return pow(a, b);
        }}
};

```
