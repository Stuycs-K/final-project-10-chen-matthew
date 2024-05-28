#include "math_lib.cpp"

int main(int argc, char* argv[]) {
    assert(argc == 4);
    int n = atoi(argv[1]), e = atoi(argv[2]), message = atoi(argv[3]);
    int c = bExpo(message, e, n);
    printf("Your encrypted message is: %d\n", c);
}