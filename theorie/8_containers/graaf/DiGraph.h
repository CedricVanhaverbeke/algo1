#include <cassert>
#include <cstdlib>
#include <functional>
#include <iomanip>
#include <iostream>
#include <memory>
#include <queue>
#include <sstream>
#include <stack>
#include <vector>
using namespace std;

template <class T>
class DiGraph;

template <class T>
class Node;

template <class T>
using Nodeptr = std::unique_ptr<Node<T>>;

// De implementatie van de DiGraph is met de lijstenvoorstelling
template <class T>
class DiGraph {
   public:
    void addNode(T);
    int getAantalElementen();

    void addNeighbourToNode(int, Node<T>*);

    ostream& DEPrint(ostream&);
    ostream& BEPrint(ostream&);

    friend ostream& operator<<(ostream& os, DiGraph<T>& dg) {
        return dg.schrijf(os);
    }

    vector<Nodeptr<T>> nodes;

   private:
    // nodes in de graaf
    ostream& schrijf(ostream& os);
    void behandel_knoop(Node<T>*, vector<Node<T>*>& ontdekt, ostream& os);
};

template <class T>
class Node {
    friend class DiGraph<T>;

   public:
    // constructor
    Node(T sleutel) : sleutel{sleutel} {}

    void addNeighbour(Node<T>*);

    T sleutel;

    // bevat een lijst van pointers naar de buren
    vector<Node<T>*> neighbours;
};
