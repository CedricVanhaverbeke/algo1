#include <fstream>
#include <string>
#include "BinBoom.cpp"

using std::cout;
using std::endl;
using std::ifstream;
using std::string;

int main() {
    Binboom<string> b;
    ifstream is;
    is.open("jacht.txt");

    is >> b;

    // controle van de boom
    b.schrijf(cout);

    cout << endl << endl;

    cout << "vraag: ";
    // In preorder overlopen voor de vraag
    b.DEbezoek([](string&& s) { cout << s << " "; }, [](string&& s) {},
               [](string&& s) {});

    cout << "?" << endl << "antwoord: ";

    // In inorder overlopen
    b.DEbezoek([](string&& s) {}, [](string&& s) { cout << s << " "; },
               [](string&& s) {});
}