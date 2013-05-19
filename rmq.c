#include <stdio.h>

#define cmp(a, b) ((a) < (b) ? (a) : (b))

int dp[8][64];

void rmq_init(int *v, int n) {
    for (int i = 0; i < n; i++)
        dp[i][0] = v[i];

    for (int j = 1; (1 << j) <= n; j++)
        for (int i = 0; i + (1 << j) - 1 < n; i++)
            dp[i][j] = cmp(dp[i][j - 1], dp[i + (1 << (j - 1))][j - 1]);
}

int rmq_query(int i, int j) {
    int k = 0, d = j - i;
    while (d >> 1) {
        k++;
        d >>= 1;
    }

    printf("k: %d\n", k);

    return cmp(dp[i][k], dp[j - (1 << k) + 1][k]);
}

int main(int argc, char *argv[]) {
    int v[] = {3, 45, 6, 7, 8, 10, 22, 3, 1, 6};
    rmq_init(v, 10);

    int f, t;
    while (scanf("%d %d", &f, &t)) {
        printf("%d - %d: %d\n", f, t, rmq_query(f, t));
    }

    return 0;
}
