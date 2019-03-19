#include <math.h>

template <class T>
int getJuisteIndex(std::vector<T>& v) {
    int getal = rand() % v.size();
    return getal;
}