# getallen

## Situering vh probleem:

- alfabet zijn de cijfers `0-9`
- waardes van het alfabet zijn ook dezelfde als het alfabet zelf `0-9`
- LET op: er staat `using template <class knoop>`. knoop is dus hetzelfde als T.

## Vraagstelling

't is weer op zijn Cnops opgesteld. Hier een verduidelijking:

als input krijg je n. Dit zijn een bepaald aantal getallen. Geen enkel getal mag
gelijk zijn aan 0. Bv:

```
n = 1
1
2
3
4
5
6
7
8
9

==> Dit zijn hier dus alle mogelijkheden
```

## Beetje uitleg van de prof

Een klasse waarin virtual methodes staan moeten overschreven worden in een
subklasse.

```C++
class A {
    virtual void doeIets() = 0;
}

// declaratie
class B : public A {
    void doeIets() override;
}

// implementatie
void B::doeIets(){ ... }
```

Het is dus de bedoeling dat we een subklasse maken voor de drie methodes
die reeds aangemaakt zijn.
