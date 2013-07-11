void get_fail(char *p, int l, int *f) {
    f[0] = f[1] = 0;
    for (int i = 1; i < l; i++) {
        int  j = f[i];
        while (j && p[i] != p[j])
            j = f[j];
        f[i + 1] = p[i] == p[j] ? j + 1 : 0;
    }
}

int find(char *s, int ls, char *p, int lp, int *f) {
    int j = 0;
    for (int i = 0; i < ls; i++) {
        while (j && s[i] != p[j]) j = f[j];
        if (s[i] == p[j]) j++;
        if (j == lp) return i - lp + 1;
    }
    return -1;
}