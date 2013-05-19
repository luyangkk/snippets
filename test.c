#include <stdio.h>
#include <string.h>
#include <math.h>


void foo(int a[]) {
    a[0] = 5;
    a[1] = 2;
}

int main() {

int b[] = {1, 1, 1};
    foo(b);
    printf("%d %d %d\n", b[0], b[1], b[2]);
    return 0;
}
