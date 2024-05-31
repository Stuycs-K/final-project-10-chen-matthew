#include <bits/stdc++.h>
#include <gmpxx.h>
#include "debug.cpp"

using namespace std;

int main(int argc, char* argv[]) {
    assert(argc == 4);
    mpz_class n(argv[1]), d(argv[2]), cipher(argv[3]);
    mpz_class message;
    mpz_powm(message.get_mpz_t(), cipher.get_mpz_t(), d.get_mpz_t(), n.get_mpz_t());
    gmp_printf("Your decrypted message is: %Zd\n", message);
}