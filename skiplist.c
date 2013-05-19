#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define ZSKIPLIST_MAXLEVEL 32 /* Should be enough for 2^32 elements */
#define ZSKIPLIST_P 0.25      /* Skiplist P = 1/4 */

typedef struct zskiplistNode {
    double score;
    struct zskiplistNode *backward;
    struct zskiplistLevel {
        struct zskiplistNode *forward;
        unsigned int span;
    } level[];
} zskiplistNode;

typedef struct zskiplist {
    struct zskiplistNode *header, *tail;
    unsigned long length;
    int level;
} zskiplist;

zskiplistNode *zslCreateNode(int level, double score) {
    zskiplistNode *zn = malloc(sizeof(*zn) + level *
            sizeof(struct zskiplistLevel));
    zn->score = score;
    return zn;
}

zskiplist *zslCreate(void) {
    int j;
    zskiplist *zsl;

    zsl = malloc(sizeof(*zsl));
    zsl->level = 1;
    zsl->length = 0;
    zsl->header = zslCreateNode(ZSKIPLIST_MAXLEVEL, 0);
    for (j = 0; j < ZSKIPLIST_MAXLEVEL; j++) {
        zsl->header->level[j].forward = NULL;
        zsl->header->level[j].span = 0;
    }
    zsl->header->backward = NULL;
    zsl->tail = NULL;
    return zsl;
}

void zslFreeNode(zskiplistNode *node) {
    free(node);
}

void zslFree(zskiplist *zsl) {
    zskiplistNode *node = zsl->header->level[0].forward, *next;

    free(zsl->header);
    while(node) {
        next = node->level[0].forward;
        zslFreeNode(node);
        node = next;
    }
    free(zsl);
}

int zslRandomLevel(void) {
    int level = 1;
    while ((rand() & 0xFFFF) < (ZSKIPLIST_P * 0xFFFF))
        level += 1;
    return (level < ZSKIPLIST_MAXLEVEL) ? level : ZSKIPLIST_MAXLEVEL;
}

zskiplistNode *zslInsert(zskiplist *zsl, double score) {
    zskiplistNode *update[ZSKIPLIST_MAXLEVEL], *x;
    unsigned int rank[ZSKIPLIST_MAXLEVEL];
    int i, level;

    x = zsl->header;
    for (i = zsl->level-1; i >= 0; i--) {
        /* store rank that is crossed to reach the insert position */
        rank[i] = i == (zsl->level-1) ? 0 : rank[i+1];
        while (x->level[i].forward &&
                (x->level[i].forward->score < score)) {
                 /*|| (x->level[i].forward->score == score &&
                  compareStringObjects(x->level[i].forward->obj,obj) < 0))) { */
            rank[i] += x->level[i].span;
            x = x->level[i].forward;
        }
        update[i] = x;
    }

    /* we assume the key is not already inside, since we allow duplicated
     * scores, and the re-insertion of score and redis object should never
     * happpen since the caller of zslInsert() should test in the hash table
     * if the element is already inside or not. */
    level = zslRandomLevel();
    if (level > zsl->level) {
        for (i = zsl->level; i < level; i++) {
            rank[i] = 0;
            update[i] = zsl->header;
            update[i]->level[i].span = zsl->length;
        }
        zsl->level = level;
    }
    x = zslCreateNode(level, score);
    for (i = 0; i < level; i++) {
        x->level[i].forward = update[i]->level[i].forward;
        update[i]->level[i].forward = x;

        /* update span covered by update[i] as x is inserted here */
        x->level[i].span = update[i]->level[i].span - (rank[0] - rank[i]);
        update[i]->level[i].span = (rank[0] - rank[i]) + 1;
    }

    /* increment span for untouched levels */
    for (i = level; i < zsl->level; i++) {
        update[i]->level[i].span++;
    }

    x->backward = (update[0] == zsl->header) ? NULL : update[0];
    if (x->level[0].forward)
        x->level[0].forward->backward = x;
    else
        zsl->tail = x;
    zsl->length++;
    return x;
}

int zslFind(zskiplist *zsl, double score) {
    zskiplistNode *x;
    int i;

    x = zsl->header;
    for (i = zsl->level-1; i >= 0; i--) {
        while (x->level[i].forward && x->level[i].forward->score < score) {
            x = x->level[i].forward;
        }
    }
    x = x->level[0].forward;

    return (x && x->score == score) ? 1 : 0;
}

int main(int argc, char *argv[]) {
    srand(time(NULL));

    zskiplist *list = zslCreate();

    int i, score;
    for (i = 0; i < 10; i++) {
        score = rand() % 20;
        printf("insert score %d.\n", score);
        zslInsert(list, score);
    }

    for (i = 0; i < 10; i++) {
        score = rand() % 20;
        if (zslFind(list, score)) {
            printf("find score %d.\n", score);
        } else {
            printf("score %d not in list!\n", score);
        }
    }

    return 0;
}

