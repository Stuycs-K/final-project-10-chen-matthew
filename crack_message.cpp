#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("lzcnt")

#include <bits/stdc++.h>
#include <gmpxx.h>
#include "debug.cpp"

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

bool is_quadratic_residue(mpz_class& n, int p) {
    mpz_class x;
    mpz_powm(x.get(), n.get(), z((p-1)/2), z(p));
    return x == 1;
}

void rref(vector<vector<bool>>& a) {
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
    }

    //convert to row reduced echelon form (rref)
    for (int i = 0; i < n; i++) {
        int col = -1;
        for (int j = 0; j < m; j++) {
            if (a[i][j] != 0) {
                col = j;
                break;
            }
        }
        if (col == -1) continue;

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
}

int main(int argc, char* argv[]) {
    mpz_class n(argv[1]);
    //smoothness bound, usually computation bottleneck
    const int B = atoi(argv[2]);

    //increase EPS to increase chances of nontrivial factor of N
    const int EPS = atoi(argv[3]);
    //need to factorize n into p and q
    //return d to get private key

    //get all primes up to B
    vector<bool> prime(B, 1);
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

    //assumes N isnt a trivial perfect square
    mpz_class root;
    mpz_sqrt(root.get(), n.get());
    root++;

    //bruteforce to find B-smooth numbers
    vector<int> ind;
    vector<mpz_class> smooths;
    vector<vector<bool>> matrix;
    for (int i = 0; smooths.size() <= factor_base.size()+EPS; i++) {
        mpz_class r = root+i;
        mpz_class x = r*r - n;
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
            smooths.push_back(r*r - n);
            matrix.push_back(freq);
            ind.push_back(i);
        }
    }

    //transpose matrix
    vector<vector<bool>> matrix_t(matrix[0].size(), vector<bool>(matrix.size()));
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            matrix_t[j][i] = matrix[i][j];
        }
    }

    //now solve for SxM = [0 0 ... 0] on GF(2) by using RREF form
    rref(matrix_t);
    vector<int> pivot(matrix_t.size());
    vector<bool> unknowns(matrix_t[0].size());
    for (int i = 0; i < matrix_t.size(); i++) {
        int col = -1;
        for (int j = 0; j < matrix_t[0].size(); j++) {
            if (matrix_t[i][j] != 0) {
                col = j;
                break;
            }
        }
        pivot[i] = col;
    }

    mpz_class prod = 1, sq;
    do {
        for (int i = 0; i < unknowns.size(); i++) {
            unknowns[i] = (abs((int)rng())%(B/2) == 0);
        }
        for (int i = 0; i < matrix_t.size(); i++) {
            if (pivot[i] != -1) {
                for (int j = pivot[i]+1; j < matrix_t[0].size(); j++) {
                    unknowns[pivot[i]] = unknowns[pivot[i]] ^ (matrix_t[i][j] && unknowns[j]);
                }
            }
        }

        prod = 1, sq = 1;
        for (int i = 0; i < unknowns.size(); i++) {
            if (unknowns[i]) {
               prod *= smooths[i];
            }
        }
        mpz_sqrt(sq.get(), prod.get());
    } while (prod == 1 || prod != sq * sq);

    mpz_class og = 1;
    for (int i = 0; i < unknowns.size(); i++) {
        if (unknowns[i]) {
            og *= (root+ind[i]);
        }
    }

    mpz_class gcd1, gcd2;
    mpz_gcd(gcd1.get(), z(og+sq), n.get());
    mpz_gcd(gcd2.get(), z(og-sq), n.get());
    debug(gcd1);
    debug(gcd2);

    cout << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
}