#include <bits/stdc++.h>
using namespace std;

/* =============================
         AVL TREE
   ============================= */
struct Node {
    int key;
    Node *left, *right;
    int height;

    Node(int k) {
        key = k;
        left = right = NULL;
        height = 1;
    }
};
int h(Node *n) {
    return n ? n->height : 0;
}
int bf(Node *n) {
    return n ? h(n->left) - h(n->right) : 0;
}
Node* rotateRight(Node *y) {
    Node *x = y->left;
    Node *T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(h(y->left), h(y->right)) + 1;
    x->height = max(h(x->left), h(x->right)) + 1;
    return x;
}
Node* rotateLeft(Node *x) {
    Node *y = x->right;
    Node *T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(h(x->left), h(x->right)) + 1;
    y->height = max(h(y->left), h(y->right)) + 1;
    return y;
}
Node* insertAVL(Node* root, int key) {
    if(!root) return new Node(key);
    if(key < root->key)
        root->left = insertAVL(root->left, key);
    else
        root->right = insertAVL(root->right, key);
    root->height = max(h(root->left), h(root->right)) + 1;
    int balance = bf(root);
    // Left Left
    if(balance > 1 && key < root->left->key)
        return rotateRight(root);
    // Right Right
    if(balance < -1 && key > root->right->key)
        return rotateLeft(root);
    // Left Right
    if(balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }
    // Right Left
    if(balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }
    return root;
}
void inorder(Node* root) {
    if(!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}
/* =============================
       SEGMENT TREE
   ============================= */
struct SegmentTree {
    vector<int> tree;
    int n;
    void build(vector<int>& arr) {
        n = arr.size();
        tree.assign(4*n,0);
        buildUtil(arr,1,0,n-1);
    }
     void buildUtil(vector<int>& arr,int node,int l,int r){
        if(l==r){ tree[node]=arr[l]; return; }
        int mid=(l+r)/2;

        buildUtil(arr,node*2,l,mid);
        buildUtil(arr,node*2+1,mid+1,r);

        tree[node]=tree[node*2]+tree[node*2+1];
    }
    int query(int l,int r){ return queryUtil(1,0,n-1,l,r); }
    int queryUtil(int node,int start,int end,int l,int r){
        if(r<start || end<l) return 0;
        if(l<=start && end<=r) return tree[node];
        int mid=(start+end)/2;
        return queryUtil(node*2,start,mid,l,r)
             + queryUtil(node*2+1,mid+1,end,l,r);
    }
};
/* =============================
     HOUSING ALLOCATION
   ============================= */
void allocateUnit(int application, int available){
    cout << "Application " << application 
         << " allocated to housing unit #" 
         << available << "\n";
}
/* =============================
           MAIN
   ============================= */
int main() {
    // --- AVL Tree Example ---
    Node* appTree = NULL;
    vector<int> applications = {45000, 30000, 60000, 25000};
    for(int x : applications)
        appTree = insertAVL(appTree, x);
     cout << "Stored Applications (AVL Inorder): ";
    inorder(appTree);
    cout << "\n\n";
// --- Segment Tree Example ---
    SegmentTree housing;
    vector<int> blocks = {5,3,8,2,6,4};   // number of units in each zone
    housing.build(blocks);
     int zoneL = 1, zoneR = 4;
    int available = housing.query(zoneL, zoneR);
cout << "Available units in zone range: " << available << "\n";
// --- Allocation ---
    int application = 45000;
    if(available > 0)
        allocateUnit(application, available);
    cout << "\nHousing allocated successfully!\n";
    return 0;
}
