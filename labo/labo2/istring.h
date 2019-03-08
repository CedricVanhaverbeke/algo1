#ifndef __INTSTRING_H
#define __INTSTRING_H
#include <stdlib.h>
#include <cassert>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
using std::string;
using std::vector;
/** \class Intstring
 \brief stringklasse met een constructor die een getal gebruikt
 overerving van string is veilig: er worden geen extra gegevensvelden
 toegevoegd.
*/

class Intstring : public string {
    static const vector<string> duizendmacht;
    static const vector<string> cijfer;
    static const vector<string> tiental;

   public:
    static string kleinerDanDuizend(int a) {
        string uit;
        int ihonderd = a / 100;
        if (ihonderd > 1) uit += cijfer.at(ihonderd);
        if (ihonderd > 0) uit += "honderd";
        a = a - 100 * ihonderd;
        if (a < 20)
            uit += cijfer[a];
        else {
            if (a % 10) uit += cijfer[a % 10] + "en";
            uit += tiental[a / 10];
        };
        return uit;
    };
    Intstring(int a = 0) : string("") {
        string getal;
        if (a < 0) {
            getal = "min ";
            a = -a;
        };
        if (a >= 1000000000) {
            getal += cijfer[a / 1000000000] + " miljard ";
            a = a % 1000000000;
        }
        if (a > 1000000) {
            getal += kleinerDanDuizend(a / 1000000) + " miljoen ";
            a = a % 1000000;
        };
        if (a > 1000) {
            getal += kleinerDanDuizend(a / 1000) + "duizend ";
            a = a % 1000;
        };
        if (a > 0) getal += kleinerDanDuizend(a);
        if (getal == "") getal = "nul";
        string::swap(getal);
    };
    Intstring(Intstring&& v) : string(move(v)){};
    Intstring& operator=(Intstring&& v) {
        string::operator=(move(v));
        return *this;
    };
    Intstring& operator=(int i) {
        Intstring a(i);
        std::swap(*this, a);
        return *this;
    };
    Intstring(const Intstring& v) = delete;
    Intstring& operator=(const Intstring& v) = delete;
};
const std::vector<string> Intstring::duizendmacht = {
    ","
    "duizend ",
    " miljoen ", " miljard "};
const std::vector<string> Intstring::cijfer = {
    "",         "een",     "twee",      "drie",     "vier",
    "vijf",     "zes",     "zeven",     "acht",     "negen",
    "tien",     "elf",     "twaalf",    "dertien",  "veertien",
    "vijftien", "zestien", "zeventien", "achttien", "negentien"};
const std::vector<string> Intstring::tiental = {
    "",        "tien",   "twintig",  "dertig",  "veertig",
    "vijftig", "zestig", "zeventig", "tachtig", "negentig"};

#endif
;