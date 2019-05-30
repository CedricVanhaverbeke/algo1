//
// Created by Cedric Vanhaverbeke on 2019-05-30.
//

#include "Binary_Tree.h"

using std::vector;

// Kleine boomstructuur om te testen, gebaseed op 118
template<class T>
void Binary_Tree<T>::maakTestTree(vector<T> & v) {
        this->sleutel = move(std::make_unique<T>(v[0]));
        this->left = std::make_unique<Binary_Tree<T>>();
        this->left->parent = this;

        this->right = std::make_unique<Binary_Tree<T>>();
        this->right->parent = this;

        this->left->sleutel = move(std::make_unique<T>(v[1]));
        this->right->sleutel = move(std::make_unique<T>(v[2]));


        this->left->left =  std::make_unique<Binary_Tree<T>>();
        this->left->left->parent = this->left.get();
        this->left->left->sleutel = move(std::make_unique<T>(v[3]));

        this->right->left = std::make_unique<Binary_Tree<T>>();
        this->right->left->parent = this->right.get();
        this->right->right = std::make_unique<Binary_Tree<T>>();
        this->right->right->parent = this->right.get();

        this->right->left->sleutel = move(std::make_unique<T>(v[4]));
        this->right->right->sleutel = move(std::make_unique<T>(v[5]));
}

// recursieve implementatie van zoeken
template<class T>
bool Binary_Tree<T>::zoekSleutel(T sleutel) {
    bool found = false;
    if(sleutel == *(this->sleutel)){
        return true;
    } else {

        if(sleutel <  *(this->sleutel)){
            if(this->left != nullptr) {
                found = this->left->zoekSleutel(sleutel);
            }
        }

        if(sleutel >  *(this->sleutel)){
            if(this->right != nullptr){
                found = this->right->zoekSleutel(sleutel);
            }
        }
    }
    return found;
}

template<class T>
Binary_Tree<T> * Binary_Tree<T>::findMinimum() {
    Binary_Tree* ptr = this;
    if(this->left == nullptr) {
        return ptr;
    } else {
        ptr = this->left->findMinimum();
    }
    return ptr;
}

template<class T>
Binary_Tree<T> * Binary_Tree<T>::findMaximum() {
    Binary_Tree* ptr = this;
    if(this->right == nullptr) {
        return ptr;
    } else {
        ptr = this->left->findMaximum();
    }
    return ptr;
}

template<class T>
T Binary_Tree<T>::getSleutel() {
    return *(this->sleutel);
}

template<class T>
Binary_Tree<T> * Binary_Tree<T>::getNext() {
    Binary_Tree<T> * ptr = this;

    // Voorbeeld p 118 knoop 25
    if(this->right != nullptr){
        ptr = this->right->findMinimum();
    } else {
        // Voorbeeld p 118 knoop 49
        T teZoeken = this->getSleutel();
        ptr = ptr->parent;
        while (ptr != NULL && ptr->getSleutel() <= teZoeken) {
            ptr = ptr->parent;
        }
    }

    // Checken of we nu effectief een pointer mogen teruggeven
    if(ptr == NULL){
        return NULL;
    }
    return ptr;
}

template<class T>
Binary_Tree<T> *Binary_Tree<T>::getPrevious() {
    auto ptr = this;

    // Voorbeeld p 118 knoop 9
    if(this->left != nullptr){
        ptr =  this->left->findMinimum();
    } else {
        // Voorbeeld p 118 knoop 21
        T teZoeken = ptr->getSleutel();
        ptr = ptr->parent;
        while (ptr != NULL && ptr->getSleutel() <= teZoeken) {
            ptr = ptr->parent;
        }
    }
    // Checken of we nu effectief een pointer mogen teruggeven
    if(ptr == NULL){
        return NULL;
    }
    return ptr;
}
