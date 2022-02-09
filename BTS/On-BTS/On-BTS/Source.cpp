// cay AVL
#include<iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

struct NODE {
	int key;
	NODE* l;
	NODE* r;
	int h;
};

// Khoi tao node
NODE* creatNode(int data) {
	NODE* p = new NODE();
	p->key = data;
	p->l = NULL;
	p->r = NULL;
	p->h = 1; // do node duoc tao ra chac chan duoc them o la 
	return p;
}

// duyet tien thu tu 

void NLR(NODE* root) {
	if (root == NULL) return;
	cout << root->key << " ";
	NLR(root->l);
	NLR(root->r);
}

// trung thu tu
void LNR(NODE* root) {
	if (root == NULL) return;
	LNR(root->l);
	cout << root->key << "-" << root->h << " ";
	LNR(root->r);
}

// hau thu tu
void LRN(NODE* root) {
	if (root == NULL) return;
	LRN(root->l);
	LRN(root->r);
	cout << root->key << " ";
}

//duyet theo muc
void LevelOrder(NODE* root) {
	if (root == NULL) return;

	NODE* cur;
	vector<NODE*> temp;
	temp.push_back(root);
	while (temp.size() != 0) {
		cur = temp[0];
		cout << temp[0]->key << " ";
		temp.erase(temp.begin());
		if (cur->l != NULL) temp.push_back(cur->l);
		if (cur->r != NULL) temp.push_back(cur->r);
	}	
}

int height(NODE* root) {
	if (root == NULL) return 0;
	return 1 + max(height(root->l), height(root->r));
}

NODE* Search(NODE* root, int x) {
	if (root == NULL) return NULL;
	if (root->key == x) return root;
	if(x > root->key) Search(root->r, x);
	else Search(root->l, x);
}

int heightnode(NODE* root, NODE* p) {
	NODE* temp = Search(root, p->key);
	if (temp == NULL) return -1;
	else return height(temp);
}

// xoay phai
NODE* rightRotate(NODE* root) {
	NODE* temp1 = root->l;
	NODE* temp2 = temp1->r;

	temp1->r = root;
	root->l = temp2;

	temp1->h = height(temp1);
	root->h = height(root);
	return temp1;
}
// xoay trai

NODE* leftRotate(NODE* root) {
	NODE* temp1 = root->r;
	NODE* temp2 = temp1->l;

	temp1->l = root;
	root->r = temp2;

	temp1->h = height(temp1);
	root->h = height(root);

	return temp1;
}
bool isAVL(NODE* root) {
	if (root == NULL) return  true;
	if (abs(height(root->l) - height(root->r)) > 1) return false;
	return true;
}

// lay he so can bang de phan biet truong hop 
int getBalance(NODE* root) {
	if (root == NULL) return 0;
	return height(root->l) - height(root->r);
}

void Insert(NODE* &root, int x) {
	if (root == NULL) {
		root = creatNode(x);
		return;
	}

	if (x > root->key) Insert(root->r, x);
	else if (x < root->key) Insert(root->l, x);
	else return; // neu da co thi khong them vao nua 

	// cap nhat chieu cao cho node vua them vao 
	root->h = height(root);

	// tim he so can bang 
	int balance = getBalance(root);

	// left lefy
	if (balance > 1 && x < root->l->key) {
		root = rightRotate(root);
		return;
	}

	// right right
	if (balance<-1 && x>root->r->key) {
		root = leftRotate(root);
		return;
	}

	// left right
	if (balance > 1 && x > root->l->key) {
		root->l = leftRotate(root->l);
		root = rightRotate(root);
		return;
	}

	// right left
	if (balance < -1 && x < root->r->key) {
		root->r = rightRotate(root->r);
		root = leftRotate(root);
		return;
	}
	return;
}

NODE* leftofright(NODE* root) {
	if (root == NULL) return NULL;
	if (root->l != NULL) leftofright(root->l);
	else return root;
}

NODE* minValueNode(NODE* root) {
	NODE* cur = root;
	while (cur->l != NULL) cur = cur->l;
	return cur;
}
void Remove(NODE* &root, int x) {
	if (root == NULL) return;
	if (x > root->key) Remove(root->r, x);
	else if (x < root->key) Remove(root->l, x);
	else {
		// truong hop khong co node con hoac chi co 1 node con 
		if (root->l == NULL || root->r == NULL) {
			NODE* temp = NULL;
			if (root->l == NULL) temp = root->r;
			else temp = root->l;

			if (temp == NULL) {
				temp = root;
				root = NULL;
			}
			else {
				root->h = temp->h;
				root->key = temp->key;
			}
			free(temp);
		}
		else
		{
			// node co 2 con 
			NODE* temp = minValueNode(root->r);
			root->key = temp->key;

			Remove(root->r, temp->key);
		}
	}
	if (root == NULL) return;

	// buoc 2: cap nhat chieu cao cua node hien tai dang xet 
	root->h = height(root);

	// buoc 3: tim he so can bang 
	
	int balance = getBalance(root);

	// left left
	if (balance > 1 && getBalance(root->l) >= 0) {
		root = rightRotate(root);
		return;
	}
	// left right
	if (balance > 1 && getBalance(root->l) < 0) {
		root->l = leftRotate(root->l);
		root = rightRotate(root);
	}

	 // right right
	if (balance < -1 && getBalance(root->r) <= 0) {
		root = leftRotate(root);
		return;
	}
	// right left
	if (balance < -1 && getBalance(root->r)>0) {
		root->r = rightRotate(root->r);
		root = leftRotate(root);
	}

	return;
		
}

NODE* createTree(int a[], int n) {
	NODE* temp = NULL;
	for (int i = 0; i < n; i++) {
		Insert(temp, a[i]);
	}
	return temp;
}


int main() {
	int a[9] = { 25,15,50,10,22,33,85,21,20 };
	NODE* pRoot = createTree(a, 9);
	LNR(pRoot);
	if (isAVL(pRoot)) cout << "\nTRUE" << endl;
	else cout << "\nFALSE" << endl;
	cout << endl;
	Remove(pRoot, 21);
	LNR(pRoot);
	if (isAVL(pRoot)) cout << "\nTRUE" << endl;
	else cout << "\nFALSE" << endl;
	cout << endl << ".........";

}

