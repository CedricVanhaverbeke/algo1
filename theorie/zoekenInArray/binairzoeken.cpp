#include <iostream>
#include <vector>

using namespace std;

// Method returns v.size() if element is not in array
// Else method returns place of element
template <class T>
int binairZoeken(vector<T>& v, T& el) {
    int l = 0, r = v.size();  // set l and r
    while (r - l > 1) {  // When size of the vector keeps being bigger than 1
        int m = l + (r - l) / 2;  // Gets the middle of the vector
        if (el < v[m]) {
            r = m;
        } else {
            l = m;
        }
    }
    return el == v[l] ? l : v.size();
}

int main(int argc, char** argv) {
    // v moet een strict stijgende vector zijn
    vector<int> v{1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    int tooSeek = 11;
    int index = binairZoeken(v, tooSeek);
    cout << index;
    return 0;
}
