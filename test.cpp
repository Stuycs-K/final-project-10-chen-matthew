#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2,bmi,bmi2,lzcnt,popcnt")
#include<bits/stdc++.h>
#include <gmpxx.h>
using namespace std;
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
vector<bool> nullspace(vector<vector<bool>>& a) {
    int n = a.size();
    int m = a[0].size();
    //convert to echelon form (ref)
    int col = 0;
    for (int i = 0; i < n; i++) {
        while (col < m && a[i][col] == 0) {
            for (int j = i; j < n; j++) {
                if (a[j][col] != 0) {
                    swap(a[i], a[j]);
                    break;
                }
            }
            if (a[i][col] == 0) col++;
        }
        if (col >= m) break;
        
        for (int j = i+1; j < n; j++) {
            if (a[j][col] != 0) {
                for (int k = col; k < m; k++) {
                    a[j][k] = a[j][k] ^ a[i][k];
                }
            }
        }
        for (auto i: a) debug(i);
        cout<<'\n';
    }

    vector<int> pivot(n);
    //convert to row reduced echelon form (rref)
    for (int i = 0; i < n; i++) {
        int col = -1;
        for (int j = 0; j < m; j++) {
            if (a[i][j] != 0) {
                col = j;
                break;
            }
        }
        pivot[i] = col;
        if (col == -1) continue;

        /*bool val = a[i][col];
        for (int j = 0; j < m; j++) {
            a[i][j] /= val;
        }*/

        //for each row above i
        for (int j = 0; j < i; j++) {
            if (a[j][col] != 0) {
                //for each column after col in row j
                for (int k = col; k < m; k++) {
                    a[j][k] = a[j][k] ^ a[i][k];
                }
            }
        }
    }
    debug(pivot);

    vector<bool> unknowns(m, 1);//1 is just arbitrary value
    for (int i = 0; i < n; i++) {
        if (pivot[i] != -1) {
            bool sum = 0;
            for (int j = pivot[i]+1; j < m; j++) {
                sum ^= a[i][j] && unknowns[j];
            }
            unknowns[pivot[i]] = sum;
        }
    }
    debug(unknowns);
    return unknowns;
}

int main() {
    /*vector<vector<bool>> a = {
        {1,0,1,1},
        {0,1,1,1},
        {0,1,1,1},
        {1,1,0,1}
    };*/
    vector<vector<int>> a = {
        {1,3,3,2},
        {2,6,9,7},
        {-1,-3,3,4}
    };
    /*vector<vector<double>> a = {
        {1,2,0,3},
        {2,4,0,7}
    };*/
    //nullspace(a);
    for (auto i: a) debug(i);
}