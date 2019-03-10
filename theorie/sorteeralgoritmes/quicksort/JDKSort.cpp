#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <vector>

using namespace std;

template <class T>
void print_vector(vector<T> &vector) {
    for (auto t : vector) {
        cout << t << " ";
    }
    cout << endl;
}

/*
    THIS ALGORITHM CAN BE VIEWED IN:
    https://learnforeverlearn.com/yaro_web/
*/

template <class T>
void dualPivotSort(vector<T> &vector, int left, int right) {
    // Only perform algorithm if right is bigger then left
    if (right > left) {
        // The element on place right needs to be bigger
        if (vector[left] > vector[right]) {
            swap(vector[left], vector[right]);
        }

        // p and q are the spil elements
        int p = vector[left], q = vector[right];

        // Partition vector according to invariant below
        int l = left + 1, g = right - 1, k = l;

        while (k <= g) {
            // If an element is smaller than the first partitioning element
            // you can just swap it with the place of k
            if (vector[k] < p) {
                swap(vector[k], vector[l]);
                l++;  // Don't forget to add 1 to l;
            } else if (vector[k] >= q) {
                // If the element at spot g is bigger than the seoncd
                // partitioning element We need to place it in the back of the
                // array We skip elements in the array that are bigger than the
                // second partitioning element So we don't do unneccesarry swaps
                while (vector[g] > q && k < g) {
                    g--;  // If the element currently at g is bigger than the
                          // second partitioning element
                    // we want to swap with the element before it.
                }
                // Now vector[g] is a smaller value
                swap(vector[k], vector[g]);
                g--;

                // Now that we swapped the value the new obtained value can
                // again be smaller than the first
                if (vector[k] < p) {
                    swap(vector[k], vector[l]);
                    l++;
                }
            }
            // 1 step is complete:
            k++;
        }

        // The following code is to place the pivots at the right spot:
        l--;
        g++;

        // Swap pivots to final place
        swap(vector[left], vector[l]);
        swap(vector[right], vector[g]);

        // Recursively sort partitions
        dualPivotSort(vector, left, l - 1);
        dualPivotSort(vector, l + 1, g - 1);
        dualPivotSort(vector, g + 1, right);
    }
}

template <class T>
void JDKdualPivotSort(vector<T> &vector) {
    dualPivotSort(vector, 0, vector.size() - 1);
}

int main() {
    srand(time(NULL));
    cout << "Before sorting: " << endl;
    std::vector<int> vector{10, 38, 27, 43, 3, 9, 82};
    print_vector(vector);

    cout << endl;

    cout << "After sorting: " << endl;
    JDKdualPivotSort(vector);
    print_vector(vector);
    return 0;
}