// implementatie van getallen.h

#include "getallen.h"
#include <algorithm>
#include <iostream>
#include <numeric>
#include <tuple>
#include <vector>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::string;

class BacktrackflexGetallen : public Backtrackflex<int> {
    // Constructor voor n
   public:
    BacktrackflexGetallen(int n) : n{n} {};
    bool controle() override;
    // verwerk: afhandeling van een oplossing die opgeslagen is in
    // deeloplossing.
    void verwerk() override;
    // geefVerdere: geef verzameling verderzettingen van de deeloplossing.
    vector<int> geefVerdere() override;

   private:
    int n;
};

bool BacktrackflexGetallen::controle() {
    // Deze functie controleert of een deeloplossing een oplossing is
    bool isOplossing = this->deeloplossing.size() == n;
   if (isOplossing) {
        int som = 0;
        for(int i = 0; i < n; i++){
            som += *(deeloplossing[i]);
        }
        if (som > this->maxSom)
            this->maxSom = som;
    }
    

    return isOplossing;
}

void BacktrackflexGetallen::verwerk() {
    // Hier zou je alle mogelijkheden kunnen printen
}

// methode van Simon
vector<int> BacktrackflexGetallen::geefVerdere() {
    vector<int> mogelijkheden;

    if (this->deeloplossing.size() < n) {
        int som_laaste_vier = 0;
        int aantal_bekeken = 0;

        // voorwaarde 1
        // Hier beginnen we achteraan naar voor zodat we nooit meer dan 12
        // krijgen, ook al zitten er nog geen 3 elementen in de array
        int i = this->deeloplossing.size() - 1;
        while (i >= 0 && aantal_bekeken < 3) {
            som_laaste_vier += *this->deeloplossing[i];
            i--;
            aantal_bekeken++;
        }
        int max_toegelaten = 12 - som_laaste_vier;

        for (int i = 1; i <= 9 && i <= max_toegelaten; i++) {
            bool canUse = true;

            // voorwaarde 3
            if (this->deeloplossing.size() >= 4 &&
                i == *this->deeloplossing[this->deeloplossing.size() - 4]) {
                canUse = false;
            }

            // voorwaarde 2, deel 1
            if (this->deeloplossing.size() >= 1 &&
                i == *this->deeloplossing[this->deeloplossing.size() - 1]) {
                canUse = false;
            }

            // voorwaarde 2, deel 2
            if (this->deeloplossing.size() >= 2 &&
                i == *this->deeloplossing[this->deeloplossing.size() - 2]) {
                canUse = false;
            }
            if (canUse) {
                mogelijkheden.emplace_back(i);
            }
        }
    }

    // std::reverse(mogelijkheden.begin(),mogelijkheden.end());
    return mogelijkheden;
}
