#include <iostream>
#include <vector>

using std::vector;
using std::ostream;
using std::endl;
using std::cout;
using std::swap;

template <class T>
ostream& operator<<(ostream& os, vector<T>& v) {
    for (auto i : v) {
        os << i << " ";
    }
    os << endl;
    return os;
}


// Methode zoekt de gesorteerde plaats
// van een element in een vector met een bepaalde index
// Dit doet dus 1 stap van quicksort
template <class T>
int vindGesorteerdePlaats(vector<T> & v, int index){
    T pivot = v[index];
    int hl = 0, hr = v.size() - 1;

    while (v[hr] > pivot) {
        hr--;
    }
    while (v[hl] < pivot) {
        hl++;
    }
        
        while (hl < hr) {
            swap(v[hl], v[hr]);
            hl++;
            hr--;

            while (v[hl] < pivot) {
                hl++;
            }
            while (v[hr] > pivot) {
                hr--;
            }
        }

    // Het element wat je geswapt hebt zit sowieso op de eerste plaats nu
    // hr is de plaats waar hij naartoe moet
    swap(v[0], v[hr]); // Deze swap moet niet meer, het is gewoon om het duidelijk te maken
    
    cout << hr << endl;
    return hr;
}



int main(){
    vector<int> v{33,11,7,9,24, 54};
    int plaats = vindGesorteerdePlaats(v, 4);
    cout << "Plaats is " << plaats << endl;

    return 0;

}

