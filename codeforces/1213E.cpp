#include <bits/stdc++.h>
using namespace std;

int n;
string s, t;

string faS(char a, char b)
{
    string ret = "";
    ret += a;
    ret += b;
    return ret;
}

int main()
{
    cin >> n;
    cin >> s >> t;

    cout << "YES\n";

    if (s == t)
    {
        for (int i = 0; i < 27; i++)
        {
            char p = 'a' + i % 3;
            char q = 'a' + (i / 3) % 3;
            char r = 'a' + (i / 3 / 3) % 3;
            if (p != q && q != r && p != r)
            {
                if (s != faS(p, q) && s != faS(q, r) && s != faS(r, p))
                {
                    for (int j = 1; j <= n; j++)
                        cout << p << q << r;
                    break;
                }
            }
        }
    }
    else if (s[0] == t[0])
    {
        if (s[1] != s[0] && t[1] != t[0])
        {
            for (char c = 'a'; c <= 'c'; c++)
                if (c != s[0])
                    for (int i = 1; i <= n; i++)
                        cout << c;
            for (int i = 1; i <= n; i++)
                cout << s[0];
        }
        else
        {
            char celalalt = 'x';
            if (s[1] != s[0])
                celalalt = s[1];
            else
                celalalt = t[1];
            char nefolosit = 'x';
            for (char da = 'a'; da <= 'c'; da++)
                if (da != s[0] && da != celalalt)
                    nefolosit = da;

            for (int i = 1; i <= n; i++)
                cout << celalalt;
            for (int i = 1; i <= n; i++)
                cout << nefolosit << s[0];
        }
    }
    else if (s[1] == t[1])
    {
        if (s[0] != s[1] && t[0] != t[1])
        {
            for (int i = 1; i <= n; i++)
                cout << s[1];
            for (char c = 'a'; c <= 'c'; c++)
                if (c != s[1])
                    for (int i = 1; i <= n; i++)
                        cout << c;
        }
        else
        {
            char celalalt = 'x';
            if (s[1] != s[0])
                celalalt = s[0];
            else
                celalalt = t[0];
            char nefolosit = 'x';
            for (char da = 'a'; da <= 'c'; da++)
                if (da != s[1] && da != celalalt)
                    nefolosit = da;

            for (int i = 1; i <= n; i++)
                cout << celalalt;
            for (int i = 1; i <= n; i++)
                cout << nefolosit << s[1];
        }
    }
    else if (s[0] == t[1] && s[1] == t[0])
    {
        char nefolosit = 'x';
        for (char c = 'a'; c <= 'c'; c++)
            if (c != s[0] && c != s[1])
                nefolosit = c;
        for (int i = 1; i <= n; i++)
            cout << s[0];
        for (int i = 1; i <= n; i++)
            cout << nefolosit;
        for (int i = 1; i <= n; i++)
            cout << s[1];
    }
    else
    {
        for (int i = 0; i < 27; i++)
        {
            char p = 'a' + i % 3;
            char q = 'a' + (i / 3) % 3;
            char r = 'a' + (i / 3 / 3) % 3;
            if (p != q && q != r && p != r)
            {
                if (s != faS(p, q) && s != faS(q, r) && s != faS(r, p) &&
                    t != faS(p, q) && t != faS(q, r) && t != faS(r, p))
                {
                    for (int j = 1; j <= n; j++)
                        cout << p << q << r;
                    break;
                }
            }
        }
    }

    return 0;
}
