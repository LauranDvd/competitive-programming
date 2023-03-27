/// submitted by Lauran on August 3, 2018
#include <iostream>
#include <vector>
#define MAX 1000005
using namespace std;
#define X first
#define Y second

int aib[MAX], cnt[MAX];
vector <int> v[MAX];
vector < pair <int, int> > q[MAX];
int n, m;
int ans[MAX], p[MAX];

int query(int poz)
{
     int s = 0;
     for (; poz <= 1000000; poz += (poz & -poz))
         s += aib[poz];
     return s;
}

void update(int poz, int val)
{
     if (!val)
        return;
     for (; poz; poz -= poz & (-poz))
         aib[poz] += val;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin >> n >> m;

    for (int i = 1; i <= n; i++)
    {
        int l, r;
        cin >> l >> r;
        cnt[l]++;
        v[r + 1].push_back(l);
    }

    for (int i = 1; i <= m; i++)
    {
        int t;
        cin >> t;
        for (int j = 1; j <= t; j++)
        {
            cin >> p[j];
            q[p[j]].push_back(make_pair(p[j - 1], i));
        }
    }

    for (int i = 1; i <= 1000000; i++)
    {
        update(i, cnt[i]);

        for (int j = 0; j < v[i].size(); j++) /// stergem segmentele disparute
            update(v[i][j], -1);
        for (int j = 0; j < q[i].size(); j++) /// ce a fost inainte de pct. asta in query-uri
        {
            int p = q[i][j].first + 1;
            ans[q[i][j].second] += query(p);
        }
    }

    for (int i = 1; i <= m; ++i)
        cout << ans[i] << "\n";
}

