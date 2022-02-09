#include <iostream>
#include <fstream>
#include <cmath>
#include <time.h>
using namespace std;

template <class T>
void HoanVi(T& a, T& b)
{
	T x = a;
	a = b;
	b = x;
}

//-------------------------------------------------

// Hàm phát sinh mảng dữ liệu ngẫu nhiên
void GenerateRandomData(int a[], int n)
{
	srand((unsigned int)time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % n;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự tăng dần
void GenerateSortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
}

// Hàm phát sinh mảng dữ liệu có thứ tự ngược (giảm dần)
void GenerateReverseData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = n - 1 - i;
	}
}

// Hàm phát sinh mảng dữ liệu gần như có thứ tự
void GenerateNearlySortedData(int a[], int n)
{
	for (int i = 0; i < n; i++)
	{
		a[i] = i;
	}
	srand((unsigned int)time(NULL));
	for (int i = 0; i < 10; i++)
	{
		int r1 = rand() % n;
		int r2 = rand() % n;
		HoanVi(a[r1], a[r2]);
	}
}

void GenerateData(int a[], int n, int dataType)
{
	switch (dataType)
	{
	case 0:	// ngẫu nhiên
		GenerateRandomData(a, n);
		break;
	case 1:	// có thứ tự
		GenerateSortedData(a, n);
		break;
	case 2:	// có thứ tự ngược
		GenerateReverseData(a, n);
		break;
	case 3:	// gần như có thứ tự
		GenerateNearlySortedData(a, n);
		break;
	default:
		printf("Error: unknown data type!\n");
	}
}

// selection sort

void selectionSort(int arr[], int n)
{
	int i, j, min_idx;

	
	for (i = 0; i < n - 1; i++)
	{
		
		min_idx = i;
		for (j = i + 1; j < n; j++)
			if (arr[j] < arr[min_idx])
				min_idx = j;

		
		HoanVi(arr[min_idx], arr[i]);
	}
}


void insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}


int binarySearch(int a[], int item,
	int low, int high)
{
	if (high <= low)
		return (item > a[low]) ?
		(low + 1) : low;

	int mid = (low + high) / 2;

	if (item == a[mid])
		return mid + 1;

	if (item > a[mid])
		return binarySearch(a, item,
			mid + 1, high);
	return binarySearch(a, item, low,
		mid - 1);
}


void b_insertionSort(int a[], int n)
{
	int i, loc, j, k, selected;

	for (i = 1; i < n; ++i)
	{
		j = i - 1;
		selected = a[i];

		
		loc = binarySearch(a, selected, 0, j);

		
		while (j >= loc)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = selected;
	}
}

//Bubble sort
void bubbleSort(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)

	
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
				HoanVi(arr[j], arr[j + 1]);
}

// ShakerSort
void shakerSort(int a[], int n)
{
	int Left = 0;
	int Right = n - 1;
	int k = 0;
	while (Left < Right)
	{
		for (int i = Left; i < Right; i++)
		{
			if (a[i] > a[i + 1])
			{
				HoanVi(a[i], a[i + 1]);
				k = i;
			}
		}
		Right = k;
		for (int i = Right; i > Left; i--)
		{
			if (a[i] < a[i - 1])
			{
				HoanVi(a[i], a[i - 1]);
				k = i;
			}
		}
		Left = k;
	}
}

//Shell Sort
int shellSort(int arr[], int n)
{
	
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		
		for (int i = gap; i < n; i += 1)
		{
			
			int temp = arr[i];

			
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
				arr[j] = arr[j - gap];

			
			arr[j] = temp;
		}
	}
	return 0;
}

//Heap Sort
void heapify(int arr[], int n, int i)
{
	int largest = i; 
	int l = 2 * i + 1; 
	int r = 2 * i + 2; 

	
	if (l < n && arr[l] > arr[largest])
		largest = l;


	if (r < n && arr[r] > arr[largest])
		largest = r;

	if (largest != i) {
		HoanVi(arr[i], arr[largest]);

		
		heapify(arr, n, largest);
	}
}


void heapSort(int arr[], int n)
{
	
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	
	for (int i = n - 1; i > 0; i--) {
		
		HoanVi(arr[0], arr[i]);

		
		heapify(arr, i, 0);
	}
}

