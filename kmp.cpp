#define MAXN 10000
#define _match(a,b) ((a) == (b))

typedef char elem_t;

int pattern_match(int ls, elem_t*str, int lp, elem_t *pat) {
    int fail[MAXN] = {-1}, i = 0, j;

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
