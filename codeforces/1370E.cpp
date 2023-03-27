/// submitted by Lauran on July 10, 2020
#include <bits/stdc++.h>
using namespace std;

int n;
char A[1000005], B[1000005];

int main()
{
    cin >> n;
    cin >> A + 1 >> B + 1;

    int cnta = 0, cntb = 0;
    for (int i = 1; i <= n; i++)
        cnta += A[i] == '1', cntb += B[i] == '1';
    if (cnta != cntb) {
        cout << -1;
        return 0;
    }

    int x = 1, y = 2; // ma rog
    vector <int> v;

    for (int i = 1; i <= n; i++)
        if (A[i] == '1' && B[i] == '0')
            v.push_back(x);
        else if (A[i] != B[i])
            v.push_back(y);

    int curr = 0, maxim = 0;
    int maxEfectiv = 0, minEfectiv = 0;
    for (auto nr: v) {
        nr == x ? curr++ : curr--;
        maxim = max(maxim, max(abs(curr - maxEfectiv), abs(curr - minEfectiv)));

        minEfectiv = min(minEfectiv, curr);
        maxEfectiv = max(maxEfectiv, curr);
    }

    cout << maxim;

    return 0;
}
