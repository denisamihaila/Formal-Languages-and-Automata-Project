#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include <unordered_set>

using namespace std;

// Funcție de hash pentru pair<char, char>
struct pair_hash {
    inline size_t operator()(const pair<char, char>& v) const {
        return v.first * 31 + v.second;
    }
};

// Regula de producție = pereche de caractere
using Production = pair<char, char>;

// Gramatica =  map - key : variabila
//                  - value = set de reguli de producție
using Grammar = unordered_map<char, unordered_set<Production, pair_hash>>;

Grammar readGrammar(const string& filename) {
    Grammar grammar; // Gramatica care va fi construită
    ifstream f(filename);
    char left; // Partea stângă a unei producții
    string right; // Partea dreaptă a unei producții

    // Citim producțiile din fișier
    while (f >> left >> right) {
        if (right.length() == 1) { // Cazul când avem producții de forma A -> a
            grammar[left].insert(Production(right[0], ' '));
        } else if (right.length() == 2) { // Cazul când avem producții de forma A -> BC
            grammar[left].insert(Production(right[0], right[1]));
        }
    }

    return grammar;
}

bool cykAlgorithm(const Grammar& grammar, const string& word) {
    int n = word.length(); // Lungimea cuvântului

    // Tabelul triunghiular CYK, inițializat cu seturi goale
    //dp[i][j] = mulțimea variabilelor care pot genera substringul cuvântului începând de la poziția i și de lungime j-i+1
    vector<vector<unordered_set<char>>> dp(n, vector<unordered_set<char>>(n));

    // Inițializarea primei diagonale a tabelului CYK
    for (int i = 0; i < n; ++i) {
        for (const auto& rule : grammar) {
            if (rule.second.count(Production(word[i], ' '))) {
                dp[i][i].insert(rule.first);
            }
        }
    }

    // Completarea tabelului CYK
    for (int len = 2; len <= n; ++len) {
        for (int i = 0; i <= n - len; ++i) {
            int j = i + len - 1;
            for (int k = i; k < j; ++k) {
                for (const auto& rule : grammar) {
                    for (const auto& prod : rule.second) {
                        if (dp[i][k].count(prod.first) && dp[k + 1][j].count(prod.second)) {
                            dp[i][j].insert(rule.first);
                        }
                    }
                }
            }
        }
    }

    // Verificăm dacă simbolul de start (presupunem că este 'S') poate genera întregul cuvânt
    return dp[0][n - 1].count('S');
}

int main() {

    ifstream f("input.txt");
    ofstream g("output.txt");
    string line, word; //liniile citite și cuvântul
    Grammar grammar;

    // Citirea gramaticii din fișier
    while (getline(f, line) && !line.empty()) {
        char left = line[0]; // Partea stângă a producției
        string right = line.substr(2); // Partea dreaptă a producției
        if (right.length() == 1) {
            grammar[left].insert(Production(right[0], ' '));
        } else if (right.length() == 2) {
            grammar[left].insert(Production(right[0], right[1]));
        }
    }

    f >> word;

    bool belongsToLanguage = cykAlgorithm(grammar, word);

    if (belongsToLanguage) {
        g << "Cuvântul aparține limbajului definit de gramatică." << endl;
    } else {
        g << "Cuvântul nu aparține limbajului definit de gramatică." << endl;
    }

    return 0;
}




/*
dp[i][j] = variabilele care pot genera substringul cuvântului începând de la poziția i până la poziția j


i\j  0     1     2    3
0   {A,C} {S,C} {B}   {S}
1         {B}   {}    {}
2               {A,C} {A}
3                     {B}
*/
