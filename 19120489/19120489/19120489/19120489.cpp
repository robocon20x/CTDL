#include<iostream>
#include<string>
#include<vector>
#include<fstream>

using namespace std;

struct NODE {
	string data;
	NODE* left;
	NODE* right;
};

void LRN(NODE* root, vector<string>& str) {

	if (root == NULL) return;


	LRN(root->left, str);
	LRN(root->right, str);
	str.push_back(root->data);

}

void LeverOrder(NODE* pRoot,vector<string> str) { // duyet theo muc
	NODE* cur;
	vector<NODE*> temp;
	temp.push_back(pRoot);
	while (temp.size()) {
		cur = temp[0];
		temp.erase(temp.begin());
		str.push_back(cur->data);
		if (cur->left != NULL) temp.push_back(cur->left);
		if (cur->right != NULL) temp.push_back(cur->right);
	}
}

void Insert(NODE*& root, string str) {
	if (root == NULL) {

		NODE* temp = new NODE;
		temp->data = str;
		temp->left = NULL;
		temp->right = NULL;
		root = temp;
		return;

	}
	if (str > root->data) Insert(root->right, str);
	else Insert(root->left, str);
}

vector<string> List() {
	vector<string> temp;
	ifstream f("name.txt");
	if (f.fail()) {
		cout << "khong mo duoc file\n";
		return temp;
	}
	while (!f.eof()) {
		string t;
		f >> t;
		temp.push_back(t);
	}
	return temp;
}

NODE* creatTree(vector<string> str) {
	NODE* temp = NULL;
	for (int i = 0; i < str.size(); i++) {
		Insert(temp, str[i]);
	}
	return temp;
}

bool find(NODE* root, string str) {
	if (root == NULL) return false;
	if (root->data == str) return true;
	if (str > root->data) return find(root->right, str);
	else return find(root->left, str);
}

NODE* leftmost_of_right(NODE* root) { 
	if (root == NULL) return NULL;
	NODE* temp = root;
	while (temp->left != NULL) {
		temp = temp->left;
	}
	return temp;
}

void remove(NODE*& root, string str) {
	if (root == NULL) return;
	if (str < root->data) remove(root->left, str);
	else if (str > root->data) remove(root->right, str);
	else {
		NODE* cur = root;
		/*if (root->left == NULL && root->right == NULL) {
			delete cur;
			return;
		}*/
		if (root->left == NULL) {
			root = root->right;
			delete cur;
			return;
		}
		else if (root->right == NULL) {
			root = root->left;
			delete cur;
			return;
		}
		else {
			NODE* temp = leftmost_of_right(root->right);
			cur->data = temp->data;
			remove(cur->right, temp->data);
		}

	}
}

void removeTree(NODE*& root) {
	if (root == NULL) return;
	removeTree(root->left);
	removeTree(root->right);
	delete root;
	root = NULL;

}

int khoangcachdenroot(struct NODE* root, string x)
{
	if (root->data == x)
		return 1;
	else if (root->data > x)
		return 1 + khoangcachdenroot(root->left, x);
	else return 1 + khoangcachdenroot(root->right, x);
}
int khoangcachngannhat(struct NODE* root, string a, string b)
{
	if (root==NULL)	return 0;

	if (root->data > a && root->data > b)
		return khoangcachngannhat(root->left, a, b);

	if (root->data < a && root->data < b) 
		return khoangcachngannhat(root->right, a, b);

	if (root->data >= a && root->data <= b)
		return khoangcachdenroot(root, a) +
		khoangcachdenroot(root, b)- 1;
}


int main() {
	// cau 1
	vector<string> str = List();
	NODE* root = creatTree(str);

	// cau 2
	string name1, name2;
	cout << "\n Nhap ten nguoi thu nhat: "; cin >> name1;
	cout << "\n Nhap ten nguoi thu hai: "; cin >> name2;

	if (find(root, name1) == true && find(root, name2) == true) {
		cout << "\n khoang cach la: " << khoangcachngannhat(root,name1, name2);
	}
	else {
		cout << " \nTen nhap vao bi sai";
	}

	// cau 3
	ifstream fi("input.txt");
	ofstream fout("output_ex3.txt");
	while (!fi.eof()) {
		string t;
		fi >> t;
		remove(root, t);
	}
	vector<string> ketqua;
	LRN(root, ketqua);
	for (int i = 0; i < ketqua.size(); i++) {
		fout << ketqua[i] << " ";
	}
	fi.close();
	fout.close();
	// cau 4: xoa cay
	removeTree(root);
}