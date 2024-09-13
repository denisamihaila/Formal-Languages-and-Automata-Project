#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#define N 1005

using namespace std;
ofstream g("output.txt");

class DFA {
private:
    int nr_noduri, nr_muchii;
    int stare_initiala;
    int nr_finale;
    bool stari_finale[N];
    bool matrice_MN[N][N]; // Matricea utilizată în Teorema Myhill-Nerode - matrice de stari echivalente: true = neechivalente
    int tabel_tranzitii[N][26];
    bool inaccesibile[N];
    int grupe[N], nr_grupe, grupa_initiala;     // Grupările rezultate din minimizarea DFA-ului
    bool grupa_finala[N]; // Grupurile care conțin stări finale
    bool neaccesibil[N]; // Grupurile de stări inaccesibile
    string GRUP[N];   // Array de stringuri care conține reprezentările text ale grupurilor de stări.
    int tabDFA[N][26];  // Tabelul de tranziții al DFA-ului minimal

    // Funcție pentru identificarea nodurilor inaccesibile
    void noduri_inaccesibile(int nod) {
        inaccesibile[nod] = false;
        for (int litera = 0; litera < 26; ++litera) {
            int vecin = tabel_tranzitii[nod][litera];
            if (vecin != -1 && inaccesibile[vecin]) {
                noduri_inaccesibile(vecin);
            }
        }
    }

public:
    DFA() : nr_noduri(0), nr_muchii(0), stare_initiala(0), nr_finale(0), nr_grupe(0), grupa_initiala(0)
    {
        for (int i = 0; i < N; ++i) {
            stari_finale[i] = false;
            inaccesibile[i] = true; // Initial toate starile sunt marcate ca inaccesibile
            grupe[i] = 0; // Initial nu avem nicio grupare facuta
            grupa_finala[i] = false; // Initial nicio grupa nu este finala
            neaccesibil[i] = false; // Initial presupunem ca toate grupurile sunt accesibile
            for (int j = 0; j < N; ++j) {
                matrice_MN[i][j] = false;
            }
            for (int j = 0; j < 26; ++j) {
                tabel_tranzitii[i][j] = -1; // Marcam cu -1, stand pentru "fara tranzitie"
            }
        }
    }

    void minimizare(string nume_fisier)
    {
        ifstream fin(nume_fisier);
        fin >> nr_noduri >> nr_muchii;

        //citim tranzitiile
        for (int i = 0; i < nr_muchii; ++i) {
            int nod1, nod2;
            char c;
            fin >> nod1 >> nod2 >> c;
            tabel_tranzitii[nod1][c - 'a'] = nod2;
        }

        fin >> stare_initiala;

        //marcăm stările inaccesibile
        for (int i = 0; i <= nr_muchii / 2; ++i)
            inaccesibile[i] = true;
        inaccesibile[stare_initiala] = false;
        noduri_inaccesibile(stare_initiala);
        for (int i = 0; i <= nr_muchii / 2; ++i)
            if (tabel_tranzitii[i][0] == i && tabel_tranzitii[i][1] == i)
                inaccesibile[i] = true;

        fin >> nr_finale;
        for (int i = 0; i < nr_finale; ++i) {
            int f;
            fin >> f;
            stari_finale[f] = true;
        }

        // Efectuăm primul pas, marcând perechile (Qa, Qb) și (Qb, Qa) = 1
        // unde Qa este stare finală, iar Qb nu este stare finală
        nr_muchii = nr_muchii / 2;
        for (int i = 1; i <= nr_muchii; ++i)
            for (int j = 1; j < i; ++j)
                if (stari_finale[i] != stari_finale[j])
                    matrice_MN[i][j] = matrice_MN[j][i] = true;

        // Iterăm asupra matricei și marcăm perechile echivalente
        // repetând acest proces până când nu se mai fac modificări

        //NOTĂ: Pentru fiecare pereche neechivalentă de stări (p, q), verificăm tranzițiile lor pentru fiecare simbol din alfabet.
        //Dacă pentru un simbol a, tranziția din p merge în starea r, iar din q merge în starea s, și perechea (r, s) este deja marcată ca neechivalentă,
        //atunci marchează (p, q) ca fiind neechivalente
        bool valid = false;
        while (!valid) {
            valid = true;
            for (int i = 1; i <= nr_muchii; ++i) {
                for (int j = 1; j < i; ++j) {
                    if (matrice_MN[i][j] == false) {
                        if (matrice_MN[tabel_tranzitii[i][0]][tabel_tranzitii[j][0]] == true || matrice_MN[tabel_tranzitii[i][1]][tabel_tranzitii[j][1]] == true)
                            {
                            matrice_MN[i][j] = matrice_MN[j][i] = true;
                            valid = false; // Am făcut modificări -> repetăm procesul
                            }
                    }
                }
            }
        }

        // Grupăm stările în funcție de valorile nule din matrice
        // matrice_MN[i][j] == false (echivalente) -> grupăm i cu j
        for (int i = 1; i <= nr_muchii; ++i) {
            for (int j = 1; j < i; ++j) {
                if (matrice_MN[i][j] == false) {
                    if (!grupe[i] && !grupe[j]) {
                        nr_grupe++;
                        grupe[i] = grupe[j] = nr_grupe;
                    } else if (grupe[j] == 0)
                        grupe[j] = grupe[i];
                    else
                        grupe[i] = grupe[j];
                }
            }
        }

        // Trecem și grupele formate dintr-o singură stare
        for (int i = 1; i <= nr_muchii; ++i)
            if (grupe[i] == 0)
                grupe[i] = ++nr_grupe;

        // Căutăm grupa care conține starea inițială și o marcăm ca fiind grupa inițială
        grupa_initiala = grupe[stare_initiala];

        // Construim DFA-ul minimal bazat pe grupurile formate
        int ct = 0;
        for (int i = 1; i <= nr_grupe; ++i) {
            stringstream ss;
            ss << "(";
            for (int j = 1; j <= nr_muchii; ++j) {
                if (grupe[j] == i) {
                    tabDFA[i][0] = grupe[tabel_tranzitii[j][0]];
                    tabDFA[i][1] = grupe[tabel_tranzitii[j][1]];
                    ss << j;
                    if (stari_finale[j] == true && grupa_finala[i] == false) {
                        grupa_finala[i] = true;
                        ct++;
                    }
                    if (inaccesibile[j] == true)
                        neaccesibil[i] = true;
                }
            }
            ss << ")";
            ss >> GRUP[i];
        }

        g << "DFA-ul minimal are urmatoarea forma: \n";
        for (int i = 1; i <= nr_grupe; ++i) {
            if (neaccesibil[i] != true) {
                if (neaccesibil[tabDFA[i][0]] != true)
                    g << GRUP[i] << " " << GRUP[tabDFA[i][0]] << " a" << "\n";
                if (neaccesibil[tabDFA[i][1]] != true)
                    g << GRUP[i] << " " << GRUP[tabDFA[i][1]] << " b" << "\n";
            }
        }
        g << "\nGrupa initiala este: " << GRUP[grupa_initiala] << "\n";
        if (ct > 1)
            g << "Starile finale sunt grupurile: ";
        else
            g << "Starea finala este grupa: ";
        for (int i = 0; i <= nr_muchii; ++i)
            if (grupa_finala[i] == true)
                g << GRUP[i] << " ";
        g << "\n";
    }
};

int main() {
    DFA dfa;
    dfa.minimizare("input.txt");
    return 0;
}
