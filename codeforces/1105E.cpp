/// submitted by Lauran on January 30, 2019
#include <bits/stdc++.h>
#define int long long
using namespace std;

const int NMAX = 1e5 + 5;
const int MMAX = 50;

int n, m;
int k;
unordered_map <string, int> M;
vector <int> V;
bool incomp[MMAX][MMAX];
vector <int> G[MMAX];
int sz;
int vec[MMAX];
unordered_map <int, int> memo;

void getVec() // obtinem mastile vecinilor
{
    for (int i = 1; i <= m; i++)
        for (auto j: G[i])
            vec[i] |= (1LL << (j - 1));
}

int solve(int mask) // subgraf complet maxim al grafului determinat de masca
{
    if (mask == 0) // gata
        return memo[mask] = 0;
    if (memo[mask])
        return memo[mask];

    int nod = 1; // primul nod care apare
    while (!(mask & (1LL << (nod - 1))))
        nod++;

    // 1. nu il luam pe nod
    int rez = solve(mask ^ (1LL << (nod - 1)));
    // 2. il luam => 1 + solve(veciniiCareAparInMasca)
    rez = max(rez, 1 + solve(mask & vec[nod]));

    return memo[mask] = rez;
}

signed main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        int op;
        cin >> op;
        if (op == 1)
            V.clear(), sz = 0;
        else
        {
            string s;
            cin >> s;

            if (!M[s])
                M[s] = ++k;
            int cod = M[s];

            V.push_back(cod); sz++;
            for (int i = 0; i < sz - 1; i++)
                incomp[cod][V[i]] = incomp[V[i]][cod] = 1;
        }
    }

    for (int i = 1; i <= m; i++)
        for (int j = i + 1; j <= m; j++)
            if (!incomp[i][j])
            {
                G[i].push_back(j);
                G[j].push_back(i);
            }

    getVec();

    cout << solve((1LL << m) - 1);

    return 0;
}
