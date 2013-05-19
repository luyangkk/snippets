#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void find(int *v, int left, int right, int k) {
    if (left >= right) {
        return;
    }

    int l = left, r = right, m = l + (r - l) / 2, tmp;
    while (l < r) {
        while (l < right && v[l] > v[m])
            l++;
        while (r > left && v[r] < v[m])
            r--;

        if (l <= r) {
            tmp = v[l], v[l] = v[r], v[r] = tmp;
            l++, r--;
        }
    }

    if (k < r) {
        find(v, left, r, k);
    } else if (k > l) {
        find(v, l, right, k - l);
    }
}

int main(int argc, char *argv) {
    srand(time(NULL));

    int v[20];
    for (int i = 0; i < 20; i++) {
        v[i] = rand() % 20;
        printf("%d ", v[i]);
    }
    putchar('\n');

    find(v, 0, 19, 7);
    for (int i = 0; i < 7; i++) {
        printf("%d ", v[i]);
    }
    putchar('\n');

    int i, j;
    for (i = 8; i < 20; i++) {
        for (j = 0; j < 7; j++) {
            if (v[i] > v[j]) {
                break;
            }
        }
    }

    if (i == 20) {
        printf("right\n");
    } else {
        printf("wrong\n");
    }

    return 0;
}
