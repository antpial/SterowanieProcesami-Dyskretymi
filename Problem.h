#include <iostream>
#include <fstream>
#include <vector>

#include "Zadanie.h"

class Problem {
public:
    std::vector<Zadanie> P;

    int zaladujZadaniaPlik(const std::string& NazwaPliku);
    void wyswietlZadania() const;
    int ileCzasuSort() const;

    void sortPoR();
    void sortPoQ();
    void sortPrzegZup();
    void sortShrage();
};
