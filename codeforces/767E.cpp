/// submitted by Lauran on November 04, 2019
#include <bits/stdc++.h>
using namespace std;

const int NMAX = 1e5 + 5;

long long n, m;
int cost[NMAX], w[NMAX];
bool bancnote[NMAX];

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
        cin >> cost[i];

    for (int i = 1; i <= n; i++)
        cin >> w[i];


    long long ans = 0;

    priority_queue < pair<long long, int> > Q;
    for (int i = 1; i <= n; i++)
    {
        if (cost[i] % 100)
            Q.push({-1LL * w[i] * (100 - cost[i] % 100), i});
        else 
            continue;

        m -= cost[i] % 100;

        if (m < 0)
        {
            long long supNou = -Q.top().first, deUnde = Q.top().second;
            Q.pop();

            ans += supNou;
            m += 100;

            bancnote[deUnde] = 1;
        }
    }

    cout << ans << "\n";
    for (int i = 1; i <= n; i++)
    {
        if (bancnote[i])
            cout << cost[i] / 100 + (cost[i] % 100 != 0) << " " << 0 << "\n";
        else 
            cout << cost[i] / 100 << " " << cost[i] % 100 << "\n";
    }


    return 0;
}
