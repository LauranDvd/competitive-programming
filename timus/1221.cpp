#include <iostream>
#define NMAX 105
using namespace std;

int n;
int M[NMAX][NMAX];
int st[NMAX][NMAX], dr[NMAX][NMAX];

void calc()
{
    for (int i = 1; i <= n; i++)
        for (int j = 1; j <= n; j++)
            if (M[i][j] == 0)
                st[i][j] = st[i][j - 1] + 1;
            else
                st[i][j] = 0;

     for (int i = 1; i <= n; i++)
        for (int j = n; j >= 1; j--)
            if (M[i][j] == 0)
                dr[i][j] = dr[i][j + 1] + 1;
            else
                dr[i][j] = 0;
}

int main()
{
    ios_base::sync_with_stdio(false);
    while (1)
    {
        cin >> n;
        if (n == 0)
            break;

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
                cin >> M[i][j];

        calc();

        int maxim = 0;

        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                bool mustCobor = 0;

                if (st[i][j] != 1 || dr[i][j] != 1) 
                    continue;

                int cur = 0, sens = 1; /// 1: creste
                for (int k = i + 1; k <= n; k++)
                {
                    if (M[k][j] == 1) /// s-o dus
                        break;

                    if (st[k][j] == cur + 2 && dr[k][j] == cur + 2) /// progres
                    {
                        if (mustCobor)
                            break;

                        if (sens == -1) /// trebuia sa coboram
                            break;
                        else
                            cur++;
                    }
                    else if (st[k][j] >= cur + 2 && dr[k][j] >= cur + 2) /// data viit. cobor
                    {
                        if (mustCobor)
                            break;

                        mustCobor = 1;
                        cur++;
                    }
                    else if (st[k][j] == cur && dr[k][j] == cur) /// regres
                    {
                        if (cur == 1) /// final
                        {
                            maxim = max(maxim, k - i + 1);
                            break;
                        }

                        if (sens == -1)
                            cur--;
                        else /// pana acum urcam
                        {
                            sens = -1;
                            cur--;
                        }
                    }
                    else
                        break;
                }
            }
        if (maxim > 0)
            cout << maxim << "\n";
        else
            cout << "No solution\n";
    }

    return 0;
}

