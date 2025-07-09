#define MAXV 100000

typedef struct {
    int numVertices, numEdges;
    char verticesList[MAXV];
    int edge[MAXV][MAXV];
} MGraph;

int uniquely(MGraph g) {
    int in_deg[MAXV];         // 存储入度
    int queue[MAXV];          // 队列
    int front = 0, rear = -1; // 队首，队尾
    int ans = 1, cnt = 0;     // 是否唯一，已处理的顶点数

    // 初始化入度表
    for (int i = 0; i < g.numEdges; ++i) {
        for (int j = 0; j < g.numEdges; ++j) {
            if (g.edge[i][j]) {
                in_deg[j]++;
            }
        }
    }

    // 初始化队列
    for (int i = 0; i < g.numEdges; ++i) {
        if (in_deg[i] == 0) {
            queue[++rear] = i;
        }
    }

    // 拓扑排序
    while (front <= rear) {
        // 如果当前有多个入度为0的顶点，拓扑序列不唯一
        if (rear - front + 1 > 1) {
            ans = 0;
        }
        int u = queue[front++];
        cnt++;
        for (int v = 0; v < g.numEdges; ++v) {
            if (g.edge[u][v]) {
                in_deg[v]--;
                if (in_deg[v] == 0) {
                    queue[++rear] = v;
                }
            }
        }
    }

    return cnt == g.numEdges && ans;
}

int main() {
}