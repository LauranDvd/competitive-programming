/// submitted by Lauran on January 10, 2020
#include <bits/stdc++.h>
using namespace std;
 
const int NMAX = 2e5 + 5;
 
int t;
int n;
int tmax;
int l[NMAX], r[NMAX];
set <int> toateNr;
map <int, int> newVal;
vector <int> in[10 * NMAX];
vector <int> out[10 * NMAX];
bool singurInceput[NMAX], singurFinal[NMAX];
int val[NMAX];
 
void curata() {
    toateNr.clear();
    newVal.clear();
    
    memset(singurInceput, 0, sizeof(singurInceput));
    memset(singurFinal, 0, sizeof(singurFinal));
    memset(val, 0, sizeof(val));
}
 
void normalizare() {
    int curr = 1;
    for (auto x: toateNr)
        newVal[x] = curr++;
    for (int i = 1; i <= n; i++) {
        l[i] = newVal[l[i]];
        r[i] = newVal[r[i]];
    }
    tmax = curr - 1;
}
 
int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0);
 
    cin >> t;
    while (t--) {
        curata();
 
        cin >> n;
        for (int i = 1; i <= n; i++) {
            cin >> l[i] >> r[i];
            toateNr.insert(l[i]);
            toateNr.insert(r[i]);
        }
        normalizare();
        for (int i = 1; i <= tmax; i++) {
            in[i].clear();
            out[i].clear();
        }
 
        for (int i = 1; i <= n; i++) {
            in[l[i]].push_back(i);
            out[r[i]].push_back(i);
        }
 
        // pt fiecare segment tin: daca este acum; de cate ori a ramas singur; daca a ramas singur la inceput
                                                                                    // sau la final
 
        int cntAcum = 0;
        set <int> setAcum;
        int ansInitial = 0;
        for (int i = 1; i <= tmax; i++) {
            for (auto x: in[i]) {
                cntAcum++;
                setAcum.insert(x);
            }
            if (cntAcum == 1 && in[i].size()) {
                // am un singur segment
                int segm = (*setAcum.begin());
                if (in[i].size()) {
                    // acum l-am introdus
                    singurInceput[segm] = 1;
                }
                val[segm]++;
            }
            for (auto x: out[i]) {
                cntAcum--;
                setAcum.erase(x);
            }
            if (cntAcum == 1 && out[i].size()) {
                // am un singur segment
                int segm = (*setAcum.begin());
                
                val[segm]++;
            }
 
            if (cntAcum == 0 && out[i].size() == 1) {
                // singur la final
                int segm = out[i][0];
                singurFinal[segm] = 1;
            }
 
            if (cntAcum == 0) {
                ansInitial++;
            }
        }
 
        //cout << ansInitial;
        int ans = 0;
        for (int i = 1; i <= n; i++) {
            val[i] = val[i] - singurInceput[i] - singurFinal[i];
            int ansHere = ansInitial + val[i];
            ans = max(ans, ansHere);
            //cout << val[i] << " ";
        }
 
        cout << ans << "\n";
 
    }
  
    return 0;
}
