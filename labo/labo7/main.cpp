#include <fstream>
#include <iostream>
#include <string>
#include <math.h> 
#include <iomanip>  
#include "hash_tabel.cpp"


using namespace std;

int superslechtehash(const string& s, int n) { return n/2 % n; }

int slechtehash(const string& s, int n) { return s.size() % n; }

int hornerhash(const string& woord, int n) {
    unsigned int horner = 0;
    for (int i = 0; i < woord.size(); i++) horner = (horner * 256 + woord[i]);
    return horner % n;
}

// enige verschil is de modulo verplaatsen 
int hornerhash_optimized(const string& woord, int n) {

    unsigned int horner = 0;
    for (int i = 0; i < woord.size(); i++) {
        horner=(horner*256 + woord[i])%n;
    }

    return horner;
};

vector<string>& readFile(string path, vector<string>& v) {
    string sleutel;
    ifstream inFile;
    inFile.open(path);
    while (inFile >> sleutel) {
        v.push_back(sleutel);
    }

    inFile.close();

    return v;
}

int main() {
    Hashtabel<string, superslechtehash> ht0{574427};
    Hashtabel<string, slechtehash> ht1{574427};
    Hashtabel<string, hornerhash> ht2{574427};
    Hashtabel<string, hornerhash_optimized> ht3{574427};
    vector<string> v;

    // vul de vector met woorden
    readFile("woordenlijst.txt", v);
    ht0.vul(v);
    ht1.vul(v);
    ht2.vul(v);
    ht3.vul(v);

    cout << left <<  setw(40) << "Score voor super slechte hash:" << ht0.score() << endl;
    cout << left <<  setw(40) << "Score voor slechte hash:" << ht1.score() << endl;
    cout << left <<  setw(40) << "Score voor betere hash:" << ht2.score() << endl;
    cout << left <<  setw(40) << "Score voor supergoede hash:" << ht3.score() << endl;
    return 0;
}
