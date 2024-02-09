#include <fstream>
#include <vector>
#include <cstring>
#define ll long long
#define pb push_back
#define MAX 100005
using namespace std;
ifstream fi("kpal.in");
ofstream fo("kpal.out");

struct upd
{
    ll st;
    ll dr;
    ll val;
};

ll x,n;
ll q;
ll S;
ll cost[30][30];
ll costMatch[30][30]; /// cost minim sa egalam litera i cu litera j
char M[MAX];
vector <ll> divizori;
vector <upd> U;

void getDiv()
{
    /*ll aux=n;
    for (ll i=2; i*i<=n; i++)
    {
        if (aux%i==0)
            divizori.pb(i);
        while (aux%i==0)
            aux/=i;
    }
    if (aux>1)
        divizori.pb(aux);


    /// il adaugam pe n daca acesta nu este prim (asa l-am adaguat la instruct.prec.)
    if (aux!=n)
        divizori.pb(n);*/

    for (ll i=2; i<=n; i++)
        if (n%i==0)
            divizori.pb(i);

}

ll getCost(ll l) /// l = lungimea unei bucati
{
    ll rez=0;

    for (ll b=1; b<=n/l; b++) /// la a cata bucata ne aflam
    {
        ll st=(b-1)*l+1,dr=b*l; /// delimitam bucata pe care o facem palindrom

        while (st<dr)
        {
            /// st si dr sunt simetrice in bucata, deci trebuie egalate
            rez+=costMatch[M[st]-'a'+1][M[dr]-'a'+1];
            st++,dr--;
        }
    }
    return rez;
}

void update(upd A)
{
    /// luam toate update-urile vechi si, daca se intersecteaza cu cel nou,
    /// imbunatatim
    //vector <upd> :: iterator it;
    vector <upd> V; /// elementele care urmeaza adaugate in U

    for (ll it=0; it<U.size(); it++)
    {
        upd x=U[it];

        ll l=0,r=-1; /// de unde pana unde se intersectaza A cu x

        /// 1. A il cuprinde pe x
        if (A.st<=x.st && A.dr>=x.dr)
        {
            l=x.st,r=x.dr;

            U.erase(U.begin()+it);
            it--;
        }


        /// 2. x il cuprinde pe A
        else if (x.st<=A.st && x.dr>=A.dr)
        {
            l=A.st,r=A.dr;

            /// partile din x neactualizate de A
            upd nou1={x.st,A.st-1,x.val};
            upd nou2={A.dr+1,x.dr,x.val};

            if (nou1.st<=nou1.dr)
                V.pb(nou1);
            if (nou2.st<=nou2.dr)
                V.pb(nou2);

            U.erase(U.begin()+it);
            it--;
        }


        /// 3. x trece prin stanga lui A
        else if (x.st<=A.st && x.dr>=A.st)
        {
            l=A.st,r=x.dr;

            /// partea din x neactualizata de A
            upd nou={x.st,A.st-1,x.val};

            if (nou.st<=nou.dr)
                V.pb(nou);

            U.erase(U.begin()+it);
            it--;
        }

        /// 4. x trece prin dreapta lui A
        else if (x.st<=A.dr && x.dr>=A.dr)
        {
            l=x.st,r=A.dr;

            /// partea din x neactualizata de A
            upd nou={A.dr+1,x.dr,x.val};

            if (nou.st<=nou.dr)
                V.pb(nou);

            U.erase(U.begin()+it);
            it--;
        }


        if (!(l==0 && r==-1))
            S-=(r-l+1)*(x.val-A.val);
    }

    V.pb(A);

    /// bagam noile elemente in U
    for (auto x: V)
        U.pb(x);
}

ll getCostMatch()
{
    for (int i=1; i<=x; i++)
        for (int j=1; j<=x; j++)
        {
            costMatch[i][j]=10005;
            for (int k=1; k<=x; k++)
                costMatch[i][j]=min(costMatch[i][j],cost[i][k]+cost[j][k]);
        }
}

int main()
{
    fi>>x;
    for (ll i=1; i<=x; i++)
        for (ll j=1; j<=x; j++)
            fi>>cost[i][j];
    getCostMatch();

    /*for (int i=1; i<=x; i++)
    {
        for (int j=1; j<=x; j++)
            fo<<costMatch[i][j]<<" ";
        fo<<"\n";
    }*/

    fi>>(M+1);
    n=strlen(M+1);
    fi>>q;

    U.pb({0,q,n});
    S=1LL*n*(q+1);

    getDiv();

    //for (auto x: divizori)
        //fo<<x<<" ";
    //return 0;

    for (auto i: divizori)
    {
        /// o bucata are lungimea i => obtinem n/i bucati
        ll k=getCost(i);
        //fo<<n/i<<" bucati: "<<k<<"\n";
        //continue;

        if (k<=q)
            update({k,q,n/i});
    }
    fo<<S;
    return 0;
}

