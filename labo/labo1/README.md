# Uitleg labo 1

Cnops smijt alles in 1 bestand en dat is vreselijk. Daarom heb ik de opgave geherformatteerd. Je kan hem hier vinden:

[Deftige opgave](./opgave_deftig.zip)

## Stap 1

Bij het maken van een lijst zie je de methode voeg toe. Op de laatste lijn staat:

```c++
*this = std::move(nieuw);
```

`*this` slaat op de lijst. \*this is een lijst en nieuw is een lijstknoop. Daarom dat we eerst de move operator moeten definiëren van lijst.
In de oplossing zie je Demian zijn uitgebreide uitleg hiervan
Dit ziet er zo uit:

```c++
// Move operator in de header
Lijst& operator=(Lijstknoopptr<T>&&);

// Bij de implementatie
Lijstknoopptr<T>::operator=(move(other));
return *this;
```

TODO: uitleg van tweede lijn. Ik denk dat je de move operator gebruikt van
de lijstknoop op die manier die al bestaat.

## Stap 2

De defaultconstructor heeft ook nog een probleem. Lijst is dan wel afgeleid van een unique_pointer, namelijk lijstknoopptr.
Hij weet niet dat we gewoon die constructor willen gebruiken. Daarom implementeren we de constructor op volgende manier:

```c++
// Default constructor: Let hier op: geen <T>! Nooit bij constructors
// In headerfile:
Lijst();

// In implementatiefile
template <class T>
Lijst<T>::Lijst() : Lijstknoopptr<T>(){};
```

## Stap 3

Volgende code werkt niet. Cnops had deze wel in commentaar gezet. Ik heb geen idee hoe belangrijk dit dus is.

```c++
    for (auto s:l)
        cerr<<s<<"\n";
    l.schrijf(cerr);
```

Alleszins: hiervoor volg je de letterlijke output van de foutmelding en ga je van de iteratorklasse in de lijst alles gaan implementeren.
Hier de foutmelding:

```
Undefined symbols for architecture x86_64:
  "Lijst<int>::iterator::operator!=(Lijst<int>::iterator const&)", referenced from:
      _main in main-fbc945.o
      Lijst<int>::schrijf(std::__1::basic_ostream<char, std::__1::char_traits<char> >&) const in main-fbc945.o
  "Lijst<int>::iterator::operator++()", referenced from:
      _main in main-fbc945.o
      Lijst<int>::schrijf(std::__1::basic_ostream<char, std::__1::char_traits<char> >&) const in main-fbc945.o
  "Lijst<int>::end() const", referenced from:
      _main in main-fbc945.o
      Lijst<int>::schrijf(std::__1::basic_ostream<char, std::__1::char_traits<char> >&) const in main-fbc945.o
  "Lijst<int>::begin() const", referenced from:
      _main in main-fbc945.o
      Lijst<int>::schrijf(std::__1::basic_ostream<char, std::__1::char_traits<char> >&) const in main-fbc945.o
  "Lijst<int>::iterator::operator*() const", referenced from:
      _main in main-fbc945.o
      Lijst<int>::schrijf(std::__1::basic_ostream<char, std::__1::char_traits<char> >&) const in main-fbc945.o
ld: symbol(s) not found for architecture x86_64
clang: error: linker command failed with exit code 1 (use -v to see invocation)
The terminal process terminated with exit code: 1
```

We moeten de iterator implementeren. De iterator is echter bv van het type iterator<int>. Daarom zijn we genoodzaakt
om een iterator te implementeren die nog een extra veld heeft, de huidige knoop waar hij mee bezig is, zodat we naar de volgende kunne

```c++
iterator(Lijstknoop<T>* l = 0) : huidig(l) {}
private:
// Anders kan je niet bijhouden bij welke lijstknoop je zit
Lijstknoop<T>* huidig;
```

```c++
//Functies implementeren
// Kijken of de waarden in de iteratoren gelijk zijn of niet
template <class T>
bool Lijst<T>::iterator::operator!=(const iterator& other) {
    return (this->huidig != other.huidig);
}

// Naar het volgende element gaan
template <class T>
const typename Lijst<T>::iterator& Lijst<T>::iterator::operator++() {
    if (this->huidig) {
        this->huidig = this->huidig->volgend.get();
    }
    return *this;
}

// De dereferentie-operator
template <class T>
const T& Lijst<T>::iterator::operator*() const {
    return this->huidig->sleutel;
}

// Code voor de iterator
// begin en end zijn eigenlijk functies van de lijst. Daarom dat this een lijst
// teruggeeft
template <class T>
typename Lijst<T>::iterator Lijst<T>::begin() const {
    // this is hier de lijst
    // this = De lijst = Lijstknooppointer
    // this-> = Lijstknoop
    // this->get() = de waarde van de lijstknoop
    return iterator(this->get());
}

template <class T>
typename Lijst<T>::iterator Lijst<T>::end() const {
    // Een gelinkte lijst eindigt op een nullpointer.
    return nullptr;
}
```

### Vragen bij deze stap

- voor wat staat de typename bij begin() en end()
- Waarom is bevat de iterator niet gewoon lijstpointers? Nu bevat hij gewoon een int en moet je een huidige knoop bijhouden om het boeltje te doen werken

## Stap 4: Assignment operator

Nu raak je al redelijk ver! Hij begint te neuten op volgende lijn:

```c++
l2 = l;
```

Dit is de copy assignment operator.

```c++
// In headerfile
 // Copy assignment operator
Lijst& operator=(const Lijst&);

// implementatie
// Copy assignment operator
// In this zit nu het linkerlid
template <class T>
Lijst<T>& Lijst<T>::operator=(const Lijst<T>& other) {
    // Als de lijsten naar hetzelfde pointen
    if (other == *this) {
        return *this;
    }

    // We gaan enkel de eerste knoop kopiëren
    // Zodat het begin van de lijst wel verschillend
    // is maar de rest niet
    if (other.get() != nullptr) {
        auto tmp = std::make_unique<Lijstknoop<T>>(other->sleutel);
        (*this) = std::move(tmp);
        this->get()->volgend = other->volgend;
    }

    return *this;
}
```

Door dit toe te voegen blijken zowel de copy constructor als de default constructor impliciet verwijderd te zijn.

“An implicitly declared copy constructor/assignment operator will be defined as deleted if the class declares a move operation, otherwise it will be defined as defaulted.”

“If any constructor is explicitly declared, then no default constructor is automatically generated.”

# Stap 5: De copy constructor implementeren

```c++
// declaratie
// Copy constructor
Lijst(const Lijst&);

// implementatie
// is volgens mij basically hetzelfde als de copy assignment operator
// Een copy constructor returnt ook niets
template <class T>
Lijst<T>::Lijst(const Lijst<T>& other) {
    auto tmp = std::make_unique<Lijstknoop<T>>(other->sleutel);
    (*this) = std::move(tmp);
    this->get()->volgend = other->volgend;
}
```

# Stap 6: De default constructor

We kunenn de default constructor van een unique pointer gebruiken

```c++
// Declaratie
// Default constructor
Lijst();

// Implementatie
// Default constructor gebruikt de constructor van een lijstknooppointer
template <class T>
Lijst<T>::Lijst() : Lijstknoopptr<T>(){};
```
