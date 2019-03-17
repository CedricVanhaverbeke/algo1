#include <iostream>
#include <vector>
using namespace std;

/*
    k = de ruimte tussen de elementen die vergeleken worden

    Deze methode is met dalende incrementen, en / 2 per stap. Dit kunnen even
   goed andere stappen zijn
*/
template <class T>
void shell_sort(vector<T>& v) {
    int k = v.size() / 2;  // initieel increment

    while (k >= 1) {  // k mag maximaal 1 worden

        // insertion sort
        for (int i = 0; i < v.size(); i += k) {
            T h = move(v[i]);
            int j = i - k;  // de waarde voor i
            while (j >= 0 && v[j] > h) {
                v[j + k] = move(v[j]);
                j -= k;
            }
            v[j + k] = move(h);  // waarde op de juiste plaats zetten
        }

        k /= 2;
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