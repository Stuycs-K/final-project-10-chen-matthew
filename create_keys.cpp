#include "math_lib.cpp"

const int EXP = 65537;//public, 2^16 + 1

//note: lcm only works in c++17 so use that flag
int main(int argc, char* argv[]) {
    int p = 97, q = 1E9+7;
    //int p = abs((int)rng())|1, q = abs((int)rng())|1;//private
    debug(p);
    debug(q);
    while (!is_prime(p)) p += 2;
    while (!is_prime(q)) q += 2;

    int n = p*q;//public
    int totient = lcm(p-1,q-1);
    int d = modular_inverse(EXP, totient); //incomplete, should be inverse of e mod totient
    
    //public key is (n, EXP), used for encrypt_message.cpp
    //private key is (n, d), used for decrypt_message.cpp
    printf("Your public key will be (%d, %d)\n", n, EXP);
    printf("Your private key will be (%d, %d)\n", n, d);
    return 0;
}