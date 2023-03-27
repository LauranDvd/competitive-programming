/// submitted by David Lauran on August 9, 2018
#include <iostream>
#include <algorithm>
#include <stack>
#include <vector>
#define NMAX 505
using namespace std;

int B[NMAX][NMAX];
int E[NMAX][NMAX];
int A[NMAX][NMAX];
int S[NMAX][NMAX];
int P[NMAX][NMAX];
int n, K;

int main()
{
    cin >> n >> K;
    n--;

    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
        {
            int v;
            cin >> v;
            B[i][j - i] = v;
            E[j][i] = v;
        }


    for (int i = 0; i < n; i++)
    {
        int c = 0;
        for (int j = i; j < n; j++)
        {
            for (int k = 0; k < n - j; k++)
                c += B[j][k];
            A[i][j] = c;
            for (int k = i; k <= j; k++)
                c -= E[j][k];
        }
    }


    for(int k = 0; k < K; k++)
        for(int i = 0; i < n; i++)
            for(int j = i; j < n; j++)
                if(S[i][k] + A[i][j] >= S[j + 1][k + 1])
                    S[j + 1][k + 1] = S[i][k] + A[i][j], P[j + 1][k + 1] = i;


    int maxim = 0, j = 0;
    for(int i = 0; i <= n; i++)
        if(S[i][K] >= maxim)
            j = i, maxim = S[i][K];
    cout << maxim << "\n";

    stack <int> s;
    for (int k = K; k; k--)
    {
        s.push(j);
        j = P[j][k];
    }
    while(!s.empty())
        cout << s.top() << " ", s.pop();

    return 0;
}
