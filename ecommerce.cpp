#include <bits/stdc++.h>
using namespace std;
// ------------------------------
// Merge Sort for Orders
// ------------------------------
void mergeVec(vector<int>& arr, int l, int m, int r) {
    vector<int> left(arr.begin() + l, arr.begin() + m + 1);
    vector<int> right(arr.begin() + m + 1, arr.begin() + r + 1);
  int i = 0, j = 0, k = l;
    while (i < left.size() && j < right.size()) {
        if (left[i] <= right[j]) arr[k++] = left[i++];
        else arr[k++] = right[j++];
    }
    while (i < left.size()) arr[k++] = left[i++];
    while (j < right.size()) arr[k++] = right[j++];
}
void mergeSortUtil(vector<int>& arr, int l, int r) {
    if (l >= r) return;
    int m = (l + r) / 2;
    mergeSortUtil(arr, l, m);
    mergeSortUtil(arr, m + 1, r);
    mergeVec(arr, l, m, r);
}
void mergeSort(vector<int>& arr) {
    if (!arr.empty()) mergeSortUtil(arr, 0, arr.size() - 1);
}
// ------------------------------
// Segment Tree for Inventory
// ------------------------------
struct SegmentTree {
    vector<int> tree;
    int n;

    void build(vector<int>& arr) {
        n = arr.size();
        tree.assign(4 * n, 0);
        buildUtil(arr, 1, 0, n - 1);
    }
  void buildUtil(vector<int>& arr, int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
        } else {
            int mid = (l + r) / 2;
            buildUtil(arr, node * 2, l, mid);
            buildUtil(arr, node * 2 + 1, mid + 1, r);
            tree[node] = tree[node * 2] + tree[node * 2 + 1];
        }
    }
 int query(int L, int R) {
        return queryUtil(1, 0, n - 1, L, R);
    }
 int queryUtil(int node, int l, int r, int L, int R) {
        if (R < l || L > r) return 0;
        if (L <= l && r <= R) return tree[node];
        int mid = (l + r) / 2;
        return queryUtil(node * 2, l, mid, L, R) +
               queryUtil(node * 2 + 1, mid + 1, r, L, R);
    }
};
// ------------------------------
// Graph + Dijkstra
// ------------------------------
vector<vector<pair<int,int>>> buildGraph() {
    int n = 6; // sample nodes
    vector<vector<pair<int,int>>> g(n);
 auto add = [&](int u, int v, int w){
        g[u].push_back({v, w});
        g[v].push_back({u, w});
    };
 // sample routes
    add(0,1,4); add(1,2,3); add(2,3,2);
    add(1,4,7); add(4,5,1); add(3,5,5);
return g;
}
vector<int> dijkstra(vector<vector<pair<int,int>>>& g, int start, int end) {
    int n = g.size();
    vector<int> dist(n, INT_MAX), parent(n, -1);
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<pair<int,int>>> pq;
 dist[start] = 0;
    pq.push({0, start});
while (!pq.empty()) {
        auto [d, u] = pq.top(); pq.pop();
        if (d != dist[u]) continue;
 for (auto& [v, w] : g[u]) {
            if (dist[v] > d + w) {
                dist[v] = d + w;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
 // reconstruct path
    vector<int> path;
    for (int cur = end; cur != -1; cur = parent[cur])
        path.push_back(cur);
reverse(path.begin(), path.end());
    return path;
}
// ------------------------------
// Helper Functions
// ------------------------------
vector<int> loadOrders() {
    return {5, 1, 3, 2, 4}; // sample priorities
}
vector<int> loadInventory() {
    return {3, 2, 5, 0, 4, 1}; // sample stock
}
void dispatchOrder(int orderID, vector<int>& path) {
    cout << "Dispatching order " << orderID << " via route: ";
    for (int x : path) cout << x << " ";
    cout << "\n";
}
// ------------------------------
// Main Program
// ------------------------------
int main() {
 // E-Commerce Order Fulfillment
    vector<int> orders = loadOrders();
    mergeSort(orders);  // sort orders by priority (low = high priority)
 vector<int> stockData = loadInventory();
    SegmentTree inventory;
    inventory.build(stockData);
int zoneL = 1, zoneR = 3;
    int available = inventory.query(zoneL, zoneR);
 vector<vector<pair<int,int>>> cityRoutes = buildGraph();
    int warehouse = 0, customer = 5;
vector<int> shortestPath = dijkstra(cityRoutes, warehouse, customer);
 if (available > 0)
        dispatchOrder(orders[0], shortestPath);
cout << "Order delivered successfully!\n";

    return 0;
}
