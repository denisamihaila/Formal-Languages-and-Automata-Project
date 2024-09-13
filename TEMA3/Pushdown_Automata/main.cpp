//automat pushdown nedeterminist (NPDA)

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <tuple>

using namespace std;

struct Transition {
    char inputSymbol;
    char stackSymbol;
    string nextState;
    string newStackSymbols;
};

// Tranzitii asociate unei stari
using Transitions = unordered_multimap<string, Transition>;
// Set de stari
using StateSet = unordered_set<string>;

struct PushdownAutomaton {
    StateSet states;              // Setul de stari ale automatului
    StateSet inputAlphabet;       // Alfabetul de intrare
    StateSet stackAlphabet;       // Alfabetul stivei
    Transitions transitions;      // Tranzitiile automatului
    string initialState;          // Starea initiala
    StateSet finalStates;         // Starile finale
    char initialStackSymbol;      // Simbolul initial din varful stivei
};

bool simulatePDA(const PushdownAutomaton& pda, const string& word, int position, string currentState, stack<char> st) {
    // Verifica daca am ajuns la sfarsitul cuvantului
    if (position == word.length()) {
        // Daca stiva contine simbolul initial si starea curenta este finala, cuvantul este acceptat
        if (st.top() == pda.initialStackSymbol && pda.finalStates.find(currentState) != pda.finalStates.end()) {
            return true;
        }
    }

    // Obtine tranzitiile posibile pentru starea curenta
    auto range = pda.transitions.equal_range(currentState);
    for (auto it = range.first; it != range.second; ++it) {
        const Transition& trans = it->second;
        // Verifica daca tranzitia este posibila (simbolul de intrare si simbolul din varful stivei se potrivesc)
        if ((trans.inputSymbol == '0' || (position < word.length() && trans.inputSymbol == word[position])) &&
            (st.empty() || st.top() == trans.stackSymbol)) {
            stack<char> newStack(st); // Creeaza o noua stiva pentru a simula tranzitia
            // Scoate simbolul din varful stivei daca este necesar
            if (!newStack.empty() && newStack.top() == trans.stackSymbol) {
                newStack.pop();
            }
            // Adauga noile simboluri in stiva
            for (auto rit = trans.newStackSymbols.rbegin(); rit != trans.newStackSymbols.rend(); ++rit) {
                if (*rit != '0') {
                    newStack.push(*rit);
                }
            }
            if (simulatePDA(pda, word, trans.inputSymbol == '0' ? position : position + 1, trans.nextState, newStack)) {
                return true; // Daca aceasta ramura accepta cuvantul
            }
        }
    }
    return false; // Daca nicio tranzitie nu duce la acceptarea cuvantului
}

bool isAcceptedByPDA(const PushdownAutomaton& pda, const string& word) {
    stack<char> initialStack; // Creeaza stiva initiala
    initialStack.push(pda.initialStackSymbol); // Adauga simbolul initial in stiva
    // Incepe simularea de la starea initiala, pozitia 0 in cuvant si stiva initiala
    return simulatePDA(pda, word, 0, pda.initialState, initialStack);
}

int main() {
    ifstream f("input.txt");
    ofstream g("output.txt");

    PushdownAutomaton pda;
    int numStates, numInputSymbols, numStackSymbols, numTransitions;
    string state, inputSymbol, stackSymbol, nextState, newStackSymbols;

    // Starile automatului
    f >> numStates;
    while (numStates--) {
        f >> state;
        pda.states.insert(state);
    }

    // Alfabetul de intrare
    f >> numInputSymbols;
    while (numInputSymbols--) {
        f >> inputSymbol;
        pda.inputAlphabet.insert(inputSymbol);
    }

    // Alfabetul stivei
    f >> numStackSymbols;
    while (numStackSymbols--) {
        f >> stackSymbol;
        pda.stackAlphabet.insert(stackSymbol);
    }

    // Tranzitiile
    f >> numTransitions;
    while (numTransitions--) {
        f >> state >> inputSymbol >> stackSymbol >> nextState >> newStackSymbols;
        Transition transition = {inputSymbol[0], stackSymbol[0], nextState, newStackSymbols};
        pda.transitions.emplace(state, transition);
    }

    // Starea initiala + simbolul initial al stivei
    f >> pda.initialState >> pda.initialStackSymbol;

    // Starile finale
    int numFinalStates;
    f >> numFinalStates;
    while (numFinalStates--) {
        f >> state;
        pda.finalStates.insert(state);
    }

    string word;
    f >> word;

    bool accepted = isAcceptedByPDA(pda, word);

    g << (accepted ? "Cuvantul " + word + " apartine limbajului definit de automat." : "Cuvantul " + word + " nu apartine limbajului definit de automat.") << endl;

    f.close();
    g.close();

    return 0;
}
