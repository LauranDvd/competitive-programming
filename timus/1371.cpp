/// submitted by David Lauran on September 24, 2018
#pragma comment(linker, "/STACK:16777216")
#include <bits/stdc++.h>
#define pb push_back
#define int long long
using namespace std;

const int NMAX = 50005;

vector <pair<int, int>> G[NMAX];
int dp[NMAX];
int fii[NMAX];
int n;

void getFii(int nod, int parinte)
{
   fii[nod] = 1;
   for (auto v: G[nod])
   {
      if (v.first == parinte)
         continue;

      getFii(v.first, nod);
      fii[nod] += fii[v.first];
   }
}

int dfs(int nod, int parinte)
{
   int rez = 0;
   for (auto v: G[nod])
   {
      if (v.first == parinte)
         continue;
      rez += dfs(v.first, nod);
   }

   for (auto xyz: G[nod])
   {
      int v = xyz.first;
      int w = xyz.second;

      if (v == parinte)
         continue;
      dp[nod] += dp[v] + w * fii[v];

      rez += (dp[v] + w * fii[v]) * (fii[nod] - fii[v]);
   }
   return rez;
}

signed main()
{
   ios_base::sync_with_stdio(false);
   cin.tie(0);
   cin >> n;
   for (int i = 1; i < n; i++)
   {
      int u, v, c;
      cin >> u >> v >> c;
      G[u].pb({v, c});
      G[v].pb({u, c});
   }
   getFii(1, -1);
   int rez = dfs(1, -1);
   cout << fixed << setprecision(10) << double((2.00 * rez) / (n * (n - 1)));

   return 0;
}
