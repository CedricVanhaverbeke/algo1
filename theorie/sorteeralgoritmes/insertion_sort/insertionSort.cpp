// https://www.cs.usfca.edu/~galles/visualization/ComparisonSort.html

#include <iostream>
#include <vector>
using namespace std;

/*
    2 tellers, i en j
    i  en j moeten altijd buren zijn

    We laten i op 1 beginnen en j eentje daarvoor.
    we houden een hulpwaarde bij zodat we de eerste waarde van v[i] kunnen
   bijhouden

   Wa laten j stapjes terug nemen zolang j groter of gelijk is aan 0 en de
   waarde van h, dus de oorspronkelijke waarde van i kleiner is dan de waarde
   van j op dat moment.

   Waar de teller j stopt wil zeggen dat v[j] kleiner wordt dan de hulpwaarde

   Daarom zetten we de hulpwaarde op plaats j+1
*/

template <class T>
void insertion_sort(vector<T>& v) {
    for (int i = 1; i < v.size(); i++) {
        T h = move(v[i]);  // De te verplaatsen waarde
        int j = i - 1;     // j eentje kleiner laten beginnen dan i
        while (j >= 0 && h < v[j]) {
            // Deze stap verschuift de waarden naar rechts
            v[j + 1] = move(v[j]);
            j--;
        }
        v[j + 1] = move(h);  // Deze stap zet de uiteindelijke waarde juist
    }
}

template <class T>
void insertion_sort_met_swap(vector<T>& v) {
    for (int i = 1; i < v.size(); i++) {
        int j = i;
        while (j > 0 && v[j] < v[j - 1]) {
            swap(v[j], v[j - 1]);
            j--;
        }
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
    vector<int> vector{4, 6, 3, 2, 9, 5, 1};
    cout << vector;
    insertion_sort(vector);
    cout << "Na sorteren\n" << vector;
    return 0;
}