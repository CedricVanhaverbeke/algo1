#include <iostream>
#include "BinBoom.cpp"

using std::cout;

template <class T>
void createTestTree(Binboom<T>& b) {
    // Create a tree to play with
    b->changeLeftChild(2);
    b->changeRightChild(3);

    b->links->changeLeftChild(4);
    b->links->changeRightChild(5);

    b->rechts->changeLeftChild(6);
    b->rechts->changeRightChild(7);

    b->links->links->changeLeftChild(8);
    b->links->links->changeRightChild(9);
    b->links->rechts->changeLeftChild(10);
    b->links->rechts->changeRightChild(11);

    b->rechts->links->changeLeftChild(12);
    b->rechts->links->changeRightChild(13);
    b->rechts->rechts->changeLeftChild(14);
}

int main() {
    // Create a tree of ints
    Binboom b(1);
    createTestTree(b);

    cout << "Diepte eerst recursief\n";
    b.DEZPrintRec(cout);

    cout << "\n\nDiepte eerst niet recursief\n";

    b.DEZPrint(cout);

    cout << "\n\nBreedte eerst\n";

    b.BEZPrint(cout);
    return 0;
}