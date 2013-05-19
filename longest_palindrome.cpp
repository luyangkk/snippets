const char padding = '#';

char * preprocess(char *before, int len) {
    char *after = (char *)malloc(sizeof(char) * len * 2 + 2);

    int k = 0;
    after[k++] = padding;
    for (int i = 0; i < len; i++) {
        after[k++] = before[i];
        after[k++] = padding;
    }
    after[k] = '\0';

    return after;
}

char * longest_palindrome(char *s, int len) {
    char *t = preprocess(s, strlen(s));
    int n = strlen(t);
    int *p = (int *)malloc(sizeof(int) * n + 1);
    memset(p , 0, sizeof(int) * n + 1);
    int c = 0, r = 0 ;

    for (int i = 0; i < n - 1; i++) {
        p[i] = r > i ? min(p[2 * c - i ], r - i) : 1;

        while (t[i + p[i]] == t[i - p[i]])
            p[i]++;

        if (i + p[i] > r)
            r = i + p[i], c = i;
    }

    r = 0;
    for (int i = 0; i < n; i++) {
        if (p[i] > r)
            c = i, r = p[i];
    }

    int k = 0;
    char *v = (char *) malloc(sizeof(char) * r);
    for (int i = c - r + 1; i < c + r; i++) {
        if (t[i] != padding)
            v[k++] = t[i];
    }
    v[k] = '\0';

    free(t);
    free(p);

    return v ;
}
