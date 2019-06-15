# Testvragen 2019

## 1) Vraag 1

**gegeven**:

een stijgend gesorteerde gelinkte lijst.

**gevraagd**:

Zet de lijst om zodat elk element in de lijst precies 2 keer voorkomt.
Je moet de lijst dus inkorten als er te veel elementen staan en
verlengen wanneer te weinig

**oplosssing**

Te vinden in `lijst.cpp`.

```cpp
template <class T>
void Lijst<T>::opdrachtTest() {
    auto loper = this->get(); // loper maken
        while(loper != nullptr) {
            T huidigElement = loper->sleutel;
            int aantal = 1;

            auto begin = loper; //copy om begin bij te houden

            while (loper->volgend.get() != nullptr && loper->volgend->sleutel == huidigElement) {
                aantal++; // tel het aantal voorkomen
                loper = loper->volgend.get();
            }

            // loper is gestopt op laatste element van de rij elementen
            if (aantal == 1) {
                auto uptr = std::make_unique<Lijstknoop<T>>(huidigElement);
                uptr->volgend = std::move(begin->volgend);
                begin->volgend = std::move(uptr);
            }

            // OPM: dus niets doen wanneer er twee elementen instaan

            if (aantal > 2) {
                // Als we naar de volgende gaan komen we dus op het
                // nieuwe element uit
                begin->volgend->volgend = std::move(loper->volgend); // skip de andere elementen
            }
            loper = begin->volgend->volgend.get(); // loper eentje vooruit zetten
        }
}
```
