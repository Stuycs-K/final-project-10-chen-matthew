#include <bits/stdc++.h>
#include <gmpxx.h>
#include "debug.cpp"

using namespace std;

//smoothness bound
const int B = 50;
//increase EPS to increase chances of nontrivial factor of N
const int EPS = 10;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

bool is_quadratic_residue(mpz_class& n, int p) {
    mpz_class x;
    mpz_powm(x.get(), n.get(), z((p-1)/2), z(p));
    return x == 1;
}

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
        //for (auto i: a) debug(i);
        //cout<<'\n';
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
    //debug(pivot);

    vector<bool> unknowns(m,1);
    //for (int i = 0; i < m; i++) {
    //    unknowns[i] = (abs((int)rng())%20 == 0);
   // }
    for (int i = 0; i < n; i++) {
        if (pivot[i] != -1) {
            bool sum = 0;
            for (int j = pivot[i]+1; j < m; j++) {
                sum ^= a[i][j] && unknowns[j];
            }
            unknowns[pivot[i]] = sum;
        }
    }
    //debug(unknowns);
    return unknowns;
}

int main(int argc, char* argv[]) {
    assert(argc == 2);
    mpz_class n(argv[1]);
    //need to factorize n into p and q
    //return d to get private key

    //get all primes up to B
    bitset<B> prime;
    prime.set();
    vector<int> factor_base;
    for (int i = 2; i <= B; i++) {
        if (prime[i]) {
            //filter using euler's criterion to see when n is a quad residue mod i
            if (is_quadratic_residue(n, i)) {
                factor_base.push_back(i);
            }

            if ((long long)i*i > B) continue;
            for (int j = i*i; j <= B; j += i) {
                prime[j] = 0;
            }
        }
    }
    debug(factor_base.size());

    //assumes N isnt a trivial perfect square
    mpz_class root;
    mpz_sqrt(root.get(), n.get());
    root++;
    debug(root);

    //bruteforce to find B-smooth numbers
    vector<mpz_class> smooths;
    vector<vector<bool>> matrix;
    for (;smooths.size() <= factor_base.size()+EPS; root++) {
        mpz_class x = root*root - n;
        vector<bool> freq(factor_base.size());
        for (int i = 0; i < factor_base.size(); i++) {
            int f = factor_base[i];
            while (x%f == 0) {
                x /= f;
                freq[i] = freq[i]^1;
            }
        }
        //B-smooth
        if (x == 1) {
            smooths.push_back(root*root - n);
            matrix.push_back(freq);
        }
    }

    //transpose matrix
    vector<vector<bool>> matrix_t(matrix[0].size(), vector<bool>(matrix.size()));
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            matrix_t[j][i] = matrix[i][j];
        }
    }
    for (auto& i: matrix_t) debug(i);
    //now solve for SxM = [0 0 ... 0] on GF(2) by Gaussian Elim

    vector<bool> sol = nullspace(matrix_t);
    debug(sol);
    debug(smooths);

    mpz_class prod = 1;
    for (int i = 0; i < sol.size(); i++) {
        if (sol[i]) {
            prod *= smooths[i];
        }
    }
    debug(prod);

    mpz_class ss;
    mpz_sqrt(ss.get(), prod.get());
    debug(ss);
}