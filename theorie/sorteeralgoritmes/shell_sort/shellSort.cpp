#include <iostream>
#include <vector>
using namespace std;

/*
    k = de ruimte tussen de elementen die vergeleken worden

    Deze methode is met dalende incrementen, en / 2 per stap. Dit kunnen even
   goed andere stappen zijn
*/
template <class T>
void shell_sort(vector<T>& vector) {
    int k = vector.size() / 2;  // initieel increment

    while (k >= 1) {
        /*
            Dit is het insertion sort deel. In plaats van
            het met adjacente waarden in de array te doen
            doen we dat nu met k plaatsen tussen. Deze
            sorteert dus de deelarray met k plaatsen tussen
        */
        for (int i = k; i < vector.size(); i += k) {  // stappen van k
            T temp = move(vector[i]);
            int j = i - k;  // ipv i - 1 zoals bij insertion, -k

            while (j >= 0 && vector[j] > temp) {
                vector[j + k] = move(vector[j]);
                j -= k;
            }
            vector[j + k] = move(temp);
        }
        k = k / 2;  // Hier verkleinen we k
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
    shell_sort(vector);
    cout << "Na sorteren\n" << vector;
    return 0;
}