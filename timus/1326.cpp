#include <bits/stdc++.h>
#define pb push_back
using namespace std;

const int INF = 1000000;

vector <int> oferta[125];
int m, n, vrea;
int dp[2][1 << 21];

int main()
{
   ios_base::sync_with_stdio(false);
   cin >> n;
   for (int i = 1; i <= n; i++)
   {
      int pret;
      cin >> pret;
      oferta[i].pb(pret);
      oferta[i].pb(1);
      oferta[i].pb(i - 1);
   }
   cin >> m;
   for (int i = 1; i <= m; i++)
   {
      int pret, nr;
      cin >> pret >> nr;
      oferta[n + i].pb(pret);
      oferta[n + i].pb(nr);
      for (int j = 1; j <= nr; j++)
      {
         int asd;
         cin >> asd;
         asd--;
         oferta[n + i].pb(asd);
      }
   }

   /*for (int i = 1; i <= n + m; i++)
   {
      for (auto x: oferta[i])
         cout << x << " ";
      cout << "\n";
   }*/

   int ideal = 0;
   int total, unu;
   cin >> total;
   for (int i = 1; i <= total; i++)
   {
      cin >> unu;
      unu--;
      ideal |= (1 << unu);
   }

   int cnt = 1;
   dp[1 - cnt][0] = 0;
   for (int mask = 1; mask < (1 << n); mask++)
      dp[1 - cnt][mask] = INF;
   for (int i = 1; i <= n + m; i++)
   {
      for (int j = 0; j < (1 << n); j++)
         dp[cnt][j] = INF;
      dp[cnt][0] = 0;
      for (int mask = 1; mask < (1 << n); mask++)
      {
         int rest = mask;
         for (int j = 2; j < oferta[i].size(); j++)
            rest &= (~(1 << oferta[i][j]));
         dp[cnt][mask] = min(dp[1 - cnt][mask], dp[1 - cnt][rest] + oferta[i][0]);
      }
      cnt = 1 - cnt;
   }
   cout << dp[1 - cnt][ideal];
   return 0;
}

