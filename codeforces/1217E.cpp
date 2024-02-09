#include <bits/stdc++.h>
using namespace std;

const int NMAX = 2e5 + 5;
const int INF = 2e9 + 5;

int n, q;
int x[NMAX], y[NMAX];
pair <int, int> aint[9][4 * NMAX];
int poz, val;
int min1, min2, st, dr;

void build(int ind, int nod, int l, int r)
{
    if (l == r)
    {
        if (y[l] % 10) // cifra nenula
            aint[ind][nod] = {x[l], INF};
        else 
            aint[ind][nod] = {INF, INF};
        return;
    }

    int mij = (l + r) / 2;
    build(ind, 2 * nod, l, mij);
    build(ind, 2 * nod + 1, mij + 1, r);

    aint[ind][nod] = {min(aint[ind][2 * nod].first, aint[ind][2 * nod + 1].first), max(aint[ind][2 * nod].first, aint[ind][2 * nod + 1].first)};
    aint[ind][nod].second = min(min(aint[ind][nod].second, aint[ind][2 * nod].second), aint[ind][2 * nod + 1].second);
}

void update(int ind, int nod, int l, int r)
{
    if (l == r)
    {
        aint[ind][nod] = {val, INF};
        return;
    }

    int mij = (l + r) / 2;
    if (poz <= mij)
        update(ind, 2 * nod, l, mij);
    else 
        update(ind, 2 * nod + 1, mij + 1, r);
    
    aint[ind][nod] = {min(aint[ind][2 * nod].first, aint[ind][2 * nod + 1].first), max(aint[ind][2 * nod].first, aint[ind][2 * nod + 1].first)};
    aint[ind][nod].second = min(min(aint[ind][nod].second, aint[ind][2 * nod].second), aint[ind][2 * nod + 1].second);
}

void query(int ind, int nod, int l, int r)
{
    if (st <= l && r <= dr)
    {
        if (aint[ind][nod].second <= min1) // actualizez ambele minime
            min1 = aint[ind][nod].first, min2 = aint[ind][nod].second;
        else if (aint[ind][nod].first <= min1) // actualizez min1 si cade pe min2
            min2 = min1, min1 = aint[ind][nod].first;
        else if (aint[ind][nod].first <= min2) // actualizez doar pe min2
            min2 = aint[ind][nod].first;

        return;
    }

    int mij = (l + r) / 2;
    if (st <= mij)
        query(ind, 2 * nod, l, mij);
    if (dr > mij)
        query(ind, 2 * nod + 1, mij + 1, r);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    
    cin >> n >> q;
    for (int i = 1; i <= n; i++)
        cin >> x[i];

    for (int i = 1; i <= n; i++)
        y[i] = x[i];

    for (int cif = 0; cif <= 8; cif++)
    {
        build(cif, 1, 1, n);

        for (int i = 1; i <= n; i++)
            y[i] /= 10;
    }

    while (q--)
    {
        int op, a, b;
        cin >> op >> a >> b;
        if (op == 1) // v[a] = b
        {
            int aux = b;
            for (int cif = 0; cif <= 8; cif++)
            {
                int aici = aux % 10; aux /= 10;

                poz = a;
                if (aici)
                    val = b;
                else 
                    val = INF;
                update(cif, 1, 1, n);
            }
        }
        else // query pe [a, b]
        {
            int ansQuery = INF;
            for (int cif = 0; cif <= 8; cif++)
            {
                min1 = INF; min2 = INF;
                st = a; dr = b;
                query(cif, 1, 1, n);
                ansQuery = min((long long)ansQuery, (long long)min1 + min2);
            }
            if (ansQuery <= 2e9)
                cout << ansQuery << "\n";
            else 
                cout << -1 << "\n";
        }
    }

    return 0;
}
