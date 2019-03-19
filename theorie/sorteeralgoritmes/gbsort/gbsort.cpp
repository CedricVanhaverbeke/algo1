#include <math.h>
#include <time.h>
#include <iostream>
#include <string>
#include <vector>
#include "includes.h"

using namespace std;

template <typename T>
ostream& operator<<(ostream& os, vector<T>& v) {
    for (int i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    os << endl;
    return os;
}

template <class T>
bool isGesorteerd(vector<T>& v) {
    int i = 1;
    while (v[i] >= v[i - 1]) {
        i++;
    }
    return i == v.size();
}

template <class T>
void gbsort(vector<T>& v) {
    for (int i = 0; i < v.size(); i++) {
        int juisteIndex = getJuisteIndex(v);
        v[i] = move(v[juisteIndex]);
    }

    // BELANGRIJK: STOP BIJ V.SIZE()/2
    for (int i = 0; i < v.size() / 2; i += 2) {
        swap(v[i], v[v.size() - 1 - i]);
    }
}

int main() {
    srand(time(NULL));
    vector<int> sort = {1, 1, 1, 1, 1, 1, 5, 4, 3, 2, 1,
                        1, 1, 4, 4, 4, 4, 5, 5, 5, 5, 5};

    while (!isGesorteerd(sort)) {
        gbsort(sort);
    }

    cout << sort;
}