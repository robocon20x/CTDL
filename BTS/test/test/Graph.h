#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <stack>
#include <queue>
using namespace std;
#define V 5  
struct cap_dinh
{
	int x;
	int y;
};
void ma_tran_ke_sang_ds_ke(string filename); // chuyen tu ma tran ke sang DS ke

void ds_ke_sang_ma_tran_ke(string filename); // chuyen tu DS ke sang ma tran ke 

void ds_canh_sang_ds_ke(string filename); // chua lam xong

void ds_ke_sang_ds_canh(string filename); // chua lam xong

void doc_du_lieu(string filename); // doc du lieu tu file

void DFS(int u); // duyet DFS

void BFS(int u); // duyet BFS

void spanning_tree_BFS(int u); // tim cay khung nho nhat dung BFS

void spanning_tree_DFS(int u); // tim cay khung nho nhat dung DFS

int minKey(int key[], bool mstSet[], int n); // ham phu cua ham spanning_tree_Prim

void print_spanning_tree_Prim(int parent[]);// ham phu cua ham spanning_tree_Prim

void spanning_tree_Prim(); // tim cay khung nho nhat (thuat toan Prim) 

void print_spanning_tree_kruskal(int a[], int b[], int weight[]); // ham phu cua ham spanning_tree_kruskal

int findParent(int node, int parent[]);// ham phu cua ham sspanning_tree_kruskal

void spanning_tree_kruskal();//  tim cay khung nho nhat (thaut toan kruskal)

void kt_su_lk_2_dinh_DFS(int u, int t); // kt 2 dinh co lien ket khong va tim duong di giua 2 dinh (DFS)

void kt_su_lk_2_dinh_BFS(int t, int u);// kt 2 dinh co lien ket khong va tim duong di giua 2 dinh (BFS)