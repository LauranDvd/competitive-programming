#include <bits/stdc++.h>
using namespace std;
ifstream fi("rafaela.in");
ofstream fo("rafaela.out");

const int NMAX = 2e5 + 5;

int n, q;
vector <int> G[NMAX];
int val[NMAX], p[NMAX];
int cntSubarb[NMAX], h[NMAX];

int nrLanturi, cnt[NMAX], sCnt[NMAX], inCeLant[NMAX], pozInLant[NMAX];
vector <int> vNoduri[NMAX];
int aib[NMAX];


inline void bagaNodLant(int nod, int lant) {
    cnt[lant]++;
    vNoduri[lant].push_back(nod);
    inCeLant[nod] = lant;
}

void decompose(int nod) {
    cntSubarb[nod] = 1;

    for (auto v: G[nod]) 
        if (v != p[nod]) {
            p[v] = nod;
            h[v] = h[nod] + 1;
            decompose(v);
            cntSubarb[nod] += cntSubarb[v];
        }

    if ((cntSubarb[nod] == 1 && nod != 1) || (nod == 1 && n == 1)) {  // frunza
        nrLanturi++;
        bagaNodLant(nod, nrLanturi);
        return;
    }
    
    int fiuBun = 0;
    for (auto v: G[nod]) 
        if (v != p[nod] && cntSubarb[v] >= cntSubarb[fiuBun]) {
            fiuBun = v;
        }
    
    bagaNodLant(nod, inCeLant[fiuBun]);
}

void updateAib(int lant, int a, int b, int v) {
    // aib[a] += v
    // aib[b + 1] -= v
    
    //cout << lant << " " << a << " " << b << " " << v << "\n";
    
    a++; b++;
    int decalaj = sCnt[lant - 1];

    for (int i = a; i <= cnt[lant]; i += (i & (-i)))
        aib[decalaj + i] += v;
    for (int i = b + 1; i <= cnt[lant]; i += (i & (-i)))
        aib[decalaj + i] -= v;
}

void updateHld(int a, int b, int v) {
    while (inCeLant[a] != inCeLant[b]) {
        if (h[a] > h[b])
            swap(a, b);
        
        // il urc pe b
        int pb = vNoduri[inCeLant[b]].back();
        // cresc, pe lantul lui b, de la parinte pana la b
        updateAib(inCeLant[b], pozInLant[b], cnt[inCeLant[b]] - 1, v);

        b = p[pb]; // auf wieder sehen, meinen Lantz
    }

    if (h[a] > h[b])
        swap(a, b);
    updateAib(inCeLant[a], pozInLant[b], pozInLant[a], v);
}

int queryAib(int lant, int a, int b) {
    //cout << lant << " " << a << " " << b << "\n";

    int decalaj = sCnt[lant - 1];
    int ret = 0;
    a++; b++;

    for (int i = b; i > 0; i -= (i & (-i)))
        ret += aib[decalaj + i];
    for (int i = a - 1; i > 0; i -= (i & (-i)))
        ret -= aib[decalaj + i];
    return ret;
}

int queryHld(int nod) {
    return queryAib(inCeLant[nod], 0, pozInLant[nod]);
}

int main()
{
    fi >> n >> q;
    for (int i = 1; i < n; i++) {
        int u, v;
        fi >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }

    h[1] = 1;
    decompose(1);

    sCnt[1] = cnt[1];
    for (int i = 2; i <= nrLanturi; i++)
        sCnt[i] = sCnt[i - 1] + cnt[i];
    
    for (int i = 1; i <= nrLanturi; i++)
        for (int j = 0; j < vNoduri[i].size(); j++)
            pozInLant[vNoduri[i][j]] = j;

    /*for (int i = 1; i <= n; i++) {
        cout << pozInLant[i] << " ";
    }
    return 0;*/

    
    for (int i = 1; i <= n; i++) {
        fi >> val[i];
        updateHld(1, i, val[i]);
    }

    
    while (q--) {
        char op;
        fi >> op;
        if (op == 'Q') {
            int x;
            fi >> x;

            int ans = queryHld(1) - queryHld(x);
            for (auto v: G[x])
                if (v != p[x]) {
                    ans = max(ans, queryHld(v));
                }

            fo << ans << "\n";
            
        }
        else {
            int v, nod;
            fi >> v >> nod;
            updateHld(1, nod, v);
        }
    }


    return 0;
}
