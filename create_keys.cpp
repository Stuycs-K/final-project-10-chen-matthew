#include <bits/stdc++.h>
#include "debug.cpp"
using namespace std;
using ll = long long;

const int EXP = 65537;//public, 2^16 + 1

const int K = 40;
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

//taken from cp algo
int extended_gcd(int a, int b, int& x, int& y) {
    x = 1, y = 0;
    int x1 = 0, y1 = 1, a1 = a, b1 = b;
    while (b1) {
        int q = a1 / b1;
        tie(x, x1) = make_tuple(x1, x - q * x1);
        tie(y, y1) = make_tuple(y1, y - q * y1);
        tie(a1, b1) = make_tuple(b1, a1 - q * b1);
    }
    return a1;
}

int modular_inverse(int v, int m) {
    v %= m;
    int a = v, b = m, x, y;
    int g = extended_gcd(a,b,x,y);
    assert(g == 1);
    return (x+m)%m;
}

int main(int argc, char* argv[]) {
    int p = 97, q = 1E9+7;
    //int p = abs((int)rng())|1, q = abs((int)rng())|1;//private
    debug(p);
    debug(q);
    while (!is_prime(p)) p += 2;
    while (!is_prime(q)) q += 2;

    int n = p*q;//public
    int totient = lcm(p-1,q-1);//private
    int d = modular_inverse(EXP, totient); //incomplete, should be inverse of e mod totient
    
    //public key is (n, EXP), used for encrypt_message.cpp
    //private key is (n, d), used for decrypt_message.cpp
    printf("Your public key will be (%d, %d)\n", n, EXP);
    printf("Your private key will be (%d, %d)\n", n, d);
    return 0;
}