#include <bits/stdc++.h>
using namespace std;

const int NMAX = 2005;

int n;
vector <int> G[NMAX], H[NMAX];
int stiva[NMAX], kStiva;
int comp[NMAX], cntComp;
bool viz[NMAX], rad[NMAX];

void dfsKosaraju(int nod) {
    viz[nod] = 1;
    for (auto v: G[nod])
        if (!viz[v])
            dfsKosaraju(v);

    stiva[++kStiva] = nod;
}

void dfsInv(int nod) {
    comp[nod] = cntComp;
    for (auto v: H[nod])
        if (!comp[v]) {
            comp[v] = cntComp;
            dfsInv(v);
        }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        while (cin >> x) {
            if (x == 0)
                break;
            G[i].push_back(x);
            H[x].push_back(i);
        }
    }

    for (int i = 1; i <= n; i++)
        if (!viz[i])
            dfsKosaraju(i);

    while (kStiva) {
        int nod = stiva[kStiva--];
        if (!comp[nod]) {
            cntComp++;
            dfsInv(nod);
        }
    }

    // fac DAG-ul
    for (int i = 1; i <= cntComp; i++)
        rad[i] = 1;
    for (int i = 1; i <= n; i++)
        for (auto v: G[i])
            if (comp[i] != comp[v])
                rad[comp[v]] = 0;

    int ans = 0;
    for (int i = 1; i <= cntComp; i++) {
        if (rad[i]) {
            if (ans) {
                cout << 0;
                return 0;
            }
            ans = i;
        }
    }

    for (int i = 1; i <= n; i++)
        if (comp[i] == ans)
            cout << i << " ";
    cout << 0;

    return 0;
}

