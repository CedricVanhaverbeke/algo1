#include <iostream>
#include <vector>

using namespace std;

// This method doesn't work :'(
template <class T>
int interpolerendZoeken(vector<T>& v, T& el) {
    int l = 0, r = v.size();  // set l and r

    // Manner to calculate m, but doesn't do jack shit
    int m = l + ((r - l) * ((el - v[l]) / (v[r] - v[l])));

    // in the while loop we need to check that m falls between the boundaries
    while (r - l > 1 && m >= l &&
           m <= r) {  // When size of the vector keeps being bigger than 1
        if (el < v[m]) {
            r = m;
        } else {
            l = m;
        }
        int m = l + ((r - l) * ((el - v[l]) / (v[r] - v[l])));
    }
    return el == v[l] ? l : v.size();
}

int main(int argc, char** argv) {
    // v moet een strict stijgende vector zijn
    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    int tooSeek = 11;
    int index = interpolerendZoeken(v, tooSeek);
    cout << index;
    return 0;
}
