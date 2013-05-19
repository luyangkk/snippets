#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void quick_sort(int v[], int left, int right) {
    if (left >= right)
        return;

    int l = left, r = right;
    int pivot = v[l + (r - l) / 2], tmp;

    while (l < r) {
        while (l < right && v[l] < pivot)
            l++;
        while (r > left && v[r] > pivot)
            r--;
        if (l <= r) {
            tmp = v[l], v[l] = v[r], v[r] = tmp;
            l++, r--;
        }
    }

    quick_sort(v, left, r);
    quick_sort(v, l, right);
}

void non_recursive_quick_sort(int v[], int left, int right) {
    int stack[256], s = 0, l, r, pivot, tmp;

    stack[s++] = left, stack[s++] = right;
    while (s > 0) {
        right = stack[--s], left = stack[--s];

        if (left >= right)
            continue;

        l = left, r = right;
        pivot = v[l + (r - l) / 2];

        while (l < right && v[l] < pivot)
            l++;
        while (r > left && v[r] > pivot)
            r--;
        if (l <= r) {
            tmp = v[l], v[l] = v[r], v[r] = tmp;
            l++, r--;
        }

        stack[s++] = left, stack[s++] = r;
        stack[s++] = l, stack[s++] = right;
    }
}

typedef struct Node {
    int k;
    struct Node *next;
    struct Node *prev;
} Node;

void list_quick_sort(Node *from, Node *to) {
    if (!from || !to || from->prev == to)
        return;

    Node *f = from, *t = to;
    int pivot = from->k, tmp;

    while (1) {
        while (f != t && f->k < pivot)
            f = f->next;

        while(t != f && t->k > pivot)
            t = t->prev;

        if (f != t)
            tmp = f->k, f->k = t->k, t->k = tmp;

        if (f == t) {
            if (t->k < pivot)
                f = f->next;
            else if (t->k > pivot)
                t = t->prev;
            else
                f = f->next, t = t->prev;
            break;
        } else if (f->next == t) {
            f = f->next, t = t->prev;
            break;
        } else {
            f = f->next, t = t->prev;
        }
    }

    list_quick_sort(from, t);
    list_quick_sort(f, to);
}

int main(int argc, char* argv) {
    srand(time(NULL));
    int v[100], i;

    for (i = 0; i < 20; i++) {
        v[i] = rand() % 100;
        printf("%d ", v[i]);
    }
    putchar('\n');

    non_recursive_quick_sort(v, 0, 19);

    for (i = 0; i < 20; i++) {
        printf("%d ", v[i]);
        if (i > 0 && v[i] < v[i - 1])
            printf("unsorted!!!\n");
    }
    puts("\n\n");

    Node *head = (Node *)malloc(sizeof(Node)), *before = head, *cur, *tail;
    head->k = rand() % 100, head->next = NULL, head->prev = NULL;
    for (i = 0; i < 20; i++) {
        cur = (Node *)malloc(sizeof(Node));
        cur->k = rand() % 100;
        before->next = cur, cur->prev = before, cur->next = NULL, before = cur;
    }
    tail = cur;

    for (cur = head; cur != NULL; cur = cur->next)
        printf("%d ", cur->k);
    putchar('\n');

    list_quick_sort(head, tail);

    for (cur = head; cur != NULL; cur = cur->next) {
        printf("%d ", cur->k);
        if (cur->next && cur->k > cur->next->k)
            printf("unsorted!!!\n");
    }
    putchar('\n');

    return 0;
}
