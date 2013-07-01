#define MAXN 10000
#define _match(a,b) ((a) == (b))

int kmp(char *str, int ls, char *pat, int lp) {
    int fail[MAXN] = {-1}, i, j;

    for (j = 1; j < lp; j++) {
        for (i = fail[j - 1]; i >= 0 && !_match(pat[i + 1], pat[j]); i = fail[i]);
        fail[j] = (_match(pat[i + 1], pat[j]) ? i + 1 : -1);
    }

    for (i = j = 0; i < ls && j < lp; i++) {
        if ( _match(str[i], pat[j]))
            j++;
        else if (j)
            j = fail[j - 1] + 1, i--;
    }

    return j == lp ? (i - lp ) : -1;
}
