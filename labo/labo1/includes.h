// Hier worden al wat zaken op voorhand gedefinieerd
#include <algorithm>
#include <cassert>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>
#include <string>

using std::endl;
using std::ofstream;
using std::ostream;
using std::string;

template <class T>
class Lijstknoop;

template <class T>
class Lijst;

template <class T>
using Lijstknoopptr = std::unique_ptr<Lijstknoop<T>>;