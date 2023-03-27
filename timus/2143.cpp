/// submitted by David Lauran on November 4, 2019
#include <bits/stdc++.h>
using namespace std;

const int NMAX = 1e2 + 5;

int n, k;
char M[NMAX][20];
int dp[2][NMAX][8];
vector < pair<int, char> > pun;


bool compatibil(int mask1, int mask2)
{
    return (mask1 & mask2) == 0 && ((mask1 << 1) & mask2) == 0 && (mask1 & (mask2 << 1)) == 0;
}

bool okPeLinie(int deki, int mask, int lin)
{
    for (int i = 0; i < 3; i++)
        if (mask & (1 << i))
            if (M[lin][deki + 2 - i] == '*')
                return 0;
    return 1;
}

bool okInSine(int mask)
{
    return (mask & (mask << 1)) == 0;
}

int nrBiti1(int x)
{
    int ret = 0;
    for (int i = 0; (x >> i); i++)
        ret += ((x >> i) & 1);
    return ret;
}

void getDp(int ind, int deki)
{
    for (int i = 1; i <= n; i++)
        for (int mask = 0; mask < (1 << 3); mask++)
            for (int maskBf = 0; maskBf < (1 << 3); maskBf++)
                if (okInSine(mask) && okInSine(maskBf) && compatibil(mask, maskBf) && okPeLinie(deki, mask, i) && okPeLinie(deki, maskBf, i - 1))
                    dp[ind][i][mask] = max(dp[ind][i][mask], dp[ind][i - 1][maskBf] + nrBiti1(mask));

}

void david(int ind, int deki, int lin, int maskAici)
{
    if (lin == 0)
        return;

    for (int i = 0; i < 3; i++)
        if (maskAici & (1 << i))
        {
            char c = 'A' + 2 - i;
            if (ind == 1)
                c += 3;
            
            pun.push_back({lin, c});
        }
    
    int nextMask = -1;
    for (int maskSus = 0; maskSus < (1 << 3); maskSus++)
        if (okInSine(maskSus) && compatibil(maskSus, maskAici) && okPeLinie(deki, maskSus, lin - 1) && dp[ind][lin - 1][maskSus] == 
                                                                                                    dp[ind][lin][maskAici] - nrBiti1(maskAici))
            nextMask = maskSus;

    david(ind, deki, lin - 1, nextMask);
}

int main()
{
    cin >> n >> k;
    for (int i = 1; i <= n; i++)
        cin >> M[i];

    getDp(0, 0);
    getDp(1, 6);


    int maxSt = 0, maxDr = 0;
    for (int mask = 0; mask < (1 << 3); mask++)
    {
        maxSt = max(maxSt, dp[0][n][mask]);
        maxDr = max(maxDr, dp[1][n][mask]);
    }

    if (maxSt + maxDr < k)
    {
        cout << "PORAZHENIE";
        return 0;
    }

    int bestMask = 0;
    for (int mask = 1; mask < (1 << 3); mask++)
        if (dp[0][n][mask] > dp[0][n][bestMask])
            bestMask = mask;

    david(0, 0, n, bestMask);

    bestMask = 0;
    for (int mask = 1; mask < (1 << 3); mask++)
        if (dp[1][n][mask] > dp[1][n][bestMask])
            bestMask = mask;

    david(1, 6, n, bestMask);

    cout << "POBEDA\n";
    for (int i = 0; i < k; i++)
        cout << pun[i].first << pun[i].second << "\n";

    return 0;
}
