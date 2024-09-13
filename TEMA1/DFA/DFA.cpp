#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <map>
//1.automat finit determinist
using namespace std;
ifstream f("input.txt");
ofstream g("output.txt");
int stare, n, m, i, j, stare_finala, nrcuv, nod1, nod2, stare_init, nrf, stare_curenta;
char caracter;
vector<int> stari;
string s;
unordered_map<int, bool> fin; //true = e stare finala, false = nu e stare finala
map<pair<int, char>, int> muta; //(stare_curenta, litera) : stare_urmatoare

int verifica_cuv(string s)
{
    stare_curenta = stare_init;
    for(i=0; i<s.size(); i++)
    {
        if(muta[ {stare_curenta,s[i]}]==0) //din starea curenta nu pleaca o muchie cu litera s[i]
            return 0;
        else
            stare_curenta = muta[ {stare_curenta,s[i]}];
    }
    if (fin[stare_curenta] == 1)
        return 1;
    else
        return 0;

}

int main()
{
    f >> n; //nr de stari
    for(i=1; i<=n; i++)
    {
        f>>stare; //numărul stării
        stari.push_back(stare);
    }
    f >> m; //nr tranzitii
    for(i=1; i<=m; i++)
    {
        f>>nod1>>nod2;
        f>>caracter;
        muta[make_pair(nod1,caracter)]=nod2;
    }
    f>>stare_init;
    f>>nrf; //numarul de stari finale
    for(i=1; i<=nrf; i++)
    {
        f>>stare_finala; //numarul fiecărei stări finale
        fin[stare_finala] = true;
    }

    f>>nrcuv; //numărul de cuvinte de verificat
    for(i=1; i<=nrcuv; i++)
    {
        f>>s;//cuvantul de verificat
        if(verifica_cuv(s)==1)
            g<<"DA\n";
        else g<<"NU\n";
    }

    return 0;
}
