/// submitted by David Lauran on September 17, 2020
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;


const int NMAX = 105;
const int INF = 1e9;

int n, m;
int dist[NMAX][NMAX];
vector <pair<int,int>> G[NMAX];
int distDij[NMAX];
int lst[NMAX][NMAX][NMAX];
int ans = INF;

void dijkstra(int nod, int tata) {
   for (int i = 1; i <= n; i++)
      distDij[i] = INF;

   priority_queue <pair<int,int>> Q;
   Q.push({0, nod});
   distDij[nod] = 0;

   while (!Q.empty()) {
      int curr = Q.top().second;
      Q.pop();

      for (auto v: G[curr]) {
         if (v.first == tata)
            continue;

         if (distDij[curr] + v.second < distDij[v.first]) {
            distDij[v.first] = distDij[curr] + v.second;
            lst[nod][tata][v.first] = curr;
            Q.push({-distDij[v.first], v.first});
         }
      }
   }
}


int main()
{
   while (1) {
      scanf("%d", &n); if (n == -1) break;
      scanf("%d", &m);

      ans = INF;

      for (int i = 1; i <= n; i++)
         G[i].clear();

      for (int i = 1; i <= n; i++)
         for (int j = i + 1; j <= n; j++)
            dist[i][j] = dist[j][i] = INF;

      for (int i = 1; i <= n; i++)
         for (int j = 1; j <= n; j++)
            for (int k = 1; k <= n; k++)
               lst[i][j][k] = 0;

      for (int i = 1; i <= m; i++) {
         int u, v, c; scanf("%d %d %d", &u, &v, &c);

         dist[u][v] = dist[v][u] = min(dist[u][v], c);
      }

      for (int i = 1; i <= n; i++)
        for (int j = i + 1; j <= n; j++)
            if (dist[i][j] < INF) {
                G[i].push_back({j, dist[i][j]});
                G[j].push_back({i, dist[i][j]});
            }

      int aFinal = -1, bFinal = -1, cFinal = -1;
      for (int a = 1; a <= n; a++)
         for (auto b: G[a]) {
            if (b.second > ans || b.first < a)
               continue;

            dijkstra(b.first, a);

            for (auto c: G[a])
               if (c.first != b.first) {
                  int costAici = b.second + distDij[c.first] + c.second;
                  if (costAici < ans) {
                     ans = costAici;

                     aFinal = a; bFinal = b.first; cFinal = c.first;
                  }
               }
         }

        vector <int> af;
        af.push_back(cFinal);

        int curr = cFinal;
        while (curr != bFinal) {
            curr = lst[bFinal][aFinal][curr];
            af.push_back(curr);
        }
        af.push_back(aFinal);

      if (ans >= INF)
         printf("No solution.\n");
      else {
         for (auto x: af)
            printf("%d ", x);
         printf("\n");
      }
   }


   return 0;
}
