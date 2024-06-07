#include <bits/stdc++.h>
#include "debug.cpp"
using namespace std;


int main() {
    auto s1 = 1.0 * clock() / CLOCKS_PER_SEC;
    int x = 0;
    for (int i = 0; i < 1E7; i++) {
        x++;
    }
    cout<<x<<'\n';
    auto s2 = 1.0 * clock() / CLOCKS_PER_SEC;
    debug(s2-s1);
}