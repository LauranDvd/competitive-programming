#include <bits/stdc++.h>
#define int long long
using namespace std;

const int NMAX = 2e5 + 5;

struct triplet {int p, q, cost;};

bool comp(triplet a, triplet b)
{
    return a.cost < b.cost;
}

int n, q;
triplet much[NMAX];
pair <int, int> query[NMAX];
int p[NMAX], cnt[NMAX];
int rez;
int ans[NMAX];

void initDsu()
{
    for (int i = 1; i <= n; i++)
    {
        p[i] = i;
        cnt[i] = 1;
    }
}

int getParinte(int nod)
{
    if (p[nod] == nod)
        return nod;
    return p[nod] = getParinte(p[nod]);
}

void unite(int x, int y)
{
    /// x in y
    int px = getParinte(x), py = getParinte(y);
    rez = rez - cnt[px] * (cnt[px] - 1) / 2 - cnt[py] * (cnt[py] - 1) / 2 +
                                        (cnt[px] + cnt[py]) * (cnt[px] + cnt[py] - 1) / 2;
    p[px] = py;
    cnt[py] += cnt[px];
}

signed main()
{
    cin >> n >> q;
    for (int i = 1; i < n; i++)
    {
        int u, v, c;
        cin >> u >> v >> c;
        much[i] = {u, v, c};
    }

    sort(much + 1, much + n, comp);

    for (int i = 1; i <= q; i++)
    {
        cin >> query[i].first;
        query[i].second = i;
    }

    sort(query + 1, query + q + 1);

    initDsu();

    int currM = 0;
    for (int i = 1; i <= q; i++)
    {
        while (currM < n - 1 && much[currM + 1].cost <= query[i].first)
        {
            currM++;
            unite(much[currM].p, much[currM].q);
        }
        ans[query[i].second] = rez;
    }

    for (int i = 1; i <= q; i++)
        cout << ans[i] << " ";

    return 0;
}

