#include <bits/stdc++.h>
#include <gmpxx.h>
#include "debug.cpp"

using namespace std;

int main(int argc, char* argv[]) {
    assert(argc == 4);
    mpz_class n(argv[1]), d(argv[2]), cipher(argv[3]), message;
    mpz_powm(message.get(), cipher.get(), d.get(), n.get());
    gmp_printf("Your decrypted message is: %Zd\n", message);
}