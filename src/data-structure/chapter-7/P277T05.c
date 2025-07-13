/**
 * @brief 各节点检索概率不等时，顺序查找target，若找到将target与其前驱交换，使经常被检索的元素尽量位于表的前端
 * @see P277 T05
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

/**
 * @brief 顺序实现
 */
typedef struct {
    int cap;
    int siz;
    int* ptr;
} ArrayList;

void print_array(const ArrayList* arr) {
    for (int i = 0; i < arr->siz; ++i) {
        printf("%d ", arr->ptr[i]);
    }
    putchar('\n');
}

void array_elem_swap(int* a, int* b) {
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

int array_search_and_swap(ArrayList* arr, int target) {
    for (int i = 0; i < arr->siz; ++i) {
        if (arr->ptr[i] == target) {
            if (i > 0 && i < arr->siz) array_elem_swap(&arr->ptr[i - 1], &arr->ptr[i]);
            return i;
        }
    }
    return arr->siz;
}

void test_array() {
    int data[] = {1, 2, 3, 4, 5};
    ArrayList arr;
    arr.cap = arr.siz = 5;
    arr.ptr = data;

    print_array(&arr); // 1 2 3 4 5

    // 查找中间元素 (3)
    int idx = array_search_and_swap(&arr, 3);
    assert(idx == 2);
    assert(arr.ptr[1] == 3 && arr.ptr[2] == 2);
    print_array(&arr); // 1 3 2 4 5

    // 查找首元素 (1)
    idx = array_search_and_swap(&arr, 1);
    assert(idx == 0);
    assert(arr.ptr[0] == 1); // 不应交换
    print_array(&arr); // 1 3 2 4 5

    // 查找不存在的元素
    idx = array_search_and_swap(&arr, 99);
    assert(idx == 5);
    print_array(&arr); // 1 3 2 4 5
}

/**
 * @brief 链式实现
 */
typedef struct _LinkNode {
    int val;
    struct _LinkNode* nex;
} LinkNode;

LinkNode* make_node(int val, LinkNode* next) {
    LinkNode* node = (LinkNode*)malloc(sizeof(LinkNode));
    node->val = val;
    node->nex = next;
    return node;
}

// 带头结点的单链表
typedef struct {
    int siz;
    LinkNode* head;
} LinkList;

void print_list(const LinkList* list) {
    for (LinkNode* p = list->head->nex; p; p = p->nex) {
        printf("%d ", p->val);
    }
    putchar('\n');
}

// 交换 node->nex 和 node->nex->nex
void link_list_elem_swap(LinkNode* node) {
    LinkNode *a = node->nex, *b = node->nex->nex;
    LinkNode* p = b->nex;

    b->nex = a;
    a->nex = p;
    node->nex = b;
}

LinkNode* link_list_search_and_swap(LinkList* list, int target) {
    if (list->head->nex && list->head->nex->val == target) {
        return list->head->nex;
    }

    for (LinkNode* p = list->head; p && p->nex && p->nex->nex; p = p->nex) {
        if (p->nex->nex->val == target) {
            link_list_elem_swap(p);
            return p->nex;
        }
    }
    return NULL;
}

void test_linked_list() {
    // 构建链表: head->1->2->3->4
    LinkList list;
    list.head = make_node(-1, NULL);
    list.head->nex = make_node(1, make_node(2, make_node(3, make_node(4, NULL))));

    print_list(&list); // 1 2 3 4

    // 查找第2个元素 (2)
    LinkNode* node = link_list_search_and_swap(&list, 2);
    assert(node != NULL);
    assert(node->val == 2);
    assert(list.head->nex->val == 2); // 应交换到首位
    assert(list.head->nex->nex->val == 1);
    print_list(&list); // 2 1 3 4

    // 查找新首元素 (2)
    node = link_list_search_and_swap(&list, 2);
    assert(node->val == 2);
    assert(list.head->nex->val == 2); // 保持原位
    print_list(&list); // 2 1 3 4

    // 清理内存
    LinkNode* curr = list.head;
    while (curr) {
        LinkNode* temp = curr;
        curr = curr->nex;
        free(temp);
    }
}

int main() {
    test_array();
    test_linked_list();
}