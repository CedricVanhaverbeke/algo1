#include "DiGraph.h"
#include <iomanip>
#include <memory>
#include <queue>
#include <vector>

using std::endl;
using std::make_pair;
using std::make_unique;
using std::pair;
using std::setw;

template <class T>
ostream& DiGraph<T>::schrijf(ostream& os) {
    for (int i = 0; i < nodes.size(); i++) {
        os << setw(2) << nodes[i]->sleutel << ": ";
        for (int j = 0; j < nodes[i]->neighbours.size(); j++) {
            os << nodes[i]->neighbours[j]->sleutel << " ";
        }
        os << endl;
    }

    return os;
}

template <class T>
void DiGraph<T>::addNode(T sleutel) {
    nodes.push_back(make_unique<Node<T>>(Node(sleutel)));
}

template <class T>
void Node<T>::addNeighbour(Node<T>* p) {
    neighbours.push_back(p);
}

template <class T>
void DiGraph<T>::addNeighbourToNode(int index, Node<T>* p) {
    nodes[index]->addNeighbour(p);
}

template <class T>
int DiGraph<T>::getAantalElementen() {
    return nodes.size();
}

template <class T>
void DiGraph<T>::behandel_knoop(Node<T>* p, vector<Node<T>*>& ontdekt,
                                ostream& os) {
    ontdekt.push_back(p);     // De knoop wordt als ontdekt gemarkeerd
    os << p->sleutel << " ";  // Hier gaan we de knoop effectief printen
    for (int i = 0; i < p->neighbours.size(); i++) {
        auto np = p->neighbours[i];  // Dit is de te zoeken npointer
        bool alOntdekt = false;
        for (int j = 0; j < ontdekt.size(); j++) {
            if (ontdekt[j] == np) {
                alOntdekt = true;
            }
        }
        if (!alOntdekt) {
            behandel_knoop(np, ontdekt, os);
        }
    }
}

template <class T>
ostream& DiGraph<T>::DEPrint(ostream& os) {
    vector<Node<T>*> ontdekt;

    for (int i = 0; i < getAantalElementen(); i++) {
        auto p = nodes[i].get();  // Dit is de te zoeken pointer
        // Checken of hij al ontdekt was
        bool alOntdekt = false;
        for (int j = 0; j < ontdekt.size(); j++) {
            if (ontdekt[j] == p) {
                alOntdekt = true;
            }
        }
        if (!alOntdekt) {
            behandel_knoop(p, ontdekt, os);
        }
    }

    return os;
}

// Hier wordt opnieuw gebruik gemaakt van
// een queue
template <class T>
ostream& DiGraph<T>::BEPrint(ostream& os) {
    queue<Node<T>*> ATW;          // queue om de volgorde te bepalen
    vector<Node<T>*> ontdekt;     // ontdekte knopen
    auto start = nodes[1].get();  // krijg de startpositie, hier 2
    ATW.emplace(start);
    while (!ATW.empty()) {
        auto p = ATW.front();
        os << p->sleutel << " ";
        ATW.pop();
        // voeg alle buren toe aan de queue die nog niet gezien zijn
        for (int i = 0; i < p->neighbours.size(); i++) {
            auto np = p->neighbours[i];  // Dit is de te zoeken npointer
            bool alOntdekt = false;
            for (int j = 0; j < ontdekt.size(); j++) {
                if (ontdekt[j] == np) {
                    alOntdekt = true;
                }
            }
            if (!alOntdekt) {
                ATW.emplace(np);
                ontdekt.push_back(np);
            }
        }
    }
    return os;
}