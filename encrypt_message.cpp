#include <bits/stdc++.h>
#include <gmpxx.h>
#include "debug.cpp"

using namespace std;

int main(int argc, char* argv[]) {
    assert(argc == 4);
    mpz_class n(argv[1]), e(argv[2]), message(argv[3]);
    mpz_class c;
    mpz_powm(c.get(), message.get(), e.get(), n.get());
    gmp_printf("Your encrypted message is: %Zd\n", c);
}