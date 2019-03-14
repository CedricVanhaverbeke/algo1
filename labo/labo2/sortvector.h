#ifndef __SORTVECTOR
#define __SORTVECTOR
/**
 \class sortvector
 \brief is een klasse van sorteerbare vectoren
 Bovenop de vectoreigenschappen zijn er hulpfuncties om sorteervergelijkingen
 te vergemakkelijken.
*/
#include <iostream>
using std::istream;
using std::move;
using std::ostream;
using std::swap;
#include <cstdlib>  // voor rand - opletten!!
#include <iomanip>  // voor setw
#include <vector>
using std::vector;

template <class T>
class Sortvector : public vector<T> {
   public:
    /// \fn Constructor: het argument geeft de grootte aan
    /// bij constructie zal de tabel opgevuld worden met
    /// n verschillende Ts in random volgorde
    /// (zie hulplidfuncties)
    Sortvector(int);  // Al geïmplementeerd

    // Volgende zaken worden verwijderd:
    Sortvector(const Sortvector<T>& v) = delete;
    Sortvector<T>& operator=(const Sortvector<T>& v) = delete;
    Sortvector<T>& operator=(Sortvector<T>&& v) = delete;
    Sortvector(Sortvector<T>&& v) = delete;

    /// \fn vul_range vul vector met de waarden T(0)...T(size()-1) in volgorde
    void vul_range();
    void draai_om();
    void vul_omgekeerd();
    void shuffle();
    void vul_random_zonder_dubbels();
    void vul_random();  //< nog niet implementeren

    bool is_gesorteerd() const;
    /// \fn is_range controleert of *this eruit ziet als het resultaat van
    /// vul_range(), d.w.z. dat, voor alle i, (*this)[i]==T(i);
    bool is_range() const;

    // Aantal inversies berekenen
    int geefaantalinversieskwadratisch() const;

    // Aantal inversies berkenen met mergesort
    int geefaantalinversiesMetMergesort() const;

    friend ostream& operator<<(ostream& os, const Sortvector<T>& s) {
        s.schrijf(os);
        return os;
    }

   private:
    void schrijf(ostream& os) const;
};

#endif