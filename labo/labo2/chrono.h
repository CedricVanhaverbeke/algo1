#ifndef __CHRONO
#define __CHRONO

#include <ctime>

class Chrono {
   public:
    Chrono();
    void start();
    void stop();
    // tijd is de tijd verlopen tussen de laatste keer dat stop() is opgeroepen
    // en de laatste keer dat start() is opgeroepen
    double tijd() const;

   private:
    clock_t begin, einde;
};

Chrono::Chrono() {}

void Chrono::start() { begin = clock(); }

void Chrono::stop() { einde = clock(); }

double Chrono::tijd() const {
    return static_cast<double>(einde - begin) / CLOCKS_PER_SEC;
}

#endif