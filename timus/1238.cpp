#include <iostream>
#include <string>
#include <algorithm>
#define NMAX 105
using namespace std;

string dp[NMAX][NMAX], S;
int l;

string falString(int a)
{
    string ret = "";
    while (a)
    {
        ret += (a % 10 + '0');
        a /= 10;
    }
    reverse(ret.begin(), ret.end());
    return ret;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin >> S;
    l = S.size();

    for (int i = 0; i < l; i++)
        dp[i][i] = S[i];

    for (int p = 1; p < l; p++) /// de la i la i + p
    {
        for (int i = 0; i + p < l; i++)
        {
            /// [i, i + p]
            int j = i + p;

            dp[i][j] = "";

            /// 1. taiere
            for (int k = i; k < j; k++) /// dupa k taiem
            {
                if (dp[i][k].size() + dp[k + 1][j].size() < dp[i][j].size() || dp[i][j].size() == 0)
                {
                    dp[i][j] = dp[i][k] + dp[k + 1][j];
                }
            }

            /// 2. unificare
            for (int k = i; k - i + 1 <= j - k; k++) /// [i, k] se repeta
            {
                if ((p + 1) % (k - i + 1)) /// nu e divizibil
                    continue;

                bool da = 1;

                string am = "", bun = S.substr(i, k - i + 1);
                for (int t = k + 1; t <= j; t++)
                {
                    am += S[t];
                    if (am.size() == bun.size())
                    {
                        if (am != bun)
                        {
                            da = 0;
                            break;
                        }
                        am.clear();
                    }
                }
                if (da)
                {
                    string aci = "";
                    int cat = (p + 1) / (k - i + 1);
                    aci += falString(cat) + "(" + dp[i][k] + ")";
                    if (aci.size() <= dp[i][j].size())
                        dp[i][j] = aci;
                }

            }
        }
    }
    cout << dp[0][l - 1];
    return 0;
}

