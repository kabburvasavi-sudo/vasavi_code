#include <bits/stdc++.h>
using namespace std;

// Lavender color
#define LAVENDER "\033[95m"
#define RESET    "\033[0m"

/*----------------------------------------------------
    AVL TREE FOR APPLICATIONS (income + family size)
-----------------------------------------------------*/
struct AppNode {
    int income, familySize;
    int height;
    AppNode *left, *right;

    AppNode(int i, int f) {
        income = i;
        familySize = f;
        height = 1;
        left = right = nullptr;
    }
};

int height(AppNode* n) { return n ? n->height : 0; }

int getBalance(AppNode* n) {
    return n ? height(n->left) - height(n->right) : 0;
}

AppNode* rightRotate(AppNode* y) {
    AppNode* x = y->left;
    AppNode* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));

    return x;
}

AppNode* leftRotate(AppNode* x) {
    AppNode* y = x->right;
    AppNode* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));

    return y;
}

AppNode* insertApp(AppNode* node, int income, int familySize) {
    if (!node) return new AppNode(income, familySize);

    if (income < node->income)
        node->left = insertApp(node->left, income, familySize);
    else
        node->right = insertApp(node->right, income, familySize);

    node->height = 1 + max(height(node->left), height(node->right));

    int balance = getBalance(node);

    // Balancing
    if (balance > 1 && income < node->left->income)
        return rightRotate(node);

    if (balance < -1 && income > node->right->income)
        return leftRotate(node);

    if (balance > 1 && income > node->left->income) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    if (balance < -1 && income < node->right->income) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    return node;
}

/*----------------------------------------------------
       SEGMENT TREE FOR HOUSING BLOCKS
-----------------------------------------------------*/

struct SegmentTree {
    vector<vector<int>> tree;   // stores sorted budgets
    int n;

    SegmentTree(int size) {
        n = size;
        tree.resize(4 * size);
    }

    void build(vector<int>& arr, int idx, int l, int r) {
        if (l == r) {
            tree[idx] = {arr[l]};
            return;
        }

        int mid = (l + r) / 2;
        build(arr, idx*2, l, mid);
        build(arr, idx*2+1, mid+1, r);

        // merge sorted lists
        merge(tree[idx*2].begin(), tree[idx*2].end(),
              tree[idx*2+1].begin(), tree[idx*2+1].end(),
              back_inserter(tree[idx]));
    }

    // Query count of budgets within range
    int query(int idx, int l, int r, int ql, int qr, int bl, int br) {
        if (qr < l || ql > r) return 0;  // completely outside
        if (ql <= l && r <= qr) {        // completely inside
            return upper_bound(tree[idx].begin(), tree[idx].end(), br) -
                   lower_bound(tree[idx].begin(), tree[idx].end(), bl);
        }

        int mid = (l + r) / 2;
        return query(idx*2, l, mid, ql, qr, bl, br) +
               query(idx*2+1, mid+1, r, ql, qr, bl, br);
    }
};

/*----------------------------------------------------
                   MAIN PROGRAM
-----------------------------------------------------*/

int main() {
    cout << LAVENDER << "Smart Housing Allocation System\n" << RESET;

    // AVL tree example insertion
    AppNode* root = nullptr;
    root = insertApp(root, 25000, 4);
    root = insertApp(root, 18000, 3);
    root = insertApp(root, 32000, 5);

    // Housing budgets (zone indexed)
    vector<int> budget = {0, 12000, 14000, 16000, 11000, 15000};
    int n = 5;

    SegmentTree st(n);
    st.build(budget, 1, 1, n);

    // Query example
    int zoneL = 2, zoneR = 5;
    int budgetL = 10000, budgetR = 15000;

    int available = st.query(1, 1, n, zoneL, zoneR, budgetL, budgetR);

    cout << LAVENDER 
         << "Available houses in zone " << zoneL << "-" << zoneR
         << " with budget " << budgetL << "-" << budgetR
         << ": " << available << "\n"
         << RESET;

    return 0;
}
