#include <bits/stdc++.h>
#include "debug.cpp"
using namespace std;

const double EPS = 1e-9;
const int INF = 2; // it doesn't actually have to be infinity or a big number

int gauss (vector < vector<double> > a, vector<double> & ans) {
    int n = (int) a.size();
    int m = (int) a[0].size() - 1;

    vector<int> where (m, -1);
    for (int col=0, row=0; col<m && row<n; ++col) {
        int sel = row;
        for (int i=row; i<n; ++i)
            if (abs (a[i][col]) > abs (a[sel][col]))
                sel = i;
        if (abs (a[sel][col]) < EPS)
            continue;
        for (int i=col; i<=m; ++i)
            swap (a[sel][i], a[row][i]);
        where[col] = row;

        for (int i=0; i<n; ++i)
            if (i != row) {
                double c = a[i][col] / a[row][col];
                for (int j=col; j<=m; ++j)
                    a[i][j] -= a[row][j] * c;
            }
        ++row;

        for (auto& i: a) debug(i);
        cout<<'\n';
    }

    ans.assign (m, 0);
    for (int i=0; i<m; ++i)
        if (where[i] != -1)
            ans[i] = a[where[i]][m] / a[where[i]][i];
    for (int i=0; i<n; ++i) {
        double sum = 0;
        for (int j=0; j<m; ++j)
            sum += ans[j] * a[i][j];
        if (abs (sum - a[i][m]) > EPS)
            return 0;
    }

    for (int i=0; i<m; ++i)
        if (where[i] == -1)
            return INF;
    return 1;
}

int main() {
    vector<vector<double>> a = {{2,-2,0,-6}, {1,-1,1,1}, {0,3,-2,-5}};
    //vector<vector<double>> a = {{1,0,1,0}, {0,1,1,0}, {0,1,1,0}, {1,1,0,0}};
    vector<double> ans;
    debug(gauss(a, ans));
    debug(ans);
    
    /*vector<bitset<4>> a(4);
    a[0] = bitset<4>("1010");
    a[1] = bitset<4>("0110");
    a[2] = bitset<4>("0110");
    a[3] = bitset<4>("1100");
    bitset<4> ans;
    gauss(a, 4, 4, ans);*/

}