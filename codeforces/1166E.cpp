/// submitted by Lauran on May 22, 2019
#include <bits/stdc++.h>
using namespace std;

const int NMAX = 1e4 + 5;

int n, m;
vector <int> v[NMAX];

bool comun(int a, int b)
{
    int pa = 0, pb = 0;
    while (pa < v[a].size() && pb < v[b].size())
    {
        if (v[a][pa] == v[b][pb])
            return 1;
        if (v[a][pa] < v[b][pb])
            pa++;
        else 
            pb++;
    }

    return 0;
}

int main()
{
    cin >> m >> n;

    for (int i = 1; i <= m; i++)
    {
        int l;
        cin >> l;
        for (int j = 1; j <= l; j++)
        {
            int x;
            cin >> x;
            v[i].push_back(x);
        }
    }

    for (int i = 1; i <= n; i++)
        sort(v[i].begin(), v[i].end());

    bool ok = 1;
    for (int i = 1; i <= m && ok; i++)
        for (int j = i + 1; j <= m && ok; j++)
            if (!comun(i, j))
                ok = 0;

    ok ? cout << "possible" : cout << "impossible";

    return 0;
}
