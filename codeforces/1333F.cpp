/// submitted by Lauran on April 11, 2020
#include <bits/stdc++.h>
using namespace std;

const int NMAX = 5e5 + 5;

int n;
int maxDiv[NMAX];

void getMaxDiv() {
    for (int i = 1; i < NMAX; i++)
        maxDiv[i] = 1;

    for (int i = 2; i < NMAX; i++)
        for (int j = 2 * i; j < NMAX; j += i)
            maxDiv[j] = i;
}

int main()
{
    scanf("%d", &n);

    getMaxDiv();

    vector <pair<int,int>> v;
    for (int i = 2; i <= n; i++) {
        v.push_back({maxDiv[i], i});
    }
    sort(v.begin(), v.end());

    for (auto x: v) {
        cout << x.first << " ";
    }

    return 0;
}
