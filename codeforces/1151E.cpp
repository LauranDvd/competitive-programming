/// submitted by Lauran on April 22, 2019
#include <bits/stdc++.h>
using namespace std;

int n;
int a[100005];

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
        cin >> a[i];

    unsigned long long rez = 0;

    for (int i = 1; i <= n; i++)
    {
        if (i == n)
        {
            // l: 1...a[i]
            // r: a[i]...n
            rez += 1LL * a[i] * (n - a[i] + 1);

            //cout << 1LL * a[i] * (n - a[i] + 1) << " ";
            break;
        }

        if (a[i + 1] > a[i])
        {
            // l: 1...a[i]
            // r: a[i]...a[i + 1]-1
            rez += max(0LL, 1LL * a[i] * (a[i + 1] - a[i]));
            //cout << max(0LL, 1LL * a[i] * (a[i + 1] - a[i])) << " ";
        }
        else
        {
            // l: a[i + 1] + 1...a[i]
            // r: a[i]...n
            rez += max(0LL, 1LL * (a[i] - a[i + 1]) * (n - a[i] + 1));
            //cout << max(0LL, 1LL * (a[i] - a[i + 1]) * (n - a[i] + 1)) << " ";
        }
    }

    cout << rez;

    return 0;
}
