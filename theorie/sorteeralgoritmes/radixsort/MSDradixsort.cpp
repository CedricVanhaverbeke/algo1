#include <math.h>
#include <bitset>
#include <iostream>
#include <string>
#include <vector>

using std::bitset;
using std::cout;
using std::endl;
using std::move;
using std::ostream;
using std::size_t;
using std::string;
using std::swap;
using std::vector;


void print_array(int* tabel, int size);

template <class T>
ostream& operator<<(ostream& os, vector<T>& v);

// A function to do counting sort of v[] according to 
// the digit represented by exp. 
void countSort(vector<int> & v, int exp, int m, int max) 
{ 
    vector<int> output;// output array 
    vector<int> frequentietabel(m, 0); 
  
    // Store frequentietabel of occurrences in count[] 
    for (int i = 0; i < v.size(); i++){
         frequentietabel[ (v[i]/exp)%10 ]++; 
    }

    cout << frequentietabel;
  
    // Change frequentietabel[i] so that frequentietabel[i] now contains actual 
    //  position of this digit in output[] 
    for (int i = 1; i < m; i++) 
        frequentietabel[i] += frequentietabel[i - 1]; 
  
    // Build the output array 
    for (int i = v.size() - 1; i >= 0; i--) 
    { 
        output[frequentietabel[ (v[i]/exp)%10 ] - 1] = v[i]; 
        frequentietabel[ (v[i]/exp)%10 ]--; 
    } 
  
    // Copy the output array to v[], so that v[] now 
    // contains sorted numbers according to current digit 
    for (int i = 0; i < v.size(); i++) 
        v[i] = output[i]; 
} 

/*
    Het principe van MSDradixsort is volledig analoog aan binaire quicksort.
    Alleen gaan we hier sorteren op grotere m (of dus de radix) waarden. Bij
   binair was dat 2.

    Het ligt dus voor de hand om gebruik te maken van countingsort om de
    onderlinge waarden te gaan sorteren
*/




void radixsort(vector<int> & v, int m) 
{ 
    // Find the maximum number to know number of digits 
    int max = 3;
  
    // Do counting sort for every digit. Note that instead 
    // of passing digit number, exp is passed. exp is 10^i 
    // where i is current digit number 
    for (int exp = 1; m/exp > 0; exp *= m) {
        countSort(v, exp, m, max); 
    }
} 

int main() {
    vector<int> v{696, 658, 759, 654, 457};
    cout << v;

    // We gaan sorteren in een tientallig stelsel
    radixsort(v, 10);
    cout << "vector na sorteren: " << endl << v;

    return 0;
}





int element_at(int number, int index, int m) {
    number /= pow(m, index - 1);
    return number % m;
}

template <class T>
ostream& operator<<(ostream& os, vector<T>& v) {
    for (auto i : v) {
        os << i << " ";
    }
    os << endl;
    return os;
}

void print_array(int* tabel, int size) {
    for (int i = 0; i < size; i++) {
        cout << tabel[i] << " ";
    }
    cout << endl;
}