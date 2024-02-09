#include <bits/stdc++.h>
using namespace std;
ifstream fi("amici.in");
ofstream fo("amici.out");

const int NMAX = 1005;

int G[NMAX][NMAX];
int n, m;
int v[NMAX];
int t;
int rez[NMAX];

int main()
{
    fi >> t;
    while (t--)
    {
        memset(G, 0, sizeof(G));

        fi >> n >> m;
        for (int i = 1; i <= m; i++)
        {
            int u, v;
            fi >> u >> v;
            G[u][v] = G[v][u] = 1;
        }

        for (int i = 1; i <= n; i++)
            G[i][i] = 1;

        for (int i = 1; i <= n; i++)
            v[i] = i;
        v[n + 1] = 1;

        bool imp = 0;
        while (1)
        {
            int poz = -1;
            for (int i = 1; i <= n; i++)
                if (G[v[i]][v[i + 1]])
                {
                    poz = i;
                    break;
                }

            if (poz == -1)
                break;

            int loc = -1;
            for (int i = 1; i <= n; i++)
                if (!G[v[i]][v[poz]] && !G[v[i + 1]][v[poz + 1]] && i != poz)
                {
                    loc = i;
                    break;
                }

            if (loc == -1)
            {
                imp = 1;
                break;
            }

            if (loc < poz)
                reverse(v + loc + 1, v + poz + 1);
            else
                reverse(v + poz + 1, v + loc + 1);
        }

        if (imp)
        {
            fo << "-1\n";
            continue;
        }

        for (int i = 1; i <= n; i++)
            rez[v[i]] = v[i + 1];

        for (int i = 1; i <= n; i++)
            fo << rez[i] << " ";
        fo << "\n";
    }

    return 0;
}
