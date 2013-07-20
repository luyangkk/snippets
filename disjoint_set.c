int set[N];

int find(int x) {
    int r = x;
    while (r != set[r])
        r = set[r];

    int i = x;
    while (x != r) {
        i = set[x];
        set[x] = r;
        x = i;
    }

    return r;
}

void merge(int x, int y) {
    int fx = find(x);
    int fy = find(y);
    if (fx != fy) {
        set[fx] = fy;
    }
}
