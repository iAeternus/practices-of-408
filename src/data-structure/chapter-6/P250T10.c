/**
 * @brief P250 T10
 */

// 链路
typedef struct {
    unsigned id;
    unsigned ip;
} Link;

// 网络
typedef struct {
    unsigned prefix;
    unsigned mask; // 子网掩码
} Net;

// 链表节点
typedef struct _LinkNode {
    short flag; // 1-Link 2-Net
    union {
        Link link;
        Net net;
    } link_or_net;
    unsigned metric;
    _LinkNode* next;
} LinkNode;

// 表头结点
typedef struct _HNode {
    unsigned router_id;
    LinkNode* adj; // 邻接链表
    _HNode* next;
} HNode;
