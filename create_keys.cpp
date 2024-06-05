#include <bits/stdc++.h>
#include <gmpxx.h>
#include "debug.cpp"

using namespace std;

const int EXP = 65537;//public, 2^16 + 1
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int main(int argc, char* argv[]) {
    const int N = atoi(argv[1]);//primes range from 2**(N-1) to 2**N-1
    gmp_randclass rando(gmp_randinit_mt);
    rando.seed(rng());
    mpz_class p = rando.get_z_bits(N), q = rando.get_z_bits(N);
    mpz_nextprime(p.get(), p.get());
    mpz_nextprime(q.get(), q.get());

    mpz_class n = p*q;
    mpz_class totient, a = p-1, b = q-1;
    mpz_lcm(totient.get(), a.get(), b.get());

    mpz_class d;
    mpz_invert(d.get(), ((mpz_class)EXP).get(), totient.get());
    
    //public key is (n, EXP), used for encrypt_message.cpp
    //private key is (n, d), used for decrypt_message.cpp
    gmp_printf("Your public key will be (%Zd, %d)\n", n, EXP);
    gmp_printf("Your private key will be (%Zd, %Zd)\n", n, d);
    return 0;
}