//Merge Sort
void merge(int arr[], int l, int m, int r)
{
	int n1 = m - l + 1;
	int n2 = r - m;

	
	int* L = new int[n1];
	int* R = new int[n2];

	
	for (int i = 0; i < n1; i++)
		L[i] = arr[l + i];
	for (int j = 0; j < n2; j++)
		R[j] = arr[m + 1 + j];

	
	int i = 0;

	
	int j = 0;

	
	int k = l;

	while (i < n1 && j < n2) {
		if (L[i] <= R[j]) {
			arr[k] = L[i];
			i++;
		}
		else {
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	
	while (i < n1) {
		arr[k] = L[i];
		i++;
		k++;
	}

	
	while (j < n2) {
		arr[k] = R[j];
		j++;
		k++;
	}
}


void mergeSort(int arr[], int l, int r) {
	if (l >= r) {
		return;
	}
	int m = (l + r - 1) / 2;
	mergeSort(arr, l, m);
	mergeSort(arr, m + 1, r);
	merge(arr, l, m, r);
}

// Quick Sort
int partition(int arr[], int low, int high)
{
	int mid = (low + high) / 2;
	if (arr[low] > arr[mid]) HoanVi(arr[low], arr[mid]);
	if (arr[low] > arr[high]) HoanVi(arr[low], arr[high]);
	if (arr[high] > arr[mid]) HoanVi(arr[high], arr[mid]);
	int pivot = arr[high]; // Pivot
	int left = low;
	int right = high - 1;

	while (true) {
		while (left <= right && arr[left] < pivot) left++;
		while (right >= left && arr[right] > pivot) right--;
		if (left >= right) break;
		swap(arr[left], arr[right]);
		left++;
		right--;
	}
	swap(arr[left], arr[high]);
	return left;
}


void quickSort(int arr[], int low, int high)
{
	if (low < high)
	{
		
		int pi = partition(arr, low, high);

		
		quickSort(arr, low, pi - 1);
		quickSort(arr, pi + 1, high);
	}
}

// Counting sort

void counting_sort(int input[], int n)
{

	int* output = new int[n]; 
	int max = input[0];
	int min = input[0];

	for (int i = 1; i < n; i++)
	{
		if (input[i] > max)
			max = input[i]; 
		else if (input[i] < min)
			min = input[i]; 
	}

	int k = max - min + 1; 

	int* count_array=new int[k]; 
	fill_n(count_array, k, 0); 

	for (int i = 0; i < n; i++)
		count_array[input[i] - min]++; 

	
	for (int i = 1; i < k; i++)
		count_array[i] += count_array[i - 1];


	
	for (int i = 0; i < n; i++)
	{
		output[count_array[input[i] - min] - 1] = input[i];
		count_array[input[i] - min]--;
	}


	for (int i = 0; i < n; i++)
		input[i] = output[i]; 

}

//Radix sort
int getMax(int arr[], int n)
{
	int mx = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > mx)
			mx = arr[i];
	return mx;
}


void countSort(int arr[], int n, int exp)
{
	int* output=new int[n]; 
	int i, count[10] = { 0 };

	
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	
	for (i = n - 1; i >= 0; i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}


	for (i = 0; i < n; i++)
		arr[i] = output[i];
}


// Radix Sort 
void radixsort(int arr[], int n)
{
	
	int m = getMax(arr, n);


	for (int exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, n, exp);
}


void print(int arr[], int n)
{
	for (int i = 0; i < n; i++)
		cout << arr[i] << " ";
}

//Flash Sort
void flashsort(int array[], int length)
{
	if (length == 0) return;

	
	int m = (int)((0.2 * length) + 2);

	
	int min, max, maxIndex;
	min = max = array[0];
	maxIndex = 0;

	for (int i = 1; i < length - 1; i += 2)
	{
		int small;
		int big;
		int bigIndex;

		
		if (array[i] < array[i + 1])
		{
			small = array[i];
			big = array[i + 1];
			bigIndex = i + 1;
		}
		else
		{
			big = array[i];
			bigIndex = i;
			small = array[i + 1];
		}

		if (big > max)
		{
			max = big;
			maxIndex = bigIndex;
		}

		if (small < min)
		{
			min = small;
		}
	}


	if (array[length - 1] < min)
	{
		min = array[length - 1];
	}
	else if (array[length - 1] > max)
	{
		max = array[length - 1];
		maxIndex = length - 1;
	}

	if (max == min)
	{
		
		return;
	}

	
	int* L = new int[m + 1];

	
	for (int t = 1; t <= m; t++)
	{
		L[t] = 0;
	}

	
	double c = (m - 1.0) / (max - min);
	int K;
	for (int h = 0; h < length; h++)
	{
		
		K = ((int)((array[h] - min) * c)) + 1;

	
		L[K] += 1;
	}

	
	for (K = 2; K <= m; K++)
	{
		L[K] = L[K] + L[K - 1];
	}

	
	int temp = array[maxIndex];
	array[maxIndex] = array[0];
	array[0] = temp;

	
	int j = 0;

	
	K = m;

	int numMoves = 0;

	while (numMoves < length)
	{
		
		while (j >= L[K])
		{
			j++;
			
			K = ((int)((array[j] - min) * c)) + 1;
		}

		
		int evicted = array[j];

		while (j < L[K])
		{
			
			K = ((int)((evicted - min) * c)) + 1;

			int location = L[K] - 1;

			int temp = array[location];
			array[location] = evicted;
			evicted = temp;

			L[K] -= 1;

			numMoves++;
		}
	}

	
	int threshold = (int)(1.25 * ((length / m) + 1));
	const int minElements = 30;

	
	for (K = m - 1; K >= 1; K--)
	{
		
		int classSize = L[K + 1] - L[K];

		if (classSize > threshold && classSize > minElements)
		{
			
			flashsort(&array[L[K]], classSize);
		}
		else 
		{
			if (classSize > 1)
			{
				insertionSort(&array[L[K]], classSize);
			}
		}
	}

	delete[] L;
}

void Copy(int a[], int b[],int n) {
	for (int i = 0; i < n; i++) {
		b[i] = a[i];
	}
}

int main() {
	ofstream f("time_data.txt");
	if (f.fail()) {
		cout << " Can't open file";
		return 0;
	}
	int n[5] = { 3000,10000,30000,100000,300000 };
	int* a = NULL;
	for (int i = 0; i < 5; i++) {
		a = new int[n[i]];
		int* b = new int[n[i]];

		GenerateData(a, n[i],2);
		Copy(a,b,n[i]);

		clock_t start, end;
		double time_use;

		start = clock();
		selectionSort(a, n[i]);
		end = clock();

		f << "selection sort\n";
		time_use = (double)(end - start) *1000000.0/ CLOCKS_PER_SEC; //us

		f << n[i] << ": " << time_use<<endl;
		
		Copy(b, a, n[i]);

		start = clock();
		insertionSort(a, n[i]);
		end = clock();

		f << "insertionSort\n";
		time_use = (double)(end - start) * 1000000.0 / CLOCKS_PER_SEC; //us
		f << n[i] << ": " << time_use <<endl;

		Copy(b, a, n[i]);

		start = clock();
		b_insertionSort(a, n[i]);
		end = clock();

		f << "binary-insertionSort\n";
		time_use = (double)(end - start) * 1000000.0 / CLOCKS_PER_SEC; //us
		f << n[i] << ": " << time_use << endl;
		
		Copy(b, a, n[i]);

		start = clock();
		bubbleSort(a, n[i]);
		end = clock();

		f << "bubble sort\n";
		time_use = (double)(end - start) * 1000000.0 / CLOCKS_PER_SEC; //us
		f << n[i] << ": " << time_use << endl;

		Copy(b, a, n[i]);

		start = clock();
		shakerSort(a, n[i]);
		end = clock();

		f << "shake Sort\n";
		time_use = (double)(end - start) * 1000000.0 / CLOCKS_PER_SEC; //us
		f << n[i] << ": " << time_use << endl;
		
		Copy(b, a, n[i]);

		start = clock();
		shellSort(a, n[i]);
		end = clock();

		f << "shellsort\n";
		time_use = (double)(end - start) * 1000000.0 / CLOCKS_PER_SEC; //us
		f << n[i] << ": " << time_use << endl;

		Copy(b, a, n[i]);

		start = clock();
		heapSort(a, n[i]);
		end = clock();

		f << "heapsort\n";
		time_use = (double)(end - start) * 1000000.0 / CLOCKS_PER_SEC; //us
		f << n[i] << ": " << time_use << endl;

		Copy(b, a, n[i]);

		start = clock();
		mergeSort(a, 0,n[i]-1);
		end = clock();

		f << "mergesort\n";
		time_use = (double)(end - start) * 1000000.0 / CLOCKS_PER_SEC; //us
		f << n[i] << ": " << time_use << endl;

		Copy(b, a, n[i]);

		start = clock();
		quickSort(a, 0,n[i]-1);
		end = clock();

		f << "Quicksort\n";
		time_use = (double)(end - start) * 1000000.0 / CLOCKS_PER_SEC; //us
		f << n[i] << ": " << time_use << endl;

		Copy(b, a, n[i]);

		start = clock();
		counting_sort(a, n[i]);
		end = clock();

		f << "Counting Sort\n";
		time_use = (double)(end - start) * 1000000.0 / CLOCKS_PER_SEC; //us
		f << n[i] << ": " << time_use << endl;

		Copy(b, a, n[i]);

		start = clock();
		radixsort(a, n[i]);
		end = clock();

		f << "Radix sort\n";
		time_use = (double)(end - start) * 1000000.0 / CLOCKS_PER_SEC; //us
		f << n[i] << ": " << time_use << endl;

		Copy(b, a, n[i]);

		start = clock();
		flashsort(a, n[i]);
		end = clock();

		f << "flash sort\n";
		time_use = (double)(end - start) * 1000000.0 / CLOCKS_PER_SEC; //us
		f << n[i] << ": " << time_use << endl;
	}
}