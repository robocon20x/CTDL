#include<iostream>
#include<random>
#include<functional>
#include<string>
using namespace std;

int main() {
	/*int a[100];
	int n = 10;

	default_random_engine generator;
	uniform_int_distribution<int> distribution(10, 100);

	auto roll = std::bind(distribution, generator);
	for (int i = 0; i < n; i++) {
		int temp = distribution(generator);
		a[i] = roll();
	}*/

	string buffer;
	getline(cin, buffer);
	try {
		int year = stoi(buffer);
		cout << "next: " << year + 1 << endl;
	}
	catch (const exception& e) {
		cout << "sai: " << e.what() << endl;
	}
}