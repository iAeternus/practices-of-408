#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// 二叉排序树节点
typedef struct _AVLNode {
    int val;
    struct _AVLNode* lch;
    struct _AVLNode* rch;
} AVLNode;

AVLNode* make_node(int val, AVLNode* lch, AVLNode* rch) {
    AVLNode* node = (AVLNode*)malloc(sizeof(AVLNode));
    assert(node != NULL);
    node->val = val;
    node->lch = lch;
    node->rch = rch;
}



// 二叉排序树
typedef struct {
    int siz;
    AVLNode* root;
} AVLTree;

void avl_create(AVLTree* t) {
    t->siz = 0;
    t->root = NULL;
}

static void clear(AVLNode* node) {
    if (!node) return;
    clear(node->lch);
    clear(node->rch);
    free(node);
}

void avl_destroy(AVLTree* t) {
    if (!t) return;
    clear(t->root);
}

AVLNode* avl_find(const AVLTree* t, int val) {
    if (!t) return NULL;
    AVLNode* p = t->root;
    while (p) {
        if (val < p->val) {
            p = p->lch;
        } else if (val > p->val) {
            p = p->rch;
        } else {
            return p;
        }
    }
    return NULL;
}

