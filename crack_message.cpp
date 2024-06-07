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

//just for convenience in reading
using ll = long long;

//binary exponentiation
int modpow(ll b, ll k, const int mod) {
    int ans = 1%mod;
    b %= mod;
    if (b < 0) b += mod;
    while (k) {
        if (k&1) ans = (ll)ans*b%mod;
        b = (ll)b*b%mod;
        k >>= 1;
    }
    return ans;
}

//finds r such that r^2 mod p = a using shanks-tonelli algorithm
int modulo_sqrt(int a, int p) {
    a %= p;
    if (a < 0) a += p;
    if (a == 0) return 0;
    if (modpow(a, (p-1)/2, p) != 1) return -1;//no solution
    if (p%4 == 3) return modpow(a, (p+1)/4, p);
    int s = p-1, n = 2, r = 0, m;
    while (s%2 == 0) r++, s /= 2;
    //setup done, now do shanks-tonelli
    while (modpow(n, (p-1)/2, p) != p-1) ++n;
    int x = modpow(a, (s+1)/2, p);
    int b = modpow(a, s, p), g = modpow(n, s, p);
    for (;; r = m) {
        int t = b;
        for (m = 0; m < r && t != 1; m++) t = 1LL*t*t%p;
        if (m == 0) return x;
        int gg = modpow(g, 1LL<<(r-m-1LL), p);
        g = 1LL*gg*gg%p;
        x = 1LL*x*gg%p;
        b = 1LL*b*g%p;
    }
}

int main(int argc, char* argv[]) {
    mpz_class n(argv[1]);
    //smoothness bound, usually the computation bottleneck so choose B wisely
    const int B = atoi(argv[2]);

    //increase EPS to increase chances of nontrivial factor of N
    const int EPS = atoi(argv[3]);
    
    //just a number to pad out our matrix
    const int PAD = 10;

    //our goal is to factorize n into p and q
    //then, return d which is private key

    auto s1 = 1.0 * clock() / CLOCKS_PER_SEC;

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

            if ((ll)i*i > B) continue;
            //regular sieve to eliminate primes
            for (int j = i*i; j <= B; j += i) {
                prime[j] = 0;
            }
        }
    }

    auto s2 = 1.0 * clock() / CLOCKS_PER_SEC;
    cout<<"find factor base: "<<(s2-s1) << '\n';

    //assumes N isnt a trivial perfect square, otherwise we can just return root
    mpz_class root;
    mpz_sqrt(root.get(), n.get());
    root++;

    //bruteforce to find B-smooth numbers
    vector<int> ind;
    vector<mpz_class> smooths;
    vector<vector<bool>> matrix;
    
    //1E7 which is large enough so we can probably find enough smooth numbers
    //if we cant, increase 1E7 to 1E8 but it'll prob already be too big
    vector<array<mpz_class,2>> sieve(1E7);
    
    //populate sieve, sieve[i][0] will be divided, sieve[i][1] just stores original
    for (int i = 0; i < sieve.size(); i++) {
        mpz_class r = root+i;
        sieve[i][0] = sieve[i][1] = r*r - n;
    }

    for (int j = 0; j < factor_base.size(); j++) {
        //find the roots i of (root + i)^2 - n mod f
        int f = factor_base[j];
        mpz_class tmp = n%f;
        int uitmp = tmp.get_ui();
        mpz_class tmp2 = root%f;
        int m = modulo_sqrt(uitmp, f);
        int r1 = ((m - (int)tmp2.get_ui())%f+f)%f;
        int r2 = ((-m - (int)tmp2.get_ui())%f+f)%f;

        //typical sieve-like setup
        for (int i = r1; i < sieve.size(); i += f) {
            while (sieve[i][0]%f == 0) {
                sieve[i][0] /= f;
            }
        }
        //check for the f = 2 case
        if (r1 == r2) continue;
        for (int i = r2; i < sieve.size(); i += f) {
            while (sieve[i][0]%f == 0) {
                sieve[i][0] /= f;
            }
        }
    }
    auto s3 = 1.0 * clock() / CLOCKS_PER_SEC;
    cout<<"finish sieve: "<<(s3-s2) << '\n';

    //find the B-smooth numbers and find the frequency of primes in its factored representation
    for (int i = 0; i < sieve.size(); i++) {
        if (sieve[i][0] == 1) {
            ind.push_back(i);
            smooths.push_back(sieve[i][1]);
            //manually calculate the powers instead of storing in the sieve to reduce memory usage and time
            vector<bool> freq(factor_base.size());
            for (int j = 0; j < factor_base.size(); j++) {
                int f = factor_base[j];
                while (sieve[i][1]%f == 0) {
                    sieve[i][1] /= f;
                    freq[j] = freq[j]^1;
                }
            }
            matrix.push_back(freq);
        }
    }
    auto s4 = 1.0 * clock() / CLOCKS_PER_SEC;
    cout<<"find smooths: "<<(s4-s3) << '\n';
   
    debug(smooths.size());
    debug(factor_base.size());
    //B isnt large enough
    assert(smooths.size() > factor_base.size());

    //transpose matrix (ie flip matrix across diagonal) so we can use rref on it
    vector<vector<bool>> matrix_t(matrix[0].size(), vector<bool>(matrix.size()));
    for (int i = 0; i < matrix.size(); i++) {
        for (int j = 0; j < matrix[0].size(); j++) {
            matrix_t[j][i] = matrix[i][j];
        }
    }

    auto s5 = 1.0 * clock() / CLOCKS_PER_SEC;
    cout<<"flip matrix: "<<(s5-s4) << '\n';

    //now solve for x in Ax = [0 0 ... 0] on GF(2) by using RREF form
    rref(matrix_t);
    vector<int> pivot(matrix_t.size());
    //unknowns is our solution vector
    vector<bool> unknowns(matrix_t[0].size());

    auto s6 = 1.0 * clock() / CLOCKS_PER_SEC;
    cout<<"convert rref: "<<(s6-s5) << '\n';

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
            unknowns[i] = (abs((int)rng())%(B/EPS+1) == 0);
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

    auto s7 = 1.0 * clock() / CLOCKS_PER_SEC;
    cout<<"repeat for nontrivial: "<<(s7-s6) << '\n';

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