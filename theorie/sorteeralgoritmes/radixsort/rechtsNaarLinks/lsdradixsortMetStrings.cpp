#include <iostream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, vector<T>& v) {
    for (int i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    os << endl;
    return os;
}

int getElementAt(string element, int exp, int maxLength) {
    char karakter = element[maxLength - exp - 1];
    return int(karakter) - 48;
}

void countsort(vector<string>& v, int m, int exp, int maxLength,
               vector<string>& h) {
    vector<int> frequentietabel(m, 0);

    for (int i = 0; i < v.size(); i++) {
        frequentietabel[getElementAt(v[i], exp, maxLength)]++;
    }

    for (int i = 1; i < m; i++) {
        frequentietabel[i] += frequentietabel[i - 1];
    }

    for (int i = v.size() - 1; i >= 0; i--) {
        h[--frequentietabel[getElementAt(v[i], exp, maxLength)]] = v[i];
    }
}

void lsdradixsort(vector<string>& v, int m, vector<string>& h) {
    int maxlength = v[0].length();

    // maximale lengte bepalen
    for (int i = 1; i < v.size(); i++) {
        if (v[i].length() > maxlength) {
            maxlength = v[i].length();
        }
    }

    // Nullen vooraan zetten
    for (int i = 0; i < v.size(); i++) {
        int aantalNullen = maxlength - v[i].length();
        for (int j = 0; j < aantalNullen; j++) {
            string nul = "0";
            nul.append(v[i]);
            v[i] = nul;
        }
    }

    // Nu beginnen sorteren
    for (int i = 0; i < maxlength; i++) {
        countsort(v, 10, i, maxlength, h);
    }

    // trailing nullen verwijderen
    for (int i = 0; i < h.size(); i++) {
        int j = 0;
        while (h[i].at(j) == '0') {
            h[i] = h[i].substr(1);
        }
    }

    v = move(h);
}

int main() {
    vector<string> v{"4158", "5", "433", "76"};

    cout << "originele vector: " << endl << v << endl << endl;

    vector<string> h(v.size());
    lsdradixsort(v, 10, h);
    cout << v;
}