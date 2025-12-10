#include <iostream>
using namespace std;

/* ======================================================
                 SIMPLE AVL TREE
====================================================== */
struct Node {
    int income;
    int familySize;
    Node *left, *right;
    int height;
};

int height(Node* n) {
    if (n == NULL) return 0;
    return n->height;
}

Node* newNode(int income, int familySize) {
    Node* n = new Node;
    n->income = income;
    n->familySize = familySize;
    n->left = n->right = NULL;
    n->height = 1;
    return n;
}

int getBalance(Node* n) {
    if (n == NULL) return 0;
    return height(n->left) - height(n->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    y->left = x->right;
    x->right = y;

    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));
    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));

    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    x->right = y->left;
    y->left = x;

    x->height = 1 + (height(x->left) > height(x->right) ? height(x->left) : height(x->right));
    y->height = 1 + (height(y->left) > height(y->right) ? height(y->left) : height(y->right));

    return y;
}

Node* insert(Node* node, int income, int familySize) {
    if (node == NULL)
        return newNode(income, familySize);

    if (income < node->income)
        node->left = insert(node->left, income, familySize);
    else
        node->right = insert(node->right, income, familySize);

    node->height = 1 + (height(node->left) > height(node->right) ?
                        height(node->left) : height(node->right));

    int balance = getBalance(node);

    // LL
    if (balance > 1 && income < node->left->income)
        return rightRotate(node);

    // RR
    if (balance < -1 && income > node->right->income)
        return leftRotate(node);

    // LR
    if (balance > 1 && income > node->left->income) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // RL
    if (balance < -1 && income < node->right->income) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}


/* ======================================================
                 SIMPLE SEGMENT TREE
====================================================== */

int seg[400];
int blocks[100];
int N;

// Build: store budgets zone-wise
void build(int idx, int l, int r) {
    if (l == r) {
        seg[idx] = blocks[l];
        return;
    }

    int mid = (l + r) / 2;
    build(idx*2, l, mid);
    build(idx*2+1, mid+1, r);

    seg[idx] = seg[idx*2] + seg[idx*2+1];   // total available houses
}

int query(int idx, int l, int r, int ql, int qr) {
    if (qr < l || ql > r) return 0;

    if (ql <= l && r <= qr) return seg[idx];

    int mid = (l + r) / 2;

    int left = query(idx*2, l, mid, ql, qr);
    int right = query(idx*2+1, mid+1, r, ql, qr);

    return left + right;
}


/* ======================================================
                       MAIN
====================================================== */
int main() {
    Node* appTree = NULL;

    cout << "Inserting Housing Applications (income, familySize):\n";

    appTree = insert(appTree, 30000, 4);
    appTree = insert(appTree, 18000, 3);
    appTree = insert(appTree, 45000, 5);
    appTree = insert(appTree, 25000, 2);

    cout << "\nApplications Inserted Successfully!\n";

    // Segment Tree Example
    N = 7;
    int temp[7] = {10000, 12000, 15000, 18000, 13000, 16000, 20000};

    for (int i = 0; i < N; i++)
        blocks[i] = temp[i];

    build(1, 0, N-1);

    int zoneL = 2;
    int zoneR = 5;

    cout << "\nQuerying housing budget from zone " << zoneL
         << " to " << zoneR << endl;

    int result = query(1, 0, N-1, zoneL, zoneR);

    cout << "Total available housing budget in range = " << result << endl;

    return 0;
}
