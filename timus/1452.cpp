/// submitted by David Lauran on September 25, 2018
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

const int NMAX = 2005;

short dp[NMAX][NMAX];
int n, k;
pair<int, short> x[NMAX];
map<int, bool> f;

void reconstituire(int i, int dif)
{
    // cout << "\n\n" << i << "\n" << dif << "\n\n";
    int j = i + 1;
    while (x[j].first - x[i].first < dif && j <= k)
        j++;
    if (j > k || x[j].first - x[i].first > dif)
        return;
    cout << x[j].second << " ";
    reconstituire(j, dif);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;

    for (int i = 1; i <= n; i++)
    {
        int val;
        cin >> val;
        if (!f[val])
        {
            k++;
            x[k].first = val;
            x[k].second = i;
        }
        f[val] = 1;
    }
    f.clear();

    // n = k;

    sort(x + 1, x + k + 1);

    if (x[1].first == x[k].first)
    {
        cout << "1\n"
             << x[1].second;
        return 0;
    }

    for (int i = 1; i <= k; i++)
        dp[i][k] = 2;

    int rez = 2, l = 1, c = k, dif = x[k].first - x[1].first;
    for (int j = k - 1; j >= 2; j--)
    {
        int i = j - 1, kk = j + 1;
        while (i >= 1 && kk <= k)
        {
            if (x[i].first + x[kk].first < 2 * x[j].first)
                kk++;

            else if (x[i].first + x[kk].first > 2 * x[j].first)
            {
                dp[i][j] = 2;
                i--;
            }
            else
            {
                dp[i][j] = 1 + dp[j][kk];
                if (dp[i][j] > rez)
                {
                    rez = dp[i][j];
                    dif = x[j].first - x[i].first;
                    l = i;
                    c = j;
                }
                i--;
                kk++;
            }
        }
        while (i >= 0)
            dp[i--][j] = 2;
    }

    cout << rez << "\n"
         << x[l].second << " " << x[c].second << " ";
    reconstituire(c, dif);

    return 0;
}
