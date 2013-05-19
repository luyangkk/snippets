#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define cmp(a, b) (a > b ? 1 : 0)

typedef int node_t;

typedef struct heap {
    node_t *v;
    int n;
    int size;
} heap;

heap *heap_init(int size) {
    heap *h;

    h = (heap *)malloc(sizeof(*h));
    h->v = (node_t *)malloc(sizeof(node_t) * size + 1);

    h->n = 0;
    h->size = size;

    return h;
}

int heap_push(heap *h, node_t x) {
    node_t *v = h->v;
    int i;

    if (h->n == h->size)
        return 1;

    i = ++h->n;
    while (i > 1 && cmp(x, v[i >> 1])) {
        v[i] = v[i >> 1];
        i >>= 1;
    }
    v[i] = x;

    return 0;
}

void heap_pop(heap *h, node_t *x) {
    node_t *v = h->v;
    int n = h->n, i = 1, j;

    if (h->n == 0) {
        x = NULL;
        return;
    }

    *x = v[i];

    for (j = 2; j < n; j <<= 1) {
        if (cmp(v[j + 1], v[j]))
            j++;

        if (!cmp(v[j], v[n]))
            break;

        v[i] = v[j];
        i = j;
    }

    v[i] = v[n];
    h->n--;
}

void heap_show(heap *h) {
    int i;
    for (i = 1; i <= h->n; i++) {
        printf("%d ", h->v[i]);
    }
    putchar('\n');
}

void heap_adjust(heap *h, int i, int n) {
    node_t *v = h->v, tmp;
    int j;

    tmp = v[i];
    j = i * 2;
    while (j <= n) {
        if (j < n && cmp(v[j + 1], v[j]))
            j++;

        if (!cmp(v[j], tmp))
            break;

        v[j >> 1] = v[j];
        j = j << 1;
    }

    v[j >> 1] = tmp;
}

heap *heap_build(node_t *l, int l_size) {
    int i;

    heap *h = (heap *)malloc(sizeof(heap));
    h->size = l_size;
    h->n = l_size;
    h->v = l;

    for (i = h->n >> 1; i > 0; i--) {
        heap_adjust(h, i, h->n);
    }

    return h;
}

void heap_sort(node_t *l, int l_size) {
    heap *h = heap_build(l, l_size);

    node_t tmp;
    for (int i = l_size - 1; i > 0; i--) {
        tmp = l[i + 1];
        l[i + 1] = l[1];
        l[1] = tmp;
        heap_adjust(h, 1, i);
    }
}

int main(int argc, char *argv) {
    srand(time(NULL));

    heap *h = heap_init(128);
    int i, x, l[21];

    printf("push:   ");
    for (i = 0; i < 20; i++) {
        x = rand() % 100;
        heap_push(h, x);
        printf("%d ", x);
    }
    putchar('\n');

    printf("pop:    ");
    for (i = 0; i < 20; i++) {
       heap_pop(h, &x);
       printf("%d ", x);
    }
    printf("\n\n");

    printf("build:  ");
    for (i = 1; i <= 20; i++) {
        l[i] = rand() % 100;
        printf("%d ", l[i]);
    }
    h = heap_build(l, 20);
    putchar('\n');

    printf("show:   ");
    heap_show(h);

    printf("pop:    ");
    for (i = 0; i < 20; i++) {
       heap_pop(h, &x);
       printf("%d ", x);
    }
    printf("\n\n");

    printf("raw:    ");
    for (i = 1; i <= 20; i++) {
        l[i] = rand() % 100;
        printf("%d ", l[i]);
    }
    putchar('\n');

    heap_sort(l, 20);

    printf("sorted: ");
    for (i = 1; i <= 20; i++) {
        printf("%d ", l[i]);
    }
    printf("\n\n");

    return 0;
}
