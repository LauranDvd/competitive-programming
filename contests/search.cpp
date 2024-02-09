#include <bits/stdc++.h>
using namespace std;
ifstream fi("search.in");
ofstream fo("search.out");

const int NMAX = 105;
const int LMAX = 5005;

int n, q;
char A[NMAX][LMAX];
int sz[NMAX];
short nxt[NMAX][LMAX][30];
stack <short> stiva[NMAX];
int poz[NMAX], lstPoz[NMAX], hopa[NMAX];

int main()
{
    fi >> n >> q;
    for (int i = 1; i <= n; i++) {
        fi >> A[i] + 1;
        sz[i] = strlen(A[i] + 1);

        for (char x = 'a'; x <= 'z'; x++) {
            int lst = 0;
            for (int j = sz[i]; j >= 1; j--) {
                nxt[i][j][x - 'a'] = lst;
                if (A[i][j] == x)
                    lst = j;
            }
        }
    }

    char prim;
    fi >> prim; q--;

    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= sz[i]; j++)
            if (A[i][j] == prim) {
                stiva[i].push(j);
                break;
            }
        if (stiva[i].empty())
            hopa[i] = 1;
        else
            ans++;
    }

    fo << ans << "\n";

    while (q--) {
        char x; fi >> x;

        ans = 0;
        for (int i = 1; i <= n; i++) {
            if (x != '-') {
                if (hopa[i])
                    hopa[i]++;
                else {
                    if (nxt[i][stiva[i].top()][x - 'a']) {
                        stiva[i].push(nxt[i][stiva[i].top()][x - 'a']);
                        ans++;
                    }
                    else
                        hopa[i] = 1;
                }
            }
            else {
                if (hopa[i]) {
                    hopa[i]--;
                    if (hopa[i] == 0)
                        ans++;
                }
                else {
                    stiva[i].pop();
                    ans++;
                }
            }
        }

        fo << ans << "\n";
    }


    return 0;
}
