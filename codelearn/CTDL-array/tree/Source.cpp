#include<iostream>

using namespace std;

struct NODE {
    int key;
    NODE* left;
    NODE* right;
};

bool isleaf(NODE* root) {

}

void LNR(NODE* root) {
    if (root == NULL) return;
   LNR(root->left);
    cout << root->key << " ";
   LNR(root->right);
}

void Addnode(NODE*& root, int x) {
    if (root == NULL) {
        root = new NODE();
        root->key = x;
        root->left = NULL;
        root->right = NULL;
        return;
    }
    if (root->key < x) Addnode(root->right, x);
    if (root->key >= x) Addnode(root->left, x);

}


int main() {
    NODE* root = NULL;
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        Addnode(root, x);
    }
    LNR(root);
}