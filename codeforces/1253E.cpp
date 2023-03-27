/// submitted by Lauran on November 21, 2019
#include <bits/stdc++.h>
using namespace std;

int n, m;
int l[85], r[85];
int dp[100005];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        int x, s;
        cin >> x >> s;
        l[i] = max(0, x - s);
        r[i] = min(m, x + s);
    }

    for (int i = m - 1; i >= 0; i--)
    {
        dp[i] = m - i;

        for (int j = 1; j <= n; j++)
        {
            if (l[j] <= i + 1 && i + 1 <= r[j])
            {
                dp[i] = dp[i + 1];
                break;
            }

            if (i < l[j])
            {
                int cost = l[j] - i - 1;
                dp[i] = min(dp[i], cost + dp[min(m, r[j] + cost)]);
            }
        }
    }

    cout << dp[0];


    return 0;
}
