/// submitted by David Lauran on February 13, 2018
#include <iostream>
#include <vector>
#include <iomanip>
#define MAX 1005
#define pb push_back
using namespace std;

vector < pair<int,int> > G[MAX];
double R[MAX];
int val[MAX][2];
bool viz[MAX][2];
int n,m;

void dfs(int nod,int d,int sum)
{
    if (viz[nod][d])
        return;
    viz[nod][d]=1;

    val[nod][d]=sum;
    R[nod]+=sum;

    for (int i=0; i<G[nod].size(); i++)
        dfs(G[nod][i].first,1-d,G[nod][i].second-sum);
}

int main()
{
    cin>>n>>m;
    for (int i=1; i<=m; i++)
    {
        int a,b,x;
        cin>>a>>b>>x;
        G[a].pb({b,x});
        G[b].pb({a,x});
    }

    /// parcurgem graful
    for (int i=1; i<=n; i++)
        if (!viz[i][0] && !viz[i][1])
            dfs(i,0,0);

    bool ok=1;

    for (int i=1; i<=n && ok; i++)
        if (!viz[i][0] || !viz[i][1])
            ok=0;
        else
            R[i]/=2;

    for (int i=1; i<=n; i++)
    {
        for (int j=G[i].size()-1; j>=0; j--)
        {
            int vecin=G[i][j].first;
            int cost=G[i][j].second;

            if (cost != val[i][0]+val[vecin][1] ||
                cost != val[i][1]+val[vecin][0])
                ok=0;
        }
    }

    if (!ok)
        cout<<"IMPOSSIBLE";
    else
        for (int i=1; i<=n; i++)
            cout<<fixed<<setprecision(2)<<R[i]<<"\n";

    return 0;
}
