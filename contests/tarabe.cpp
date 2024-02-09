#include <fstream>
#include <vector>
#define ll long long
using namespace std;
ifstream fi("tarabe.in");
ofstream fo("tarabe.out");

vector < pair<ll, ll> > V;
ll n,k;

ll ok(ll x)
{
    ll res=0;
    for (ll i=0; i<n; i++)
    {
        if (x >= V[i].first)
            res += (x - V[i].first) / V[i].second + 1;
    }
    return res;
}

int main() {

    fi >> n >> k;
    V.resize(n);

    for (ll i = 0; i < n; ++i)
        fi >> V[i].second >> V[i].first;

    /// costul maxim la care ajungem pt un obiect
    ll lo = 0, hi = 1;
    while (ok(hi) <= k)
        hi<<=1LL;
    while (lo < hi)
    {
        ll mid = (lo + hi) >> 1;
        if (ok(mid) >= k)
            hi = mid;
        else
            lo = mid + 1;
    }

    /// calculam si eliminam obiecte de cost maxim care sunt in plus
    ll ans = lo;
    ll res = 0;
    ll totalOb = 0;
    for (ll i = 0; i < n; ++i)
    {
        ll aici = 0;
        ll a = V[i].first, b = V[i].second;
        if (ans >= V[i].first)
            aici = (ans - V[i].first) / V[i].second + 1;

        ll llerm = aici * (aici - 1) / 2;
        res += aici * a + b * llerm;
        totalOb += aici;
    }
    fo << res - (totalOb - k) * ans << "\n";

    return 0;
}
