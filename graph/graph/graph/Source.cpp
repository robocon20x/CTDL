//#include<iostream>
//#include<vector>
//#include<fstream>
//
//using namespace std;
//
//void input1(vector<int*> &a, int& v) {
//	
//	fstream fin("graph1.txt");
//	if (fin.fail()) {
//		cout << "\n khong mo duoc file\n";
//		return;
//	}
//	fin >> v;
//	for (int i = 0; i < v; i++) {
//		a[i] = new int[v];		
//	}
//	for (int i = 0; i < v; i++) {
//		for (int j = 0; j < v; j++) {
//				fin >> a[i][j];
//		}
//	}
//	fin.close();
//}
//
//void output1(vector<int*> a, int v) {
//	fstream fout("graph1_output.txt");
//	if (fout.fail()) {
//		cout << "\n khong mo duoc file\n";
//		return;
//	}
//	fout << v <<endl;
//	// chuyen doi
//	vector<int> b;
//	for (int i = 0; i < v; i++) {
//		int k = 0;
//		for (int j = 0; j < v; j++)
//			if (a[i][j] == 1) k++;
//		b.push_back(k);
//		for (int j = 0; j < v; j++)
//			if (a[i][j] == 1) b.push_back(j);
//	}
//	// xuat ra file
//	while (b.size() != 0) {
//		int t = b[0];
//		int i = 0;
//		while (i <= t) {
//			fout << b[0];
//			b.erase(b.begin());
//			i++;
//		}
//		fout << endl;
//	}
//
//	fout.close();
//}
//
//void input2(vector<int> &a, int& v) {
//
//	fstream fin("graph2.txt");
//	if (fin.fail()) {
//		cout << "\n khong mo duoc file\n";
//		return;
//	}
//	fin >> v;
//	while (!fin.eof()) {
//		int t;
//		fin >> t;
//		a.push_back(t);
//	}
//	fin.close();
//}
//
//void output2(vector<int> a, int v) {
//	fstream fout("graph2_output.txt");
//	if (fout.fail()) {
//		cout << "\n khong mo duoc file\n";
//		return;
//	}
//	fout << v << endl;
//	// khoi tao mang trung gian b
//	vector<int*>b;
//	for (int i = 0; i < v; i++)
//		b[i] = new int[v];
//	for (int i = 0; i < v; i++) {
//		for (int j = 0; j < v; j++) {
//			b[i][j] = 0;
//		}
//	}
//	int k = 0; // dung de dem so dong
//	while (a.size() != 0) {
//		int temp = a[0];
//		a.erase(a.begin());
//		while (temp > 0) {
//			b[k][a[0]] = 1;
//			a.erase(a.begin());
//			temp--;
//		}
//		k++;
//	}
//
//	// xuat file
//	for (int i = 0; i < v; i++) {
//		for (int j = 0; j < v; j++) {
//			fout << b[i][j] << " ";
//		}
//		fout << endl;
//	}
//
//	fout.close();	
//}
//
//// cau 3
//
//bool isvector(vector<int*>a, int v) {// neu true la do thi co huong
//	for (int i = 0; i < v; i++) {
//		for (int j = 0; j < v; j++) {
//			if (a[i][j] != a[j][i]) return true;
//		}
//	}
//	return false;
//}
//
//int dinh(int v) {
//	return v;
//}
//
//int canh(vector<int*>a, int v) { // truong hop co huong
//	int s = 0;
//	for (int i = 0; i < v; i++) {
//		for (int j = 0; j < v; j++) {
//			s += a[i][j];
//		}
//	}
//	return s;
//}
//
//int canh2(vector<int*>a, int v) {// truong hop vo huong
//	return canh(a, v) / 2;
//}
//
//int bac(vector<int*>a, int v,int dinh) { // vo huong
//	int s = 0;
//	for (int i = 0; i < v; i++) {
//		s += a[dinh][i];
//	}
//	return s;
//}
//
//// bac co huong
//int bactrong(vector<int*>a, int v, int dinh) {
//	int s = 0;
//	for (int i = 0; i < v; i++) {
//		s += a[i][dinh];
//	}
//	return s;
//}
//
//int bacngoai(vector<int*>a, int v, int dinh) {
//	int s = 0;
//	for (int i = 0; i < v; i++) {
//		s += a[dinh][i];
//	}
//	return s;
//}
//
//vector<int> dinhtreo(vector<int*>a, int v) {
//	vector<int> b;
//	for (int i = 0; i < v; i++) {
//		if (bac(a, v, i) == 0) b.push_back(i); // vo huong , tuong tu voi co huong....
//		// 	if (bactrong(a, v, i) == 0&& bacngoai(a,v,i)==0) b.push_back(i);
//	}
//}
//
//bool daydu(vector<int*>a, int v) {
//	for (int i = 0; i < v; i++) {
//		for (int j = 0; j < v; j++) {
//			if (a[i][j] == 0 && i != j) return false;
//		}
//	}
//	return true;
//}
//
//bool vong(vector<int*>a, int v) {
//	for (int i = 0; i < v; i++) {
//		if (bac(a, v, i) != 2) return false;
//	}
//	if (canh2(a, v) != v) return false;
//	return true;
//}
//
//bool haiphia(vector<int*>a, int v) {
//
//
//}


#include<iostream>
#define NODE 5
using namespace std;

int graph[NODE][NODE] = {
   {0, 1, 1, 1, 0},
   {1, 0, 1, 0, 0},
   {1, 1, 0, 0, 0},
   {1, 0, 0, 0, 1},
   {0, 0, 0, 1, 0}
};

bool isCycle(int u, bool visited[], int parent) {
    visited[u] = true;    //mark v as visited
    for (int v = 0; v < NODE; v++) {
        if (graph[u][v]) {
            if (!visited[v]) {     //when the adjacent node v is not visited
                if (isCycle(v, visited, u)) {
                    return true;
                }
            }
            else if (v != parent) {    //when adjacent vertex is visited but not parent
                return true;    //there is a cycle
            }
        }
    }
    return false;
}

bool isTree() {
    bool* vis = new bool[NODE];

    for (int i = 0; i < NODE; i++)
        vis[i] = false;    //initialize as no node is visited

    if (isCycle(0, vis, -1))    //check if there is a cycle or not
        return false;

    for (int i = 0; i < NODE; i++) {
        if (!vis[i])    //if there is a node, not visited by traversal, graph is not connected
            return false;
    }
    return true;
}

int main() {
    if (isTree())
        cout << "The Graph is a Tree.";
    else
        cout << "The Graph is not a Tree.";
}