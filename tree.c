#include <stdio.h>

typedef struct Node {
    int data;
    struct Node *left;
    struct Node *right;
} Node;

void postorder_traversal(Node *root) {
    Node *stack[64], *p = root;
    int flag[64], top = -1, f;

    if (root == NULL) {
        return;
    }

    do {
        while (p != NULL) {
            stack[++top] = p;
            flag[top] = 0;
            p = p->left;
        }

        p = stack[top];
        f = flag[top--];
        if (f == 0) {
            stack[++top] = p;
            flag[top] = 1;
            p = p->right;
        } else {
            printf("%d\n", p->data);
            p = NULL;
        }
    } while (top != -1);
}

int main(int argc, char *argv) {
    Node _1, _2, _3, _4, _5, _6, _7;
    _1.data = 1, _2.data = 2, _3.data = 3, _4.data = 4,
    _5.data = 5, _6.data = 6, _7.data = 7;
    _1.left = &_2, _1.right = &_3, _2.left = &_4, _2.right = &_5,
    _3.left = &_6, _3.right = &_7, _4.left = _4.right = _5.left =
    _5.right = _6.left = _6.right = _7.left = _7.right = NULL;

    postorder_traversal(&_1);

    return 0;
}
