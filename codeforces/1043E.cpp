#include <bits/stdc++.h>
#define mp make_pair
#define ll long long
#define int long long
using namespace std;

const int NMAX = 300005;

int n, m;
ll x[NMAX], y[NMAX];
ll SX[NMAX], SY[NMAX];
pair <ll, ll> srt[NMAX];
ll rez[NMAX];

bool cmp(pair <ll, int> a, pair <int, int> b)
{
   return a.second - a.first <= b.second - b.first;
}

int calc(int a, int b)
{
   return min(x[a] + y[b], x[b] + y[a]);
}

int cauta(int x) // pana la ce pozitie e <= x
{
   int st = 1, dr = n + 1;
   if (srt[1].second - srt[1].first > x)
      return 0;

   while (dr - st > 1)
   {
      int mij = (st + dr) / 2;
      if (srt[mij].second - srt[mij].first <= x)
         st = mij;
      else
         dr = mij;
   }
   return st;
}


signed main()
{
   ios_base::sync_with_stdio(false);
   cin.tie(0);
   cin >> n >> m;
   for (int i = 1; i <= n; i++)
   {
      cin >> x[i] >> y[i];
      srt[i] = {x[i], y[i]};
   }

   sort(srt + 1, srt + n + 1, cmp);

   for (int i = 1; i <= n; i++)
   {
      SX[i] = SX[i - 1] + srt[i].first;
      SY[i] = SY[i - 1] + srt[i].second;
   }

   for (int i = 1; i <= n; i++)
   {
      int a = x[i], b = y[i];

      // 1. a + y[j] <=> y[j] - x[j] <= b - a

      int poz = cauta(b - a);

      int caz1 = poz;
      int caz2 = n - caz1;

      if (i <= poz)
         caz1--;
      else
         caz2--;

      rez[i] = SY[poz] + a * caz1 + SX[n] - SX[poz] + b * caz2;
      if (i <= poz)
         rez[i] -= y[i];
      else
         rez[i] -= x[i];
   }

   for (int i = 1; i <= m; i++)
   {
      int u, v;
      cin >> u >> v;
      rez[u] -= calc(u, v);
      rez[v] -= calc(u, v);
   }

   for (int i = 1; i <= n; i++)
      cout << rez[i] << " ";

   return 0;
}

