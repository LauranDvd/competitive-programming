/// submitted by David Lauran on November 5, 2019
#include <bits/stdc++.h>
#define ll long long
#define int long long
using namespace std;

const int MAXLOG = 70;
const int MAXL = 105;
const int MOD = 1e9 + 7;

int q;
ll n, k, l;
int init[MAXLOG];
int memo[MAXLOG][MAXL][MAXL];

int bkt(int ceCifra, int catePeCifra, int spargeriRamase)
{
    if (memo[ceCifra][catePeCifra][spargeriRamase] != -1)
        return memo[ceCifra][catePeCifra][spargeriRamase];
    if (spargeriRamase == 0)
        return memo[ceCifra][catePeCifra][spargeriRamase] = 1;

    if (ceCifra == 0)
    {
        if (spargeriRamase)
            return memo[ceCifra][catePeCifra][spargeriRamase] = 0;
        return memo[ceCifra][catePeCifra][spargeriRamase] = 1;
    }
    
    long long ret = 0;
    for (int cateSpargeriFac = 0; cateSpargeriFac <= catePeCifra && cateSpargeriFac <= spargeriRamase; cateSpargeriFac++)
    {
        ret = (ret + bkt(ceCifra - 1, min(l, init[ceCifra - 1] + 1LL * cateSpargeriFac * k), spargeriRamase - cateSpargeriFac));
        if (ret >= MOD)
            ret -= MOD;
    }

    return memo[ceCifra][catePeCifra][spargeriRamase] = ret;
}

signed main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    cin >> q;
    while (q--)
    {
        cin >> n >> k >> l;

        int nrCifre = 0, sumCifre = 0;
        while (n)
        {
            init[nrCifre++] = n % k;
            sumCifre += n % k;
            n /= k;
        }
        nrCifre--;

        int spargeri = (l - sumCifre) / (k - 1);

        if ((l - sumCifre) % (k - 1))
        {
            cout << 0 << "\n";
            continue;
        }

        memset(memo, -1, sizeof(memo));

        cout << bkt(nrCifre, min((int)l, init[nrCifre]), spargeri) << "\n";
    }

    return 0;
}
