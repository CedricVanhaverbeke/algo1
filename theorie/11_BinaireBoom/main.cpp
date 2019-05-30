#include <iostream>
#include "Binary_Tree.cpp"
#include <vector>

int main() {
    Binary_Tree<int> tree;
    std::vector<int> v = {25, 9, 40, 4, 33, 57};
    tree.maakTestTree(v);

    // Testen van zoekfunctie
    if(tree.zoekSleutel(69)){
        std::cout << "Sleutel gevonden";
    } else {
        std::cout << "Sleutel niet gevonden";
    }

    std::cout << std::endl << std::endl;

    // Testen van minimummethode
    std::cout << "Minimum is " << tree.findMinimum()->getSleutel();

    std::cout << std::endl << std::endl;

    std::cout << "Maximum is " <<  tree.findMaximum()->getSleutel();

    std::cout << std::endl << std::endl;

    // Geeft de opvolger van 25 terug
    std::cout << "De opvolger van 25 is " << tree.getNext()->getSleutel();

    std::cout << std::endl << std::endl;

    std::cout << "De opvolger van 9 is " << tree.left->getNext()->getSleutel();

    std::cout << std::endl << std::endl;

    // Testen of het laatste element goed doorgegeven wordt
    auto opvolger = tree.right->right->getNext();
    if(opvolger != NULL) {
        std::cout << "De opvolger van 57 is " << tree.right->right->getNext()->getSleutel() << std::endl;
    } else {
        std::cout << "Er is geen opvolger, laatste element bereikt" << std::endl;
    }

    std::cout << std::endl << std::endl;

    std::cout << "De voorganger van 33 is " << tree.right->left->getPrevious()->getSleutel();


    return 0;
}