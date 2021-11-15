/*
 * Write a program to find the length of the Longest Common Subsequence(LCS)
 * of two given sequences X and Y and print all possible LCS using
 * PRINT_LCS().
 */

#include <iostream>
#include <set>
using namespace std;

#define N 128

int l[N][N];

set<string> find_lcs(string x, string y, int m, int n)
{
    set<string> s;

    if ( m == 0 || n == 0 ) {
        s.insert("");
        return s;
    }

    if ( x[m - 1] == y[n - 1] ) {
        set<string> tmp = find_lcs(x, y, m - 1, n - 1);

        for (string str : tmp)
            s.insert(str + x[m - 1]);
    } else {
        if ( l[m - 1][n] >= l[m][n - 1] )
            s = find_lcs(x, y, m - 1, n);

        if ( l[m][n - 1] >= l[m - 1][n] ) {
            set<string> tmp = find_lcs(x, y, m, n - 1);
            s.insert(tmp.begin(), tmp.end());
        }
    }

    return s;
}

int length_lcs(string x, string y, int m, int n)
{
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j <= n; j++) {
            if ( i == 0 || j == 0 )
                l[i][j] = 0;
            else if ( x[i - 1] == y[j - 1] )
                l[i][j] = l[i - 1][j - 1] + 1;
            else
                l[i][j] = max(l[i - 1][j], l[i][j - 1]);
        }
    }
    return l[m][n];
}

static inline void print_lcs(string x, string y, int m, int n)
{
    set<string> s = find_lcs(x, y, m, n);

    int i = 1;
    for (string str : s) {
        cout << "LCS-" << i++ << " : " << str << endl;
    }
}

int main(void)
{
    string x;
    string y;

    cout << "Enter x : ";
    cin >> x;
    cout << "Enter y : ";
    cin >> y;

    int m = x.length();
    int n = y.length();

    cout << "\nLength of LCS : " << length_lcs(x, y, m, n) << endl;
    print_lcs(x, y, m, n);

    return EXIT_SUCCESS;;
}
