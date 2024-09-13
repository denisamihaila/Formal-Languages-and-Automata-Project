#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include <algorithm>

using namespace std;

struct Transition {
    string startState;
    char inputSymbol;
    char outputSymbol;
    string endState;
};

int main() {
    ifstream f("input.txt");
    ofstream g("output.txt");

    int numStates, numInputSymbols, numOutputSymbols, numTransitions;
    f >> numStates; // Numarul de stari

    vector<string> states(numStates); // Vectorul cu stari
    for (int i = 0; i < numStates; ++i) {
        f >> states[i]; // Starile
    }

    f >> numInputSymbols; // Numarul de simboluri de intrare
    vector<char> inputAlphabet(numInputSymbols); // Vector cu alfabetul de intrare
    for (int i = 0; i < numInputSymbols; ++i) {
        f >> inputAlphabet[i]; // Alfabetul de intrare
    }

    f >> numOutputSymbols; // Numarul de simboluri de iesire
    vector<char> outputAlphabet(numOutputSymbols); // Vector cu alfabetul de iesire
    for (int i = 0; i < numOutputSymbols; ++i) {
        f >> outputAlphabet[i]; // Alfabetul de iesire
    }

    f >> numTransitions; // Numarul de tranzitii
    vector<Transition> transitions(numTransitions); // Vector cu tranzitiile
    for (int i = 0; i < numTransitions; ++i) {
        f >> transitions[i].startState >> transitions[i].inputSymbol >> transitions[i].outputSymbol >> transitions[i].endState;
    }

    string initialState;
    f >> initialState;

    int numFinalStates;
    f >> numFinalStates;
    vector<string> finalStates(numFinalStates);
    for (int i = 0; i < numFinalStates; ++i) {
        f >> finalStates[i];
    }

    string word;
    f >> word;

    string currentState = initialState; // Setam starea curenta ca fiind starea initiala
    string outputWord = ""; // Initializam cuvantul de iesire

    for (char symbol : word) {
        bool transitionFound = false;
        for (const auto& t : transitions) {
            // Verificam daca exista o tranzitie valida pentru starea si simbolul curent
            if (t.startState == currentState && t.inputSymbol == symbol) {
                currentState = t.endState; // Schimbam starea curenta
                outputWord += t.outputSymbol; // Adaugam simbolul de iesire la cuvantul de iesire
                transitionFound = true; // Marcam ca am gasit o tranzitie
                break; // Iesim din bucla deoarece am gasit o tranzitie valida
            }
        }
        if (!transitionFound) {
            g << "Nicio tranzitie valida pentru simbolul: " << symbol << endl;
            return 1;
        }
    }

    // Verificam daca starea curenta este una dintre starile finale
    bool isFinalState = find(finalStates.begin(), finalStates.end(), currentState) != finalStates.end();
    if (isFinalState) {
        g << outputWord << endl;
    } else {
        g << "Starea finala nu este valida." << endl;
        return 1;
    }

    f.close();
    g.close();

    return 0;
}
