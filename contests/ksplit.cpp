#include <fstream>
#include <vector>
#define MAX 100005
using namespace std;
ifstream fi("ksplit.in");
ofstream fo("ksplit.out");

typedef long long LL;

LL min1[MAX],min2[MAX],max1[MAX],max2[MAX];
LL x[MAX],S[MAX],n;
vector <pair<int,int>> rez;
///min1=minim suma subsecventa care incepe pe i
///min2=minim suma subsecventa care se termina pe i

int main()
{
    fi>>n;
    for (int i=1; i<=n; i++)
        fi>>x[i],S[i]=S[i-1]+x[i];
    for (int i=1; i<=n; i++)
    {
        min2[i]=min(x[i],x[i]+min2[i-1]);
        max2[i]=max(x[i],x[i]+max2[i-1]);
    }
    for (int i=n; i>=1; i--)
    {
        min1[i]=min(x[i],x[i]+min1[i+1]);
        max1[i]=max(x[i],x[i]+max1[i+1]);
    }

    LL maxim=x[1],l=1,kk=1;
    rez.push_back({1,-1});
    int dir=-1;
    for (int k=1; k<n; k++)
    {
        LL local=max(max2[k]-min1[k+1],max1[k+1]-min2[k]);
        if (local>=maxim)
        {
            if (local>maxim)
                rez.clear();
            maxim=local;
            if (max2[k]-min1[k+1]>max1[k+1]-min2[k])
                dir=-1; ///marele e in stanga
            else
                dir=1; ///marele e in dreapta
            kk=k;
            rez.push_back({kk,dir});
        }

    }
    fo<<maxim<<"\n";

    int LMAX=0;

    for (auto x: rez)
    {
        int dir=x.second,k=x.first;
        int st=k,dr=k+1;

        if (dir==-1)
        {
            ///marele in stanga
            for (int i=st; i>=1; i--)
                if (S[k]-S[i-1]>=S[k]-S[st-1])
                    st=i;

            for (int i=dr; i<=n; i++)
                if (S[i]-S[k]<=S[dr]-S[k])
                    dr=i;
            LMAX=max(LMAX,dr-st+1);
        }

        else
        {
            ///marele in dreapta

            for (int i=st; i>=1; i--)
                if (S[k]-S[i-1]<=S[k]-S[st-1])
                    st=i;

            for (int i=dr; i<=n; i++)
                if (S[i]-S[k]>=S[dr]-S[k])
                    dr=i;
            LMAX=max(LMAX,dr-st+1);
        }
    }
    fo<<LMAX;
    return 0;
}

