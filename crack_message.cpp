#include <bits/stdc++.h>
#include <gmpxx.h>
#include "debug.cpp"

using namespace std;

//smoothness bound
const int B = 500;
//increase EPS to increase chances of nontrivial factor of N
const int EPS = 10;

bool is_quadratic_residue(mpz_class& n, int p) {
    mpz_class x;
    mpz_powm(x.get(), n.get(), z((p-1)/2), z(p));
    return x == 1;
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
    debug(smooths.size());
    for (auto& i: matrix) debug(i);

    //now solve for SxM = [0 0 ... 0] on GF(2) by Gaussian Elim

}