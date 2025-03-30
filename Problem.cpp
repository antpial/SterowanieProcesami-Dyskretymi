#include "Problem.h"

int Problem::zaladujZadaniaPlik(const std::string& NazwaPliku) {
    std::ifstream f(NazwaPliku);
    if (!f.is_open()) {
        std::cerr << "Error opening the file!" << std::endl;
        return 1;
    }

    int ile;
    if (!(f >> ile)) {
        std::cerr << "Błąd odczytu liczby zadań!" << std::endl;
        return 2;
    }

    for (int i = 0; i < ile; ++i) {
        int pj, rj, qj;
        if (!(f >> pj >> rj >> qj)) {
            std::cerr << "Błąd odczytu danych dla zadania!" << std::endl;
            return 3;
        }
        P.emplace_back(pj, rj, qj);
    }

    f.close();
    return 0;
}

void Problem::wyswietlZadania() const {
    for (const auto& zadanie : P) {
        std::cout << "P: " << zadanie.Pj << ", R: " << zadanie.Rj << ", Q: " << zadanie.Qj << std::endl;
    }
}

int Problem::ileCzasuSort() const {

    int czas = 0;
    int najdluzszyOgonek = 0;

    for(int i=0; i<P.size(); i++){  // co iteracje przechodzimy na kolejny element

        while(P[i].Rj > czas){   // jezeli nie mozemy zaczac nowego zadania czekamy, a w tym czasie ogonek sie wykonuje
            czas++;
            najdluzszyOgonek--;
        }

        czas += P[i].Pj;    // wykonujemy zadanie
        najdluzszyOgonek -= P[i].Pj;    //ogonek wykonuje sie razem z zadaniem

        if(najdluzszyOgonek < P[i].Qj)  // sprawdzamy czy dluzej zajmie wykonanie sie biezacego ogonka czy nowego
            najdluzszyOgonek = P[i].Qj;
    }

    if(najdluzszyOgonek > 0)    // sprawdzamy czy ogonek nam nie zostal
        czas+= najdluzszyOgonek;

    return czas;
}
