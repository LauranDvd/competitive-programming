#include <bits/stdc++.h>
using namespace std;

const long long MOD = 998244353;

long long p[200005];
int n;

void getPuteri() {
    p[0] = 1;
    for (int i = 1; i <= n; i++)
        p[i] = p[i - 1] * 10 % MOD;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;

    getPuteri();

    for (int k = 1; k <= n; k++) {
        if (k == n) {
            cout << 10;
        }
        else {
            // 1. st = 1
            long long ans = 9 * p[n - k - 1] % MOD;
            // 2. st = n-k+1
            ans += 9 * p[n - k - 1] % MOD;
            ans %= MOD;
            
            // 3. altfel
            if (n - k >= 2)
                ans += 81 * p[n - k - 2] % MOD * (n - k + 1 - 2) % MOD;
            ans %= MOD;

            ans = ans * 10 % MOD;
            cout << ans << " ";
        }
    }


    return 0;
}

