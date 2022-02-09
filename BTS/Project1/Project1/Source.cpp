#include<iostream>
#include<vector>
#include<string>

using namespace std;

struct NODE {
	int key;
	NODE* left;
	NODE* right;
};

NODE* Creatnode(int k) {
	NODE* temp = new NODE;
	temp->key = k;
	temp->left = NULL;
	temp->right = NULL;
	return temp;
}

struct List {
	int key;
	List* next;
};

void NLR(NODE* pRoot) // duyet tien thu tu
{ 
	if (pRoot == NULL) return;
	cout  <<pRoot->key<<" ";
	NLR(pRoot->left);
	NLR(pRoot->right);
}

void LNR(NODE* pRoot) // duyet trung thu tu
{
	if (pRoot == NULL) return;
	LNR(pRoot->left);
	cout << pRoot->key << " ";
	LNR(pRoot->right);
}

void LRN(NODE* pRoot) // duyet hau thu tu
{
	if (pRoot == NULL) return;
	LRN(pRoot->left);
	LRN(pRoot->right);
	cout << pRoot->key << " ";
}

//void test() {
//	vector<int> a;
//	for (int i = 0; i < 5; i++) {
//		a.push_back(i);
//	}
//
//	a.erase(a.begin() + 1);
//	a.push_back(10);
//	for (int i = 0; i < a.size(); i++) {
//		cout << a[i];
//	}
//}


void LeverOrder(NODE* pRoot) { // duyet theo muc
	NODE* cur;
	vector<NODE*> temp;
	temp.push_back(pRoot);
	while (temp.size()) {
		cur = temp[0];
		temp.erase(temp.begin());
		cout << cur->key << " ";
		if (cur->left != NULL) temp.push_back(cur->left);
		if (cur->right != NULL) temp.push_back(cur->right);
	}
}

NODE* Search(NODE* pRoot, int x) { // tim kiem node co gia tri bang gia tri cho truoc
	if (pRoot == NULL) return NULL;
	if (pRoot->key == x) return pRoot;
	if (x > pRoot->key) Search(pRoot->right, x);
	else Search(pRoot->left, x);
}

void Insert(NODE*& pRoot, int x) { // them node vao cay nhi phan

	if (pRoot == NULL) {
		NODE* temp = Creatnode(x);
		pRoot = temp;
		return;
	}
	if (x > pRoot->key) return Insert(pRoot->right, x);
	else return Insert(pRoot->left, x);
}

NODE* leftmost_of_right(NODE* pRoot) { // tim gia tri hau to cua root
	if (pRoot == NULL) return NULL;
	NODE* temp = pRoot;
	while (temp->left != NULL) {
		temp = temp->left;
	}
	return temp;
}

void remove(NODE*& pRoot, int x) {  // xoa node
	if (pRoot == NULL) return;
	if (x < pRoot->key) remove(pRoot->left, x);
	else if (x > pRoot->key) remove(pRoot->right, x);
	else {
		NODE* cur = pRoot;
		/*if (pRoot->left == NULL && pRoot->right == NULL) {
			delete cur;
			return;
		}*/
		if (pRoot->left == NULL) {
			pRoot = pRoot->right;
			delete cur;
			return;
		}
		else if (pRoot->right == NULL) {
			pRoot = pRoot->left;
			delete cur;
			return;
		}
		else {
			NODE* temp = leftmost_of_right(pRoot->right);
			cur->key = temp->key;
			remove(cur->right, temp->key);
		}

	}
}

NODE* createTree(int a[], int n) {
	NODE* temp=NULL;
	for (int i = 0; i < n; i++) {
		Insert(temp, a[i]);
	}
	return temp;
}

void removeTree(NODE*& pRoot) {
	if (pRoot == NULL) return;
	removeTree(pRoot->left);
	removeTree(pRoot->right);
	delete pRoot;
	pRoot = NULL;

}

int Height(NODE* pRoot) {
	if (pRoot == NULL) return 0;
	return 1 + max(Height(pRoot->left), Height(pRoot->right));
}

int heightNode(NODE* pRoot, int x) {
	NODE* temp = Search(pRoot, x);
	if (temp == NULL) return -1;
	return Height(temp);
}

int Level(NODE* pRoot, NODE* p) {
	return Height(pRoot) - Height(p);
}

bool isleaf(NODE* pRoot) {
	if (pRoot->left == NULL && pRoot->right == NULL) return true;
	return false;
}

int coutLeaf(NODE* pRoot) {
	if (pRoot == NULL) return 0;
	if (isleaf(pRoot)) return 1;
	return coutLeaf(pRoot->left) + coutLeaf(pRoot->right);
}

bool isBST(NODE* pRoot) {
	if (pRoot== NULL) return true;
	if (pRoot->right != NULL && pRoot->right->key < pRoot->key) return false;
	if (pRoot->left != NULL && pRoot->left->key > pRoot->key) return false;
	if (!isBST(pRoot->left) || !isBST(pRoot->right)) return false;
	return true;
}

bool isFullBST(NODE* pRoot) {
	if (isBST(pRoot)) return true;
	else return false;
}

int minway(NODE* pRoot, int x) {
	if (pRoot == NULL) return 0;
	if (pRoot->key == x) return 1;
	if (pRoot->key > x) return 1 + minway(pRoot->left, x);
	else return 1+ minway(pRoot->right, x);
}

// tim duong di ngan nhat giua x va y 
int minwaybw(NODE* pRoot, int x, int y) {
	if (pRoot == NULL) return 0;
	if (pRoot->key < x && pRoot->key < y) return minwaybw(pRoot->right, x, y);
	else if (pRoot->key > x && pRoot->key > y) return minwaybw(pRoot->left, x, y);
	else return minway(pRoot, x) + minway(pRoot, y) - 1;
}

int main() {
	int a[9] = { 25,15,50,10,22,33,85,21,20};
	NODE* pRoot = createTree(a,9);
	LNR(pRoot);
	//remove(pRoot, 50);
	cout << endl;
	// LNR(pRoot);
	cout << heightNode(pRoot, 15);
	//removeTree(pRoot);
	cout << endl << "........." << Height(pRoot);
	//LNR(pRoot);
}