#include <bits/stdc++.h>
using namespace std;
ifstream fi("drumuri5.in");
ofstream fo("drumuri5.out");
#define cin fi
#define cout fo
 
const int NMAX = 150005;

int n, m;
vector <int> G[NMAX], inv[NMAX], aciclic[NMAX];
set <int> S[NMAX];
bool viz[NMAX];
int stiva[NMAX], kStiva;
int nrComp;
vector <int> vComp[NMAX];
int comp[NMAX];
int in[NMAX], out[NMAX], drumMax[NMAX];
vector <int> nodCuDrum[NMAX];
 
void kosa(int nod)
{
    viz[nod] = 1;
    for (auto v: G[nod])
        if (!viz[v])
        {
            kosa(v);
        }
    stiva[++kStiva] = nod;
}
 
void dfs(int nod)
{
    comp[nod] = nrComp;
    vComp[nrComp].push_back(nod);
 
    for (auto v: inv[nod])
        if (!comp[v])
            dfs(v);
}
 
void faScc()
{
    for (int i = 1; i <= n; i++)
        if (!viz[i])
            kosa(i);
 
    while (kStiva)
    {
        int nod = stiva[kStiva--];
        if (!comp[nod])
        {
            nrComp++;
            dfs(nod);
        }
    }
}
 
void getDrumMax(int nod)
{
    drumMax[nod] = 1;
 
    for (auto v: aciclic[nod])
    {
        if (drumMax[v] == 0)
        {
            getDrumMax(v);
        }
        drumMax[nod] = max(drumMax[nod], drumMax[v] + 1);
    }
}
 
int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        inv[v].push_back(u);
    }

    faScc();
    
    for (int i = 1; i <= n; i++)
        for (auto v: G[i])
        {
            int gr1 = comp[i], gr2 = comp[v];
            if (gr1 != gr2)
                S[gr1].insert(gr2);
        }
 
    for (int i = 1; i <= nrComp; i++)
        for (auto x: S[i])
        {
            aciclic[i].push_back(x);
            out[i]++;
            in[x]++;
        }
 
    for (int i = 1; i <= nrComp; i++)
        if (drumMax[i] == 0)
            getDrumMax(i);


    /*for (int i = 1; i <= nrComp; i++)
        cout << vComp[i][0] << " ";
        return 0;
*/
    /*for (int i = 1; i <= nrComp; i++)
        cout << drumMax[i] << " ";
    return 0; */


 
    for (int i = 1; i <= nrComp; i++)
        nodCuDrum[drumMax[i]].push_back(i);

    set <int> T;
 
    int distMax = -1;
    for (int i = 1; i <= nrComp; i++)
        if (in[i] == 0)
        {
            T.insert(i);
            if (drumMax[i] == distMax)
                ;
            else if (drumMax[i] > distMax)
            {
                distMax = drumMax[i];
            }
        }
 
    vector <int> rezComp;
    while (!T.empty() && distMax >= 0)
    {
        if (T.size() == 1)
        {
            int nod = (*T.begin());
            rezComp.push_back(nod);
            T.erase(nod);
 
            for (auto v: aciclic[nod])
            {
                in[v]--;
                if (in[v] == 0)
                    T.insert(v);
            }
 
            distMax--;
        }
 
        else 
        {
            for (auto nod: nodCuDrum[distMax])
                //if (T.find(nod) != T.end())
                {
                    T.erase(nod);
                    for (auto v: aciclic[nod])
                    {
                        in[v]--;
                        if (in[v] == 0)
                            T.insert(v);
                    }
                }
            distMax--;
        }
    }
    
    vector <int> rezNoduri;
    for (auto x: rezComp)
        for (auto y: vComp[x])
            rezNoduri.push_back(y);

    sort(rezNoduri.begin(), rezNoduri.end());

    cout << rezNoduri.size() << "\n";
    for (auto x: rezNoduri)
        cout << x << " ";
 
    return 0;
}
