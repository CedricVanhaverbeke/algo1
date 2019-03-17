#include <iostream>
#include <vector>
using namespace std;

/*
    Bij selection sort beginnen we achteraan
    We kijken naar het grootste element, standaard
    zeggen we dat het grootste element zich bevindt op plaats i.
    Als i dan toevallig echt het grootste element is
    zal swap niets doen.

    Het nadeel van deze methode is het maximum bepalen
    Daardoor is de uitvoeringstijd nog altijd O(n^2).
    Door gebruik te maken van een stijgende heap kunnen we
    dit reduceren naar O(nlogn)
*/
template <class T>
void selection_sort(vector<T>& vector) {
    for (int i = vector.size() - 1; i >= 0; i--) {
        // Het maximum zoeken van de array adhv de plaats
        // Dit is de naïeve methode
        int max = i;
        for (int j = 0; j < i; j++) {
            if (vector[j] > vector[max]) {
                max = j;
            }
        }
        swap(vector[i], vector[max]);
    }
}

template <class T>
ostream& operator<<(ostream& os, vector<T>& v) {
    for (int i = 0; i < v.size(); i++) {
        os << v[i] << " ";
    }
    os << endl;
    return os;
}

int main() {
    cout << "Before sorting: " << endl;
    vector<int> vector{4, 8, 9, 10, 7, 1, 9, 12, 3, 6};
    cout << vector;
    selection_sort(vector);
    cout << "Na sorteren\n" << vector;
    return 0;
}