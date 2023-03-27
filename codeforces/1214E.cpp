/// submitted by Lauran on September 11, 2019
#include <bits/stdc++.h>
using namespace std;

const int NMAX = 1e5 + 5;

bool comp(pair <int, int> a, pair <int, int> b)
{
    return a.first > b.first;
}

int n;
pair <int, int> d[NMAX];
vector <int> drum;
vector < pair<int, int> > rez;

int main()
{
    cin >> n;
    for (int i = 1; i <= n; i++)
    {
        cin >> d[i].first;
        d[i].second = i;
    }

    sort(d + 1, d + n + 1, comp);

    for (int i = 1; i < n; i++)
    {
        rez.push_back({d[i].second * 2 - 1, d[i + 1].second * 2 - 1});
        drum.push_back(d[i].second * 2 - 1);
    }
    drum.push_back(d[n].second * 2 - 1);

    int curr = 0;
    for (int i = 1; i <= n; i++)
    {
        while (d[i].second * 2 - 1 != drum[curr])
            curr++;

        int leg = drum[curr + d[i].first - 1];
        rez.push_back({d[i].second * 2, leg});

        if (curr + d[i].first - 1 == drum.size() - 1)
            drum.push_back(d[i].second * 2);
    }

    for (auto x: rez)
        cout << x.first << " " << x.second << "\n";


    return 0;
}
