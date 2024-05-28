#include "math_lib.cpp"

int main(int argc, char* argv[]) {
    assert(argc == 4);
    int n = atoi(argv[1]), d = atoi(argv[2]), cipher = atoi(argv[3]);
    int message = bExpo(cipher, d, n);
    printf("Your decrypted message is: %d\n", message);
}