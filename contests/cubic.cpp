#include <fstream>
#include <vector>
#define MAX 1005
#define MOD 9901
using namespace std;
ifstream fi("cubic.in");
ofstream fo("cubic.out");

vector <int> X[MAX];
int n,P;
char M[MAX][MAX];
int rez=1;

void construire(int zona,int l,int c)
{
    while (1) {
        X[zona].push_back(M[l][c]-'0');
        if (zona==(n+1)/2)
            break;
        if (l==zona && c==n/2) /// finalul zonei
        {
            /// construire(zona+1,l+1,c+1);
            zona++,l++,c++;
            continue;
        }

        if (l==zona && c!=n-zona+1) /// partea de sus, fara colt
            ///construire(zona,l,c+1);
            c=c+1;
        else if (l==zona) /// partea de sus cu colt
            ///construire(zona,l+1,c);
            l++;

        else if (l==n-zona+1 && c!=zona) /// partea de jos, fara colt
            ///construire(zona,l,c-1);
            c--;
        else if (l==n-zona+1) /// partea de jos cu colt
            ///construire(zona,l-1,c);
            l--;

        else if (c==zona && l!=zona) /// partea de stanga, fara colt
            ///construire(zona,l-1,c);
            l--;
        else if (c==zona) /// partea de stanga cu colt
            ///construire(zona,l,c+1);
            c++;

        else if (c==n-zona+1 && l!=n-zona+1) /// partea de dreapta, fara colt
            ///construire(zona,l+1,c);
            l++;
        else if (c==n-zona+1) /// partea de dreapta cu colt
            ///construire(zona,l,c-1);
            c--;
    }

}

void rezolva(int zona)
{
    /// rezolvam pt zona
    int aici=0;
    int k=n-2*(zona-1);
    int total=k*4-4;
    for (int p=0; p<=P && p<total; p++) /// sus se afla p-ul
    {
        int poz1=p%total,poz2=(p+k-1)%total,poz3=(p+2*k-2)%total,poz4=(p+3*k-3)%total;
        if (X[zona][poz1]==1 && X[zona][poz2]==1 && X[zona][poz3]==1 &&
            X[zona][poz4]==1)
                aici++;
    }
    ///fo<<zona<<": "<<aici<<"\n";

    if (total<=P) /// se repeta aceeasi configuratie
    {
        aici=aici*(P/total); /// rotiri complete
        int rest=P%total; /// rotiri ramase
        for (int p=0; p<=rest; p++) /// sus se afla p-ul
        {
            int poz1=p%total,poz2=(p+k-1)%total,poz3=(p+2*k-2)%total,poz4=(p+3*k-3)%total;
            if (X[zona][poz1]==1 && X[zona][poz2]==1 && X[zona][poz3]==1 &&
                X[zona][poz4]==1)
                    aici++;
        }
    }

    rez=(rez*aici)%MOD;
}

int main()
{
    fi>>n>>P;
    for (int i=1; i<=n; i++)
        fi>>M[i]+1;
    construire(1,1,(n+1)/2);

    /*for (int i=1; i<=(n+1)/2; i++)
    {
        for (auto x: X[i])
            fo<<x<<" ";
        fo<<"\n";
    }*/
    for (int i=1; i<(n+1)/2; i++)
        rezolva(i);
    fo<<rez;
    return 0;
}

