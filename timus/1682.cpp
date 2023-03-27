/// submitted by David Lauran on March 11, 2018
#include <cstdio>
#include <vector>
#define ll long long
#define MAXK 100005
#define MAX 250000
using namespace std;

int k;
int p[MAX];
vector <int> P[MAXK];

int parinte(int nod)
{
    if (p[nod]==nod)
        return nod;
    return p[nod]=parinte(p[nod]);
}

void unire(int x,int y)
{
    p[parinte(x)]=parinte(y);
}

void precalc()
{
    for (int i=1; i<=MAX; i++)
    {
        ll rest=(1LL*i*i)%k;
        P[rest].push_back(i);
    }
}

int main()
{
    scanf("%d",&k);
    precalc();
    int curent=0;
    bool ciclu=0;
    while (!ciclu)
    {
        curent++;
        p[curent]=curent;

        /// i+curent*curent=k
        ll r=1LL*k*k*10-1LL*curent*curent;
        r%=k;
        for (int i=r; i<curent; i+=k)
        {
            if (i==0)
                continue;
            /// unim pe curent cu i
            if (parinte(curent)==parinte(i))
                ciclu=1;
            unire(curent,i);
        }
        int aux=r;

        ///curent+i*i=k
        r=(5*k-curent)%k;
        for (auto i: P[r])
        {
            if (i%k==aux) /// l-am unit mai sus
                continue;
            if (i>=curent) /// inca nu l-am scris
                break;
            if (parinte(curent)==parinte(i))
                ciclu=1;
            unire(curent,i);
        }
    }
    printf("%d",curent);
    return 0;
}
