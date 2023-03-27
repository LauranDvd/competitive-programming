/// submitted by David Lauran on August 18, 2018
#include <bits/stdc++.h>
using namespace std;

const int NMAX = 2005;
const int INF = 4000005;
const int MOD = 1000000007;

char A[NMAX], B[NMAX];
int l[NMAX][NMAX], dp[NMAX][NMAX];
int n, m;
int main()
{
   cin >> A + 1 >> B + 1;
   n = strlen(A + 1);
   m = strlen(B + 1);

   for (int i = 0; i <= n; i++)
      dp[i][0] = 1;
   for (int j = 0; j <= m; j++)
      dp[0][j] = 1;

   for (int i = 1; i <= n; i++)
   {
      for (int j = 1; j <= m; j++)
      {
         l[i][j] = max(l[i - 1][j], l[i][j - 1]);
         if (A[i] == B[j])
            l[i][j] = max(l[i][j], l[i - 1][j - 1] + 1);

         if (l[i - 1][j - 1] + 1 == l[i][j] && A[i] == B[j])
            dp[i][j] = (dp[i][j] + dp[i - 1][j - 1]) % MOD;
         else
         {
            if (l[i][j] == l[i - 1][j])
               dp[i][j] = (dp[i][j] + dp[i - 1][j]) % MOD;
            if (l[i][j] == l[i][j - 1])
               dp[i][j] = (dp[i][j] + dp[i][j - 1]) % MOD;
         }
      }
   }
   cout << dp[n][m];
   return 0;
   
   for (int i = 1; i <= n; i++)
      for (int j = 1; j <= m; j++)
         cout << i << ", " << j << ": " << dp[i][j] << "\n";

   return 0;
}
