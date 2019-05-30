//
// Created by Cedric Vanhaverbeke on 2019-05-30.
//

#include <memory>

using std::unique_ptr;
using std::shared_ptr;
using std::vector;

// Op voorhand al maken zodat we ernaar kunnen verwijzen
template <class T>
class Binary_Tree;

template <class T>
using treePtr = unique_ptr<Binary_Tree<T>>;

template <class T>
using parentPtr = shared_ptr<Binary_Tree<T>>;


template <class T>
class Binary_Tree {

public:
    T getSleutel();
    bool zoekSleutel(T sleutel);
    Binary_Tree<T> *  findMinimum();
    Binary_Tree<T> * findMaximum();
    Binary_Tree<T> * getNext();
    Binary_Tree<T> * getPrevious();
    void maakTestTree(vector<T> & v);
    treePtr<T> left;
    treePtr<T> right;

private:
    unique_ptr<T> sleutel;

    // Parent pointer is shared omdat er meerdere kinderen naar hem moeten wijzen
    Binary_Tree<T> * parent = NULL;
};
