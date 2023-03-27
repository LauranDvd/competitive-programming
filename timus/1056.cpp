/// submitted by David Lauran on July 4, 2017
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cstring>
#define MAXN 10001
using namespace std;
ifstream fi("x.in");
ofstream fo("x.out");

short n;
vector <short> rez;
vector <short> vecin[MAXN];
short D[MAXN];
short minim=MAXN+1000;

void bfs(short sursa)
{
    queue <short> Q;
    Q.push(sursa);
    while (!Q.empty())
    {
        short curent=Q.front();
        Q.pop();
        for (short i=0; i<vecin[curent].size(); i++)
        {
            if (D[vecin[curent][i]]==0&&vecin[curent][i]!=sursa)
            {
                D[vecin[curent][i]]=D[curent]+1;
                Q.push(vecin[curent][i]);
            }
        }
    }
}

int main()
{
    cin>>n;
    for (short i=2; i<=n; i++)
    {
        short parinte;
        cin>>parinte;
        vecin[i].push_back(parinte);
        vecin[parinte].push_back(i);
    }
    for (short i=1; i<=n; i++)
    {
        memset(D,0,sizeof(D));
        bfs(i);
        short maxim=0;
        for (short j=1; j<=n; j++)
            maxim=max(D[j],maxim);
        if (maxim==minim)
            rez.push_back(i);
        else if (maxim<minim)
        {
            rez.clear();
            rez.push_back(i);
            minim=maxim;
        }
    }
    for (short i=0; i<rez.size(); i++)
        cout<<rez[i]<<" ";
    return 0;
}
