#include <bits/stdc++.h>
#include "debug.cpp"
using namespace std;
using ll = long long;

const int K = 20;
const int N = 1E2+1;

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

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
        int a = rng()%(n-5)+2;
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
int main() {
    vector<bool> prime(N, 1);
    for (int i = 2; i < N; i++) {
        if (!prime[i] || (ll)i*i > N) continue;
        for (int j = i*i; j < N; j += i) {
            prime[j] = 0;
        }
    }
    debug(prime);
    for (int i = 2; i < N; i++) {
        if (miller_rabin_is_prime(i) != prime[i]) {
            debug(i);
        }

    }
}