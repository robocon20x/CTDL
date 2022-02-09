#include<iostream>
using namespace std;

// bai 1 

int recursiveBinarySearch(int* a, int left, int right, int key) {
	int mid = (left + right) / 2;
	if (a[mid] == key) {
		return mid;
	}
	if (a[mid] > key) {
		return recursiveBinarySearch(a, left, mid - 1, key);
	}
	else if (a[mid] < key) {
		return recursiveBinarySearch(a, mid + 1, right, key);
	}

}

//bai 2 
int calSumDigits(int N) {
	if (N < 10) return N;
	return (N % 10) + calSumDigits(N / 10);
}

// bai 3
// 4566789  so lon nhat la 789
int max(int a, int b) {
	if (a > b) return a;
	return b;
}
int findMax3Digits(int N) {
	if (N < 1000)return N;
	return max((N % 1000), findMax3Digits(N / 10));

}

int main() {
	int N = 123456;
	int a[6] = { 1,4,6,6,3,2 };
	cout << recursiveBinarySearch(a, 0, 6, 6) << endl;

	cout << calSumDigits(N) << endl;
	cout << findMax3Digits(N) << endl;
}