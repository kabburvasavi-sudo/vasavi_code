#include <iostream>
#include <limits>
using namespace std;

// ------------------------- Merge Sort -------------------------
void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;

    int L[100], R[100];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) arr[k++] = L[i++];
        else arr[k++] = R[j++];
    }
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = (l + r) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

// ------------------- Simple Segment Tree (Array Based) -------------------
struct SegmentTree {
    int tree[400];
    int n;

    void build(int arr[], int size) {
        n = size;
        for (int i = 0; i < 4 * n; i++) tree[i] = 0;
        buildUtil(arr, 1, 0, n - 1);
    }

    void buildUtil(int arr[], int node, int start, int end) {
        if (start == end) {
            tree[node] = arr[start];
        } else {
            int mid = (start + end) / 2;
            buildUtil(arr, node * 2, start, mid);
            buildUtil(arr, node * 2 + 1, mid + 1, end);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }
    }

    int query(int l, int r) {
        return queryUtil(1, 0, n - 1, l, r);
    }

    int queryUtil(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return queryUtil(node * 2, start, mid, l, r) +
               queryUtil(node * 2 + 1, mid + 1, end, l, r);
    }
};

// ------------------------- Dijkstra (Array Based) -------------------------
const int INF = 1e9;

void dijkstra(int graph[10][10], int n, int start, int dist[]) {
    bool visited[10] = {false};

    for (int i = 0; i < n; i++) dist[i] = INF;
    dist[start] = 0;

    for (int i = 0; i < n - 1; i++) {
        int u = -1;
        int minDist = INF;

        for (int j = 0; j < n; j++) {
            if (!visited[j] && dist[j] < minDist) {
                minDist = dist[j];
                u = j;
            }
        }

        visited[u] = true;

        for (int v = 0; v < n; v++) {
            if (graph[u][v] != 0 && dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
            }
        }
    }
}

// ----------------------------- Main Program -----------------------------
int main() {

    // ---------------- Orders ----------------
    int orders[5] = {40, 10, 30, 20, 50};
    int orderCount = 5;

    mergeSort(orders, 0, orderCount - 1);

    // ------------- Inventory (Segment Tree) -------------
    int stockData[6] = {5, 3, 2, 4, 6, 1};
    SegmentTree st;
    st.build(stockData, 6);

    int zoneL = 1, zoneR = 4;
    int available = st.query(zoneL, zoneR);

    // ------------------- City Routes --------------------
    int n = 5;
    int graph[10][10] = {
        {0, 2, 0, 6, 0},
        {2, 0, 3, 0, 0},
        {0, 3, 0, 1, 5},
        {6, 0, 1, 0, 2},
        {0, 0, 5, 2, 0}
    };

    int dist[10];
    dijkstra(graph, n, 0, dist); // warehouse = 0

    int customer = 4;

    if (available > 0) {
        cout << "Order Dispatched: " << orders[0] << endl;
        cout << "Shortest Path Distance to Customer: " << dist[customer] << endl;
        cout << "Order Delivered Successfully!\n";
    } else {
        cout << "Order Cannot be Dispatched – Out of Stock\n";
    }

    return 0;
}
