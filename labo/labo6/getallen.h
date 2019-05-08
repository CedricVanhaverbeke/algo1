// Opgave

#include <stdio.h>
#include <fstream>
#include <iostream>
using std::cerr;
using std::ostream;
#include <vector>
using std::vector;
// De klasse Backtrackflex zoekt een vector van knopen die een oplossing biedt
// voor een gegeven probleem. Wat er met deze oplossing moet gedaan worden staat
// in de functie verwerkt. Backtrackflex kan ingesteld worden zodat hij juist 1
// oplossing zoekt, of zodat hij alle oplossingen zoekt.
//
// Backtrackflex is flexibel omdat het toevoegen/wegnemen van elementen
// aan/van deeloplossing kan overschreven worden.

template <class knoop>
class Backtrackflex {
    // als opgeroepen met zoekalle=true worden alle oplossingen gezocht
   public:
    void losOp(bool zoekalle);

   protected:
    void losOp(bool& gedaan, bool zoekalle);

    // de volgende functies moeten misschien aangepast voor specifieke
    // problemen.
    virtual void voegToeAanDeeloplossing(const knoop& element);
    virtual void verwijderUitDeeloplossing();

    /**********************************************************************

    De onderstaande functies moeten ingevuld worden voor specifieke problemen.


    ***************************************************************************/
    // controle geeft true terug als de vector deeloplossing een oplossing
    // bevat.
    virtual bool controle() = 0;
    // verwerk: afhandeling van een oplossing die opgeslagen is in
    // deeloplossing.
    virtual void verwerk() = 0;
    // geefVerdere: geef verzameling verderzettingen van de deeloplossing.
    virtual vector<knoop> geefVerdere() = 0;
    // Opgelet: deeloplossing is een vector van *pointers* naar knopen; de
    // knopen zelf zitten
    // in de vector mogelijkheid die lokaal gedeclareerd wordt in losOp
    vector<const knoop*> deeloplossing;
    int maxSom = -1;
};

template <class knoop>
void Backtrackflex<knoop>::losOp(bool zoekalle) {
    deeloplossing.clear();
    bool gedaan = false;
    losOp(gedaan, zoekalle);
    // Na deze stap is het programma afgelopen
    std::cout << "Oplossing is: " << this->maxSom << std::endl;
}

template <class knoop>
void Backtrackflex<knoop>::losOp(bool& gedaan, bool zoekalle) {
    if (controle()) {  // oplossing gevonden
        verwerk();

        if (!zoekalle) gedaan = true;
    }
    // bij sommige problemen kan een oplossing nog verlengd worden tot een
    // langere oplossing daarom moet het volgend stuk code ook worden uitgevoerd
    // als we een oplossing hebben.
    if (!gedaan) {
        // noot: het werken met referenties naar elementen van een vector is
        // alleen veilig als de vector onveranderlijk is.
        const vector<knoop> mogelijkheid(geefVerdere());
        int i = 0;
        while (i < mogelijkheid.size() && !gedaan) {
            voegToeAanDeeloplossing(mogelijkheid[i]);
            losOp(gedaan, zoekalle);
            verwijderUitDeeloplossing();
            i++;
        }
    }
}

template <class knoop>
void Backtrackflex<knoop>::voegToeAanDeeloplossing(const knoop& element) {
    deeloplossing.push_back(&element);
}

template <class knoop>
void Backtrackflex<knoop>::verwijderUitDeeloplossing() {
    deeloplossing.resize(deeloplossing.size() - 1);
}