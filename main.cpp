#include <bits/stdc++.h>

#include "cube.h"

int main() {
    printf("Hello World\n");

    Cube cube;
    cube.print();

    cube.parse("U2 L2 Rw r (ULRU)");

    cube.print();
}
