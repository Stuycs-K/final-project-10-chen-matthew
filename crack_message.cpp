//some pragmas so it optimizes runtime
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("lzcnt")

#include <bits/stdc++.h>
#include <gmpxx.h>
#include "debug.cpp"

using namespace std;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//checks if n is a quadratic residue mod p using euler's criterion
//if n^((p-1)/2) = 1 mod p, then n is a quadratic residue
bool is_quadratic_residue(mpz_class& n, int p) {
    mpz_class x;
    mpz_powm(x.get(), n.get(), z((p-1)/2), z(p));
    return x == 1;
}

//takes a binary matrix and converts it into row reduced echelon form
//this form is much easier to handle when finding the solutions x such that Ax = 0
void rref(vector<vector<bool>>& a) {
    int n = a.size();
    int m = a[0].size();

    //convert to echelon form (ref)
    int col = 0;
    for (int i = 0; i < n; i++) {
        //find a row with nonzero entry at col
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

        //reduce previous rows so that we obtain a triangular form        
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
    //smoothness bound, usually the computation bottleneck so choose B wisely
    const int B = atoi(argv[2]);

    //increase EPS to increase chances of nontrivial factor of N
    const int EPS = atoi(argv[3]);

    //our goal is to factorize n into p and q
    //then, return d which is private key

    //get all primes up to B
    vector<bool> prime(B, 1);
    //primes less than or equal to B where N is a quadratic residue with that prime as mod
    vector<int> factor_base;
    for (int i = 2; i <= B; i++) {
        if (prime[i]) {
            //filter using euler's criterion to see when n is a quad residue mod i
            if (is_quadratic_residue(n, i)) {
                factor_base.push_back(i);
            }

            if ((long long)i*i > B) continue;
            //regular sieve to eliminate primes
            for (int j = i*i; j <= B; j += i) {
                prime[j] = 0;
            }
        }
    }

    //assumes N isnt a trivial perfect square, otherwise we can just return root
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
        //the exponent of all primes in factored form of r reduced to binary
        vector<bool> freq(factor_base.size());
        for (int i = 0; i < factor_base.size(); i++) {
            int f = factor_base[i];
            while (x%f == 0) {
                x /= f;
                freq[i] = freq[i]^1;
            }
        }

        //our number is B-smooth
        if (x == 1) {
            smooths.push_back(r*r - n);
            matrix.push_back(freq);
            //keep ind so we can obtain both original square and the difference between square and N
            ind.push_back(i);
        }
    }

    //transpose matrix (ie flip matrix across diagonal) so we can use rref on it
    vector<vector<bool>> matrix_t(matrix[0].size(), vector<bool>(matrix.size()));
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            matrix_t[j][i] = matrix[i][j];
        }
    }

    //now solve for x in Ax = [0 0 ... 0] on GF(2) by using RREF form
    rref(matrix_t);
    vector<int> pivot(matrix_t.size());
    //unknowns is our solution vector
    vector<bool> unknowns(matrix_t[0].size());

    //find all the pivots in each row
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

    //repeat this loop so that we don't get a weird case where the solution isn't a perfect square
    mpz_class prod = 1, sq;
    do {
        for (int i = 0; i < unknowns.size(); i++) {
            //B/8 is arbitrary, might want to change it depending on how frequent our trivial factors are
            unknowns[i] = (abs((int)rng())%(B/8+1) == 0);
        }
        for (int i = 0; i < matrix_t.size(); i++) {
            if (pivot[i] != -1) {
                for (int j = pivot[i]+1; j < matrix_t[0].size(); j++) {
                    unknowns[pivot[i]] = unknowns[pivot[i]] ^ (matrix_t[i][j] && unknowns[j]);
                }
            }
        }

        //righthand side product
        prod = 1, sq = 1;
        for (int i = 0; i < unknowns.size(); i++) {
            if (unknowns[i]) {
               prod *= smooths[i];
            }
        }
        mpz_sqrt(sq.get(), prod.get());
    } while (prod == 1 || prod != sq * sq);

    //lefthand side product
    mpz_class og = 1;
    for (int i = 0; i < unknowns.size(); i++) {
        if (unknowns[i]) {
            og *= (root+ind[i]);
        }
    }

    //chance that gcd1 and gcd2 are trivial factors of N (ie 1 and N) so we might have to run this multiple times
    mpz_class gcd1, gcd2;
    mpz_gcd(gcd1.get(), z(og+sq), n.get());
    mpz_gcd(gcd2.get(), z(og-sq), n.get());
    debug(gcd1);
    debug(gcd2);

    //print runtime so we can compare to the trial division algorithm, also so we can choose better bounds on B
    cout << "Time elapsed: " << 1.0 * clock() / CLOCKS_PER_SEC << " s.\n";
}