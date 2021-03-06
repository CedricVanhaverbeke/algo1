# Uitleg labo 1

Cnops smijt alles in 1 bestand en dat is vreselijk. Daarom heb ik de opgave geherformatteerd. Je kan hem hier vinden:

[Deftige opgave](./opgave_deftig.zip)

## Regels voor impliciet verwijderde constructoren / operatoren

- If any constructor is explicitly declared, then no default constructor is automatically generated.
- If a virtual destructor is explicitly declared, then no default destructor is automatically generated.
- If a move constructor or move-assignment operator is explicitly declared, then:

  - No copy constructor is automatically generated.
  - No copy-assignment operator is automatically generated.

- If a copy constructor, copy-assignment operator, move constructor, move-assignment operator, or destructor is explicitly declared, then:
  - No move constructor is automatically generated.
  - No move-assignment operator is automatically generated.

In C++ 11 only:

- If a copy constructor or destructor is explicitly declared, then automatic generation of the copy-assignment operator is deprecated.
- If a copy-assignment operator or destructor is explicitly declared, then automatic generation of the copy constructor is deprecated.

## Stap 1

Bij het maken van een lijst zie je de methode voeg toe. Op de laatste lijn staat:

```c++
*this = std::move(nieuw);
```

`*this` slaat op de lijst. \*this is een lijst en nieuw is een lijstknoop. Daarom dat we eerst de move operator moeten definiëren van lijst.
In de oplossing zie je Demian zijn uitgebreide uitleg hiervan
Dit ziet er zo uit:

```c++
// move operator declaratie
Lijst& operator=(Lijstknoopptr<T>&&);

// Implementatie
template <class T>
Lijst<T>& Lijst<T>::operator=(Lijstknoopptr<T>&& other) {
    // Deze methode gaat de move operator oproepen van
    // de klasse Lijstknoopptr. Je erft ervan over
    // daarom kan je daaraan.
    Lijstknoopptr<T>::operator=(move(other));
    return *this;
}
```

## Stap 2: Assignment operator

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

Door deze stap toe te voegen is de copyconstructor die normaal standaard gemaakt wordt verdwenen.
(zie regels bovenaan). Omdat we de copyconstructor gaan moeten implementeren, gaat de default constructor
ook zagen. Daarom moeten we die ook implementeren.

## Stap 3: De copy constructor implementeren

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

## Stap 4: De defaultconstructor implementeren

De defaultconstructor heeft nu dus ook nog een probleem. Lijst is dan wel afgeleid van een unique_pointer, namelijk lijstknoopptr.
Hij weet niet dat we gewoon die constructor willen gebruiken. Daarom implementeren we de constructor op volgende manier:

```c++
// Default constructor: Let hier op: geen <T>! Nooit bij constructors
// In headerfile:
Lijst();

// In implementatiefile
template <class T>
Lijst<T>::Lijst() : Lijstknoopptr<T>(){};
```

Omdat we eigenlijk gewoon de superklasse aanspreken weet C++ hier wel raad mee. Daarom volstaat om gewoon de default constructor te gebruiken

```c++
//declaratie
// default constructor
Lijst() = default;
```

## Stap 5: Move operator / Move constructor

Omdat we nu een copy constructor / copy assignment operator hebben geschreven, is de move operator
en move constructor impliciet verwijderd.

```
maak met transfer
Fout bij controle:
Aantal gemaakte knopen   : 16 (moet zijn: 8)
Aantal verwijderde knopen: 8 (moet zijn: 0)
libc++abi.dylib: terminating with uncaught exception of type char const*
```

Uitleg van de assistent: Ik heb enkel een move operator geschreven voor een Lijst met als argument een lijstknoopptr.
Daarom gebruikt mijn code de copy constructor van Lijst en wordt er gewoon een extra lijst gemaakt en direct weggegooid

In de headerfile:

```cpp
// Move operator met een lijst
Lijst& operator=(Lijst&&);

// Move constructor
Lijst(Lijst&&);
```

#### Implementatie move operator

Cnops zei dat je even goed een move operator kan implementeren met een swap, maar da's niet zo'n goede code.
In essentie willen we gewoon de move operator van de unique_pointer<T> gebruiken, of dus van een lijstknoopptr, want da's zijn alias

```cpp
// Move operator met een lijst
template <class T>
Lijst<T>& Lijst<T>::operator=(Lijst<T>&& other) {
    Lijstknoopptr<T>::operator=(move(other));
    return *this;
}
```

#### Implementatie move constructor

In essentie gebruiken we de move constructor van een Lijstknoopptr, wat eigenlijk gewoon een unique_pointer is.

```cpp
template <class T>
Lijst<T>::Lijst(Lijst<T>&& other) : Lijstknoopptr<T>(move(other)) {}
```

## Stap 6: Lege lijsten toekennen

Nu is er nog een probleem met volgende lijn code:

```cpp
l = l2;
```

In l2 zit een lege lijst en daar kan onze assignment operator nog niet mee overweg.
Daarom schrijven we: als het wel over een lege lijst gaat:

```cpp
} else {
    (*this) = nullptr;
}
```

## Stap 7 : Iteratoren - was deel II van het labo

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

We moeten de iterator implementeren. De iterator is echter bv van het type Lijstknoop. Daarom zijn we genoodzaakt
om een iterator te implementeren die nog een extra veld heeft, de huidige knoop waar hij mee bezig is, zodat we naar de volgende kunnen

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

### Eindremarks labo

We hebben nu een aantal constructoren geschreven die eigenlijk letterlijk doen wat de superklasse doet. Daarom is het ook perfect mogelijk om gewoon dit te schrijven

```cpp
    // Move operator met een lijst
    Lijst& operator=(Lijst&&) = default;

    // Move constructor
    Lijst(Lijst&&) = default;

    // Default constructor
    Lijst() = default;
```

Zelfs de copyconstructor werkt als we hem zo implementeren. Dat komt echter omdat we hem in ons testprogramma niet gebruiken. Moesten we hem testen, zou C++ er wellicht niet
mee omkunnen. Daarom zet ik hem niet in het rijtje.
