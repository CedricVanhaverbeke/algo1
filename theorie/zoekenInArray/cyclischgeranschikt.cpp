// Boek p 48

#include <iostream>
#include <vector>

using namespace std;

template <class T>
int vindCyclischBegin(vector<T>& v) {
    int l = 0, r = 1;

    // We laten r vergroten tot we zien dat r kleiner wordt.
    while (v[l] < v[r]) {
        r *= 2;
    }
    // Daarna tellen we gewoon af tot we de juiste waarde vinden
    // We mogen niet voorbij de vorige waarde van r: r/2
    l = r - 1;
    while (v[l] < v[r] && l >= r / 2) {
        l--;
        r--;
    }

    return r;
}

int main(int argc, char** argv) {
    // v is nu cyclisch
    vector<int> v{6, 7, 8, 9, 10, 0, 1, 2, 3, 4, 5};
    int index = vindCyclischBegin(v);
    cout << "Cyclisch begin is op index " << index
         << " met als waarde: " << v[index] << endl;
    return 0;
}
