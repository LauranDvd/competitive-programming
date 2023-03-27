/// submitted by Lauran on January 14, 2020
#include <bits/stdc++.h>
using namespace std;

const int NMAX = 3e5 + 5;

struct chestie {
    int a, b, c;
};

int n, m;
vector <int> sunat[NMAX];
int x[NMAX];
int ansMin[NMAX], ansMax[NMAX];
int aib[NMAX];
bool pus[NMAX];
int lst[NMAX];

inline int lsb(int x) {
    return (x & (-x));
}

void update(int poz, int val, int n) {
    for (; poz <= n; poz += lsb(poz))
        aib[poz] += val;
}

int getSum(int poz, int n) {
    int ret = 0;
    for (; poz; poz -= lsb(poz))
        ret += aib[poz];
    return ret;
}

bool cmp(chestie x, chestie y) {
    return x.c < y.c;
}

int main()
{
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= m; i++) {
        scanf("%d", &x[i]);
        sunat[x[i]].push_back(i);
    }

    for (int i = 1; i <= n; i++) {
        ansMax[i] = i;

        if (sunat[i].empty())
            ansMin[i] = i;
        else
            ansMin[i] = 1;
    }

    // 1. inainte de prima punere a fiecaruia
    for (int i = 1; i <= m; i++) {
        if (!pus[x[i]]) {
            // prima punere. interoghez cate numere > x[i]
            ansMax[x[i]] = max(ansMax[x[i]], x[i] + getSum(n, n) - getSum(x[i], n));
            update(x[i], 1, n);
        }
        pus[x[i]] = 1;
    }

    // cei care nu au fost sunati niciodata
    for (int i = 1; i <= n; i++) {
        if (sunat[i].empty()) {
            ansMax[i] = max(ansMax[i], i + getSum(n, n) - getSum(i, n));
        }
    }

    vector <chestie> q;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j < sunat[i].size(); j++) {
            // dupa sunarea j si inainte de sunarea j+1
            int l = sunat[i][j] + 1;
            int r;
            if (j + 1 < sunat[i].size())
                r = sunat[i][j + 1] - 1;
            else
                r = m;
            q.push_back({i, l, r});
        }
    }

    sort(q.begin(), q.end(), cmp);

    memset(aib, 0, sizeof(aib));
    int prevR = 0;
    for (auto query: q) {
        int ind = query.a;
        int l = query.b;
        int r = query.c;
        if (l > r)
            continue;
        //cout << ind << " " << l << " " << r << "\n";

        for (int i = prevR + 1; i <= r; i++) {
            if (lst[x[i]] != 0) {
                update(lst[x[i]], -1, m);
            }
            update(i, 1, m);
            lst[x[i]] = i;
        }

        int ansHere = getSum(r, m) - getSum(l - 1, m) + 1;
        ansMax[ind] = max(ansMax[ind], ansHere);

        prevR = r;
    }

    for (int i = 1; i <= n; i++)
        cout << ansMin[i] << " " << ansMax[i] << "\n";


    return 0;
}
