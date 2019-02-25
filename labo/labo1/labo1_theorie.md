# Labo 1 - theorie

Lel, we kunnen niet binnen in ons lokaal want het is te klein.

- Het eerste labo is een herhalingslabo
- Hoop problemen oplossen.
- We letten vooral op geheugenbeheer.
- Er wordt expliciet gebruik gemaakt van pointers

## Smart pointers

unique pointer en shared pointer

- Kunnen dynamisch geheugen alloceren
- Die doen het werk voor u. Automatische garbage collectie.

### shared pointer

- Hebben een tellerke, een reference counter.
  - reference counter verhoogt als er iemand naar dit stuk geheugen wijst
  - En vice versa, verlaagt ook als niet naar dit stuk gewezen wordt.
- Veroorzaakt wel overhead (de referencecounter).

Als de reference counter op 0 staat, zal het stuk geheugen gedealloceerd worden.

### unique pointers

- Gebruiken een heel ander model: een hiërarchisch model
- Zie het als ouder-kind relaties
- ieder stuk geheugen heeft 1 beheerder, dus 1 ouder -> kan meerdere kinderen hebben.
- De unique pointer is - zoals de naam zelf zegt - uniek. De unique pointer is de beheerder.
- Er kunnen wel gewone pointers zijn naar dat stuk geheugen, alleen beheren ze het stuk geheugen
  niet.
- Als de unique pointer verwijdert wordt, moet het stuk geheugen ook gedealloceerd worden.

### move & copy

- 2 soorten objecten
  - simpele objecten: Een object dat 1 stukje geheugen bevat
  - complexe objecten

Stel: a wil alle eigenschappen van b opnemen, waarbij a en b simpele objecten zijn. Bij
een simpel object is dat makkelijk: je moet enkel alle gegevensvelden kopiëren. velden
en pointers kan je gewoon overnemen

```cpp
a = b // bij simpele objecten zijn move en copy hetzelfde
```

Bij complexe objecten: een complex object beheert zelf ook andere complexe objecten.
Typisch bij gegevensstructuren

#### Copy

Ik wil alle eigenschappen van a overnemen in b maar a moet blijven bestaan.

#### Move

b moet alle eigenschappen van a overnemen, en daarna ben ik niet meer geïnteresseerd in a.
Nu mag je niet gewoon copy doen. We gaan de resources niet verdubbelen maar laten pointen naar de resources van a

Bv: bij gelinkte lijst, enkel eerste knoop verplaatsen

```cpp
b = a; // Typisch copyconstructor
b = move(a); //Typisch met move
```

#### swap

Je kan ook de move-operator definiëren met een swap
Dit is bijvoorbeeld zo bij strings

```cpp
b = move(a) // Stel dat a & b strings zijn dan worden a en b geswapt.
```
