#include <cstdio>
#include <algorithm>

using namespace std;

struct edge_t {
    int f, t, w;
} link[128 * 128];

int n, set[128], ind;

int find(int x) {
    int r = x, i;

    while (r != set[r]) {
        r = set[r];
    }

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

    if (fx != fy)
        set[fx] = fy;
}

bool cmp(const edge_t &lhs, const edge_t &rhs) {
    return lhs.w < rhs.w ? true : false;
}

int kruskal(struct edge_t *link) {
    int min = 0;

    for (int i = 0; i < ind; i++) {
        if (find(link[i].f) != find(link[i].t)) {
            min += link[i].w;
            merge(link[i].f, link[i].t);
        }
    }

    return min;
}

int main(int argc, char *argv[]) {
    /* usaco: agrinet */

    freopen("agrinet.in", "r", stdin);
    freopen("agrinet.out", "w", stdout);

    int w;
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            scanf("%d", &w);
            if (j > i) {
                link[ind].f = i;
                link[ind].t = j;
                link[ind++].w = w;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        set[i] = i;
    }

    sort(link, link + ind, cmp);

    printf("%d\n", kruskal(link));

    return 0;
}
