#include "Problem.h"
#include "iostream"
#include <algorithm>
#include <vector>


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
        int rj, pj, qj;
        if (!(f >> rj >> pj >> qj)) {
            std::cerr << "Błąd odczytu danych dla zadania!" << std::endl;
            return 3;
        }
        P.emplace_back(rj, pj, qj);
    }

    f.close();
    return 0;
}



void Problem::wyswietlZadania() const {
    for (const auto& zadanie : P) {
        std::cout << "R: " << zadanie.Rj << ", P: " << zadanie.Pj << ", Q: " << zadanie.Qj << std::endl;
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



void Problem::sortPoR(){
    std::sort(P.begin(), P.end(), [](const Zadanie& a, const Zadanie& b) {
        return a.Rj < b.Rj; 
    });
}



void Problem::sortPoQ(){
    std::sort(P.begin(), P.end(), [](const Zadanie& a, const Zadanie& b) {
        return a.Qj > b.Qj; 
    });
}


void Problem::sortPrzegZup(){

    int najszybciej = ileCzasuSort();
    std::vector<Zadanie> Najszybszy;
    std::vector<Zadanie> buff;

    Najszybszy = P;
    buff = P;

    // Tworzymy wektor indeksów pomocniczych
    std::vector<int> indices(P.size());
    for (int i = 0; i < P.size(); ++i) {
        indices[i] = i;
    }

    do {
        for (int i = 0; i < P.size(); ++i) {
            buff[i] = P[indices[i]];
        }

        P = buff;
        if(ileCzasuSort() < najszybciej){
            Najszybszy = P;
            najszybciej = ileCzasuSort();
            std::cout << ileCzasuSort() << "\n";
        }

    } while (std::next_permutation(indices.begin(), indices.end()));

    P = Najszybszy;
}



void Problem::sortShrage() {
    std::vector<Zadanie> N = P;
    std::vector<Zadanie> G;
    std::vector<Zadanie> nowyP;

    int t = 0;

    // posortuj N po r_j rosnąco
    std::sort(N.begin(), N.end(), [](const Zadanie& a, const Zadanie& b) {
        return a.Rj < b.Rj;
    });

    while (!G.empty() || !N.empty()) {
        // Przenoszenie zadań dostępnych w czasie t z N do G
        while (!N.empty() && N.front().Rj <= t) {
            G.push_back(N.front());
            N.erase(N.begin());
        }

        if (!G.empty()) {
            // Szukamy zadania o największym q_j
            auto it = std::max_element(G.begin(), G.end(), [](const Zadanie& a, const Zadanie& b) {
                return a.Qj < b.Qj;
            });

            Zadanie e = *it;
            G.erase(it);
            nowyP.push_back(e);
            t += e.Pj;
        } else {
            // Przeskocz czas do najbliższego zadania
            t = N.front().Rj;
        }
    }

    P = nowyP;
}



// sortowanie po R+Q
void Problem::sortWlasne(){

    std::sort(P.begin(), P.end(), [](const Zadanie& a, const Zadanie& b) {
        return a.Qj + a.Rj < b.Qj + b.Rj; 
    });

}