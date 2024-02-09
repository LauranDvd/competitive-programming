#include <bits/stdc++.h>
#define int long long
using namespace std;

const int NMAX = 35;
const int CMAX = 150;

struct numar
{
   short nrc;
   short C[CMAX];
};

void init(numar &A, int val)
{
   A.nrc = 1;
   A.C[1] = val;
   for (int i = 2; i < CMAX; i++)
      A.C[i] = 0;
}

numar adun(numar A, numar B)
{
   numar rez;
   init(rez, 0);

   int s, t = 0;
   for (int i = 1; i <= max(A.nrc, B.nrc) + 1; i++)
   {
      s = A.C[i] + B.C[i] + t;
      rez.C[i] = s % 10;
      t = s / 10;
   }
   rez.nrc = max(A.nrc, B.nrc) + 1;
   while (rez.C[rez.nrc] == 0)
      rez.nrc--;
   return rez;
}

numar prod(numar A, int x)
{
   for (int i = 1; i <= A.nrc; i++)
      A.C[i] *= x;

   int s, t = 0;
   for (int i = 1; i < CMAX; i++)
   {
      s = A.C[i] + t;
      A.C[i] = s % 10;
      t = s / 10;
   }
   A.nrc = CMAX - 1;
   while (A.C[A.nrc] == 0)
      A.nrc--;
   return A;
}

void afis(numar A)
{
   for (int i = A.nrc; i >= 1; i--)
      cout << A.C[i];
}

int n;
numar dp[2][NMAX][NMAX][4];
signed main()
{
   cin >> n;
   int cnt = 0;
   init(dp[cnt][0][0][1], 1);

   for (int i = 1; i <= n; i++)
   {
      for (int j = 0; j <= n; j++)
      {
         for (int k = 0; k <= n; k++)
         {
            if (i + j + k == 1)
               continue;

            //dp[i][j][k][1] = (dp[i - 1][j][k][2] + dp[i - 1][j][k][3]) * (n - i + 1);
            dp[cnt][j][k][1] = adun(dp[1 - cnt][j][k][2], dp[1 - cnt][j][k][3]);
            dp[cnt][j][k][1] = prod(dp[cnt][j][k][1], n - i + 1);

            if (j)
            {
               dp[cnt][j][k][2] = adun(dp[cnt][j - 1][k][1], dp[cnt][j - 1][k][3]);
               dp[cnt][j][k][2] = prod(dp[cnt][j][k][2], n - j + 1);
            }//dp[i][j][k][2] = (dp[i][j - 1][k][1] + dp[i][j - 1][k][3]) * (n - j + 1);
            if (k)
            {
               dp[cnt][j][k][3] = adun(dp[cnt][j][k - 1][1], dp[cnt][j][k - 1][2]);
               dp[cnt][j][k][3] = prod(dp[cnt][j][k][3], n - k + 1);
            }
               //dp[i][j][k][3] = (dp[i][j][k - 1][1] + dp[i][j][k - 1][2]) * (n - k + 1);

         }
      }
      cnt = 1 - cnt;
      for (int j = 0; j <= n; j++)
         for (int k = 0; k <= n; k++)
         {
            init(dp[cnt][j][k][1], 0);
            init(dp[cnt][j][k][2], 0);
            init(dp[cnt][j][k][3], 0);
         }
   }

   /*numar A;
   init(A, 5);
   numar B;
   init(B, 4);
   afis(prod(A, 6));
   return 0;*/

   //cout << dp[n][n][n][2];
   afis(dp[1 - cnt][n][n][2]);
   return 0;
}

