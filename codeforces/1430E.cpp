#include <bits/stdc++.h>
using namespace std;

const int NMAX = 2e5 + 5;

int n;
char A[NMAX], B[NMAX];
set <int> S[30];
int p[NMAX];
int aib[NMAX];

inline int lsb(int x) {
   return (x & (-x));
}

void update(int poz, int val) {
   for (; poz <= n; poz += lsb(poz))
      aib[poz] += val;
}

int getSum(int poz) {
   int ret = 0;
   for (; poz; poz -= lsb(poz))
      ret += aib[poz];
   return ret;
}

int main()
{
   ios_base::sync_with_stdio(false);
   cin.tie(0);

   cin >> n;
   for (int i = 1; i <= n; i++) {
      cin >> A[i];
      S[A[i] - 'a'].insert(i);
   }

   for (int i = 1; i <= n; i++)
      B[i] = A[n - i + 1];

   for (int i = 1; i <= n; i++) {
      p[i] = *S[B[i] - 'a'].begin();
      S[B[i] - 'a'].erase(S[B[i] - 'a'].begin());
   }

   // numar inversiunile
   long long ans = 0;
   for (int i = 1; i <= n; i++) {
      ans += getSum(n) - getSum(p[i]);

      update(p[i], 1);
   }
   cout << ans;


   return 0;
}

