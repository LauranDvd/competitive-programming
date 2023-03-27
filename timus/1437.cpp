/// submitted by David Lauran on August 29, 2018
#include <bits/stdc++.h>
#define ll long long
using namespace std;

unordered_map <ll, bool> M;
ll rez;
ll ta, tb, tc;
bool F[5000];

void dfs(ll a, ll b, ll c)
{
   if (M[(a << 16LL) + (b << 8LL) + c]) // am mai avut aceeasi configuratie
      return;
   M[(a << 16LL) + (b << 8LL) + c] = 1;

   // adaugam fiecare suma posibila
   for (int i = 0; i <= 1; i++)
      for (int j = 0; j <= 1; j++)
         for (int k = 0; k <= 1; k++)
            if (!F[a * i + b * j + c * k])
            {
               rez++, F[a * i + b * j + c * k] = 1;
               //cout << a * i + b * j + c * k << "\n";
            }


   // fill-am unul dintre ele
   dfs(ta, b, c);
   dfs(a, tb, c);
   dfs(a, b, tc);

   dfs(min(ta, a + b), a + b - min(ta, a + b), c);
   dfs(min(ta, a + c), b, a + c - min(ta, a + c));
   dfs(a + b - min(tb, a + b), min(tb, a + b), c);
   dfs(a, min(tb, b + c), b + c - min(tb, b + c));
   dfs(a + c - min(tc, a + c), b, min(tc, a + c));
   dfs(a, b + c - min(tc, b + c), min(tc, b + c));
}

signed main()
{
   ios_base::sync_with_stdio(false);
   cin.tie(0);
   cin >> ta >> tb >> tc;
   F[0] = 1;
   dfs(0, 0, 0);
   cout << rez;
   return 0;
}
