#include <fstream>
#include <string>
#include "BinBoom.cpp"

using std::cout;
using std::ifstream;
using std::string;

int main() {
    Binboom<string> b;
    ifstream is;
    is.open("jacht.txt");

    is >> b;

    b.schrijf(cout);
}