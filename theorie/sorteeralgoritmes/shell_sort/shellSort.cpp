#include <iostream>
#include <vector>
using namespace std;

/*
    k = de ruimte tussen de elementen die vergeleken worden

    i begint op k.
    j begint op i - k, dus de eerst mogelijke plaats van de reeks

    Daarna gaan we elk element van de j-deelreeks controleren met een vorm van
    insertion sort, dat is lijn 27.

    Deze methode is met dalende incrementen, en / 2 per stap. Dit kunnen even
   goed andere stappen zijn
*/
template <class T>
vector<T> &shell_sort(vector<T> &vector) {
    int k = vector.size() / 2;  // initieel increment

    while (k >= 1) {  // of dus k >= 1
        for (int i = k; i < vector.size(); i++) {
            T temp = move(vector[i]);

            int j = i - k;  // Aangezien i op k begint trekken we af om het
                            // element ervoor te vinden

            // insertion sort deel
            while (j >= 0 && vector[j] > temp) {
                vector[j + k] = move(vector[j]);

                // Op deze manier controleren we elke k'de stap voor j kleiner
                // dan  0 wordt
                j -= k;
            }

            // want j is kleiner geworden dan 0 na de laatste iteratie
            // Het kleinste element moet de tijdelijke waarde worden
            // Want anders staan er dubbels in
            vector[j + k] = move(temp);
        }

        k = k / 2;
    }

    return vector;
}

template <class T>
void print_vector(vector<T> &vector) {
    for (auto t : vector) {
        cout << t << " ";
    }
    cout << endl;
}

int main() {
    cout << "Before sorting: " << endl;
    vector<int> vector{4, 8, 9, 10, 7, 1, 9, 12, 3, 6};
    print_vector(vector);

    cout << endl;

    cout << "After sorting: " << endl;
    vector = shell_sort(vector);
    print_vector(vector);
    return 0;
}