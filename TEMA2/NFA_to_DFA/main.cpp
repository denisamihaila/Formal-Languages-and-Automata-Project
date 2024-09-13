#include <fstream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <queue>
#include <algorithm>

using namespace std;

ifstream f("input.txt");
ofstream g("output.txt");

class NFA
{
private:
    int nr_noduri, nr_muchii, start, nr_finale, noduri_finale[105];
    vector<int> v[105][35]; //vector de tranzitii: v[nod1][caracter - 'a'] = vector cu toate stările în care putem ajunge

public:
    NFA() : nr_noduri(0), nr_muchii(0), start(0), nr_finale(0)
    {
        for (int i = 0; i < 105; ++i)
        {
            noduri_finale[i] = 0;
        }
    }

    friend istream &operator>>(istream &in, NFA &nfa)
    {
        in >> nfa.nr_noduri >> nfa.nr_muchii >> nfa.start >> nfa.nr_finale;
        for (int i = 1; i <= nfa.nr_muchii; i++)
        {
            int x, y;
            char c;
            in >> x >> y >> c; //muchie de la x la y cu c
            nfa.v[x][c - 'a'].push_back(y); //
        }
        for (int i = 1; i <= nfa.nr_finale; i++)
            in >> nfa.noduri_finale[i];
        return in;
    };

    void NFAtoDFA()
    {
        vector<vector<int>> nodes; // nodes[i] = multimea de noduri din NFA care reprezinta nodul i din noul DFA.
        nodes.push_back(vector<int>());  // Indicele 0 este neocupat

        unordered_set<int> start_node;
        start_node.insert(start);
        nodes.push_back(vector<int>(start_node.begin(), start_node.end()));

        // Initial am indicele 1(pentru nodul de start al dfa-ului)
        // Dupa ce scot un indice din coada, pentru toate nodurile care reprezinta acel indice,
        // le iau vecinii(pentru fiecare litera), si impreuna toti vecinii reprezinta un nod din dfa(daca
        // aceasta multime de vecini nu exista deja).

        queue<int> que;
        que.push(1);

        int dfa[10005][35] = {0}; //tranzitiile din DFA
        while (!que.empty())
        {
            int index = que.front();
            vector<int> node_dfa = nodes[index];
            que.pop();
            for (int c = 0; c < 26; ++c) //de la a la z sunt 26 de caractere
            {
                unordered_set<int> new_node_dfa;
                for (int node : node_dfa) //adaug vecinii pt fiecare nod
                {
                    for (int i = 0; i < v[node][c].size(); ++i)
                    {
                        new_node_dfa.insert(v[node][c][i]);
                    }
                }
                // Daca nu am niciun vecin, atunci nu am tranzitie
                if (new_node_dfa.empty())
                {
                    continue;
                }

                int new_index = nodes.size();
                // Verific daca in nodes exista deja o multime cu aceleasi noduri din nfa
                bool exists = false;
                for (int i = 1; i < nodes.size(); ++i)
                {
                    if (nodes[i].size() != new_node_dfa.size())
                    {
                        continue;
                    }

                    bool equal = true;
                    for (int val : new_node_dfa)
                    {
                        if (find(node_dfa.begin(), node_dfa.end(), val) == node_dfa.end())
                        {
                            equal = false;
                            break;
                        }
                    }

                    if (equal)
                    {
                        exists = true;
                        new_index = i;
                        break;
                    }
                }

                if (!exists)
                {
                    nodes.push_back(vector<int>(new_node_dfa.begin(), new_node_dfa.end()));
                    que.push(new_index);
                }

                dfa[index][c] = new_index;
            }
        }

        for (int i = 1; i < nodes.size(); ++i)
        {
            g << "Nodul " << i << " = { ";
            for (int node : nodes[i])
            {
                g << node << " ";
            }
            g << "}\n";
        }
        g << "\n";

        for (int i = 1; i < nodes.size(); ++i)
        {
            for (int c = 0; c < 26; ++c)
            {
                if (dfa[i][c] != 0)
                {
                    g << i << " " << dfa[i][c] << " " << char(c + 'a') << "\n";
                }
            }
        }
    }
};

int main()
{
    NFA nfa;
    f >> nfa;
    nfa.NFAtoDFA();

    f.close();
    g.close();
    return 0;
}




