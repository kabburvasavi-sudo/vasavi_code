#include <iostream>
#include <algorithm>

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
    if (!root) return new Node(key);

    if (key < root->key)
        root->left = insertAVL(root->left, key);
    else
        root->right = insertAVL(root->right, key);

    root->height = max(h(root->left), h(root->right)) + 1;
    int balance = bf(root);

    // Balancing cases
    if (balance > 1 && key < root->left->key)
        return rotateRight(root);

    if (balance < -1 && key > root->right->key)
        return rotateLeft(root);

    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}

void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->key << " ";
    inorder(root->right);
}

/* =============================
       SEGMENT TREE (ARRAY)
   ============================= */
struct SegmentTree {
    int tree[100];
    int n;

    void build(int arr[], int size) {
        n = size;
        buildUtil(arr, 1, 0, n - 1);
    }

    void buildUtil(int arr[], int node, int l, int r) {
        if (l == r) {
            tree[node] = arr[l];
            return;
        }
        int mid = (l + r) / 2;
        buildUtil(arr, node * 2, l, mid);
        buildUtil(arr, node * 2 + 1, mid + 1, r);
        tree[node] = tree[node * 2] + tree[node * 2 + 1];
    }

    int query(int l, int r) {
        return queryUtil(1, 0, n - 1, l, r);
    }

    int queryUtil(int node, int start, int end, int l, int r) {
        if (r < start || end < l) return 0;
        if (l <= start && end <= r) return tree[node];
        int mid = (start + end) / 2;
        return queryUtil(node * 2, start, mid, l, r)
             + queryUtil(node * 2 + 1, mid + 1, end, l, r);
    }
};

/* =============================
     HOUSING ALLOCATION
   ============================= */
void allocateUnit(int application, int available) {
    cout << "Application " << application
         << " allocated. Units available: "
         << available << endl;
}

/* =============================
           MAIN
   ============================= */
int main() {

    // AVL Tree: Applications
    Node* appTree = NULL;
    int applications[4] = {45000, 30000, 60000, 25000};

    for (int i = 0; i < 4; i++)
        appTree = insertAVL(appTree, applications[i]);

    cout << "Stored Applications (AVL Inorder): ";
    inorder(appTree);
    cout << "\n\n";

    // Segment Tree: Housing Units
    SegmentTree housing;
    int blocks[6] = {5, 3, 8, 2, 6, 4};
    housing.build(blocks, 6);

    int zoneL = 1, zoneR = 4;
    int available = housing.query(zoneL, zoneR);

    cout << "Available units in zone range: " << available << endl;

    // Allocation
    int application = 45000;
    if (available > 0)
        allocateUnit(application, available);

    cout << "\nHousing allocated successfully!" << endl;
    return 0;
}
