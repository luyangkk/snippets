#include <cstring>
#include <queue>

#define MAX_NODE 1024
#define SIGMA_SIZE 26

using namespace std;

struct Actomaton {

    /* tree array */
    char ch[MAX_NODE][SIGMA_SIZE];

    /* the values of nodes */
    int val[MAX_NODE];

    /* the number of nodes */
    int sz;

    /* the fail array */
    int f[MAX_NODE];

    /* the last array */
    int last[MAX_NODE];

    Actomaton() {
        sz = 1;
        init(0);
    }

    void init(int x) {
        memset(last, 0, sizeof(last));
        memset(ch[x], 0, sizeof(ch[x]));
        val[x] = 0;
    }

    int idx(char c) {
        return c - 'a';
    }

    void insert(char *s, int v) {
        int u = 0, n = strlen(s);
        for (int i = 0; i < n; i++) {
            int c = idx(s[i]);
            if (!ch[u][c]) {
                init(sz);
                ch[u][c] = sz++;
            }
            u = ch[u][c];
        }
        val[u] = v;
    }

    void getFail() {
        queue<int> q;
        f[0] = 0;
        for (int c = 0; c < SIGMA_SIZE; c++) {
            int u = ch[0][c];
            if (u) { f[u] = 0; q.push(u); last[u] = 0; }
        }

        while (!q.empty()) {
            int r = q.front(); q.pop();
            for (int c = 0; c < SIGMA_SIZE; c++) {
                int u = ch[r][c];
                if (!u) continue;
                q.push(u);
                int v = f[r];
                while (v && !ch[v][c]) v = f[v];
                f[u] = ch[v][c];
                last[u] = val[f[u]] ? f[u] : last[f[u]];
            }
        }
    }

    void find(char *s, int n) {
        int j = 0;

        for (int i = 0; i < n; i++) {
            int c = idx(s[i]);
            while (j && !ch[j][c]) j = f[j];
            j = ch[j][c];
            if (val[j])
                print(j);
            else if (last[j])
                print(last[j]);
        }
    }

    void print(int j) {
        if (j) {
            printf("%d: %d\n", j, val[j]);
            print(last[j]);
        }
    }

};

int main(int argc, char *argv[]) {
    Actomaton actomaton;

    actomaton.insert("he", 1);
    actomaton.insert("she", 1);
    actomaton.insert("his", 1);
    actomaton.insert("hers", 1);
    actomaton.getFail();

    char s[] = "she";
    actomaton.find(s, strlen(s));

    return 0;
}
