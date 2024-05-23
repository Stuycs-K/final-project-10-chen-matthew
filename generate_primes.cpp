#include <bits/stdc++.h>
#include "debug.cpp"
using namespace std;
using ll = long long;

const int K = 40;
const int EXP = 65537;//public, 2^16 + 1
const int NUMPRIMES = 18;
const int primes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61};

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

//binary exponentiation to calculate (b^p) mod m
int bExpo(int b, int p, int mod) {
    b %= mod;
    int ans = 1;
    while (p) {
        if (p&1) ans = ((ll)ans*b)%mod;
        b = ((ll)b*b)%mod;
        p >>= 1;
    }
    return ans;
}

//miller rabin primality test with K iterations
bool miller_rabin_is_prime(int n) {
    int s = 0, tmp = n-1, d;
    while (!(tmp&1)) {
        s++;
        tmp >>= 1;
    }
    d = tmp;

    for (int i0 = 0; i0 < K; i0++) {
        int a = abs((int)rng())%(n-1);
        while (a < 2) a = abs((int)rng())%(n-1);
        int x = bExpo(a, d, n);
        int y;
        for (int i1 = 0; i1 < s; i1++) {
            y = ((ll)x*x)%n;
            if (y == 1 && x != 1 && x != n-1) {
                return 0;
            }
            x = y;
        }
        if (y != 1) {
            return 0;
        }
    }
    return 1;
}

bool is_prime(int n) {
    if ((!(n&1) && n != 2) || n < 2) return 0;
    for (int i = 0; i < NUMPRIMES; i++) {
        if (n == primes[i]) return 1;
        if (n%primes[i] == 0) return 0;
    }
    return miller_rabin_is_prime(n);
}

array<int,3> bezouts_euclidean(int a, int b) {
    //array<int,3> 

}

signed main() {
    int p = abs((int)rng())|1, q = abs((int)rng())|1;//private
    debug(p);
    debug(q);
    while (!is_prime(p)) p += 2;
    while (!is_prime(q)) q += 2;

    int n = p*q;//public
    int totient = lcm(p-1,q-1);//private
    int d; //incomplete, should be inverse of e mod totient
    
    //public values are n and EXP
    //this will be used for key generation
}