#include <iostream>
#include <vector>
using namespace std;

template <class T>
void insertion_sort(vector<T>& v) {
    for (int i = 1; i < v.size(); i++) {
        T h = move(v[i]);
        int j = i - 1;
        while (j >= 0 &&
               h < v[j]) {  // Deze stap verschuift de waarden naar rechts
            v[j + 1] = move(v[j]);
            j--;
        }
        v[j + 1] = move(h);  // Deze stap zet de uiteindelijke waarde juist
    }
}

template <class T>
void insertion_sort_met_swap(vector<T>& v) {
    for (int i = 1; i < v.size(); i++) {
        int j = i - 1;
        T h = move(v[i]);
        while (j >= 0 && h < v[j]) {
            v[j] = swap(h);
            j--;
        }
    }
}

template <class T>
void print_vector(vector<T>& v) {
    for (auto x : v) {
        cout << x << " ";
    }
    cout << endl;
}

int main() {
    vector<int> vector{4, 6, 3, 2, 9, 5, 1};
    print_vector(vector);
    insertion_sort_met_swap(vector);
    print_vector(vector);
    return 0;
}