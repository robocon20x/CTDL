#include "sort.h"
#include"data.h"
#include <vector>
#include<list>
#include<cmath>

//Selection Sort
void selectionSort(int arr[], int n) {
	int i, j, min_index;

	for (i = 0; i < n - 1; i++) {
		min_index = i;
		for (j = i + 1; j < n; j++) {

			if (arr[min_index] > arr[j])
				min_index = j;
		}
		HoanVi(arr[min_index], arr[i]);
	}

}

//Insertion sort
void insertionSort(int arr[], int n)
{
	int i, key, j;
	for (i = 1; i < n; i++)
	{
		key = arr[i];
		j = i - 1;

		/* Move elements of arr[0..i-1], that are
		greater than key, to one position ahead
		of their current position */
		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}
		arr[j + 1] = key;
	}
}


//Binary Insertion sort
int binarySearch(int a[], int item, int low, int high)
{
	if (high <= low)
		return (item > a[low]) ? (low + 1) : low;

	int mid = (low + high) / 2;

	if (item == a[mid])
		return mid + 1;

	if (item > a[mid])
		return binarySearch(a, item, mid + 1, high);
	return binarySearch(a, item, low, mid - 1);
}
void insertionBinarySort(int a[], int n)
{
	int i, loc, j, k, selected;

	for (i = 1; i < n; ++i)
	{
		j = i - 1;
		selected = a[i];

		// find location where selected sould be inseretd 
		loc = binarySearch(a, selected, 0, j);

		// Move all elements after location to create space 
		while (j >= loc)
		{
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = selected;
	}
}


//Bubble Sort
void bubbleSort(int arr[], int n)
{
	int i, j;
	for (i = 0; i < n - 1; i++)

		// Last i elements are already in place  
		for (j = 0; j < n - i - 1; j++)
			if (arr[j] > arr[j + 1])
				HoanVi(arr[j], arr[j + 1]);
}


//Shaker sort
void shakerSort(int a[], int n)
{
	bool swapped = true;
	int start = 0;
	int end = n - 1;

	while (swapped) {
		// reset the swapped flag on entering 
		// the loop, because it might be true from 
		// a previous iteration. 
		swapped = false;

		// loop from left to right same as 
		// the bubble sort 
		for (int i = start; i < end; ++i) {
			if (a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
				swapped = true;
			}
		}

		// if nothing moved, then array is sorted. 
		if (!swapped)
			break;

		// otherwise, reset the swapped flag so that it 
		// can be used in the next stage 
		swapped = false;

		// move the end point back by one, because 
		// item at the end is in its rightful spot 
		--end;

		// from right to left, doing the 
		// same comparison as in the previous stage 
		for (int i = end - 1; i >= start; --i) {
			if (a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
				swapped = true;
			}
		}

		// increase the starting point, because 
		// the last stage would have moved the next 
		// smallest number to its rightful spot. 
		++start;
	}
}

//Shell Sort
void shellSort(int arr[], int n)
{
	// Start with a big gap, then reduce the gap 
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		// Do a gapped insertion sort for this gap size. 
		// The first gap elements a[0..gap-1] are already in gapped order 
		// keep adding one more element until the entire array is 
		// gap sorted  
		for (int i = gap; i < n; i += 1)
		{
			// add a[i] to the elements that have been gap sorted 
			// save a[i] in temp and make a hole at position i 
			int temp = arr[i];

			// shift earlier gap-sorted elements up until the correct  
			// location for a[i] is found 
			int j;
			for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
				arr[j] = arr[j - gap];

			//  put temp (the original a[i]) in its correct location 
			arr[j] = temp;
		}
	}
}


//Heap Sort

//void createHeap(int _array[], int _length)
//{
//	int offset, heapSize;
//	heapSize = _length - 1;
//
//	for (offset = (_length / 2); offset >= 0; offset--)
//	{
//		Heapify(_array, offset, heapSize);
//	}
//}
void heapify(int arr[], int n, int i)
{
	int largest = i; // Initialize largest as root 
	int l = 2 * i + 1; // left = 2*i + 1 
	int r = 2 * i + 2; // right = 2*i + 2 

	// If left child is larger than root 
	if (l < n && arr[l] > arr[largest])
		largest = l;

	// If right child is larger than largest so far 
	if (r < n && arr[r] > arr[largest])
		largest = r;

	// If largest is not root 
	if (largest != i)
	{
		swap(arr[i], arr[largest]);

		// Recursively heapify the affected sub-tree 
		heapify(arr, n, largest);
	}
}

// main function to do heap sort 
void heapSort(int arr[], int n)
{
	// Build heap (rearrange array) 
	for (int i = n / 2 - 1; i >= 0; i--)
		heapify(arr, n, i);

	// One by one extract an element from heap 
	for (int i = n - 1; i >= 0; i--)
	{
		// Move current root to end 
		swap(arr[0], arr[i]);

		// call max heapify on the reduced heap 
		heapify(arr, i, 0);
	}
}


//QuickSorr

void Swap_element_array(int arr[], int low, int high) {
	HoanVi(arr[low], arr[high]);
}

//Median of three to choose a pivot
int MedianOfThree(int arr[], int low, int high) {
	int center = (low + high) / 2;

	if (arr[low] > arr[center]) Swap_element_array(arr, center, low);
	if (arr[low] > arr[high]) Swap_element_array(arr, low, high);
	if (arr[center] > arr[high]) Swap_element_array(arr, center, high);

	return center;
}

//Partition
int partition(int arr[], int low, int high) {

	int pivot = MedianOfThree(arr, low, high);
	int left = low;
	int right = high - 1;

	while (true) {
		while (left <= right && arr[left] < arr[pivot]) left++;
		while (right >= left && arr[right] > arr[pivot]) right--;
		if (left >= right) break;
		HoanVi(arr[left], arr[right]);
		left++;
		right--;
	}
	HoanVi(arr[left], arr[pivot]);

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

void callQuickSort(int arr[], int n) {
	int low = 0;
	int high = n - 1;
	quickSort(arr, low, high);

}

//Merge Sort
void merge(int arr[], int l, int m, int r)
{
	int i, j, k;
	int n1 = m - l + 1;
	int n2 = r - m;

	/* create temp arrays */
	vector<int> L;
	vector<int> R;

	/* Copy data to temp arrays L[] and R[] */
	for (i = 0; i < n1; i++)
		L.push_back(arr[l + i]);
	for (j = 0; j < n2; j++)
		R.push_back(arr[m + 1 + j]);

	/* Merge the temp arrays back into arr[l..r]*/
	i = 0; // Initial index of first subarray 
	j = 0; // Initial index of second subarray 
	k = l; // Initial index of merged subarray 
	while (i < n1 && j < n2)
	{
		if (L[i] <= R[j])
		{
			arr[k] = L[i];
			i++;
		}
		else
		{
			arr[k] = R[j];
			j++;
		}
		k++;
	}

	/* Copy the remaining elements of L[], if there
	   are any */
	while (i < n1)
	{
		arr[k] = L[i];
		i++;
		k++;
	}

	/* Copy the remaining elements of R[], if there
	   are any */
	while (j < n2)
	{
		arr[k] = R[j];
		j++;
		k++;
	}
}

/* l is for left index and r is right index of the
   sub-array of arr to be sorted */
void mergeSort(int arr[], int l, int r)
{
	if (l < r)
	{
		// Same as (l+r)/2, but avoids overflow for 
		// large l and h 
		int m = l + (r - l) / 2;

		// Sort first and second halves 
		mergeSort(arr, l, m);
		mergeSort(arr, m + 1, r);

		merge(arr, l, m, r);
	}
}
void callMergeSort(int arr[], int n) {
	int l = 0;
	int r = n - 1;
	mergeSort(arr, l, r);
}

//Counting Sort
void counting_sort(int input[], int n)
{
	int* output= new int[n]; // The output will have sorted input array
	int max = input[0];
	int min = input[0];

	int i;
	for (i = 1; i < n; i++)
	{
		if (input[i] > max)
		else if (input[i] < min)
			min = input[i]; // Minimum value in array
	}

	int k = max - min + 1; // Size of count array

	int* count_array=new int[k]; // Create a count_array to store count of each individual input value
	for (i = 0; i < k; i++)
		count_array[i] = 0;

	for (i = 0; i < n; i++)
		count_array[input[i] - min]++; // Store count of each individual input value

	/* Change count_array so that count_array now contains actual
	 position of input values in output array */
	for (i = 1; i < k; i++)
		count_array[i] += count_array[i - 1];

	// Populate output array using count_array and input array
	for (i = 0; i < n; i++)
	{
		output[count_array[input[i] - min] - 1] = input[i];
		count_array[input[i] - min]--;
	}

	for (i = 0; i < n; i++)
		input[i] = output[i]; // Copy the output array to input, so that input now contains sorted values

}

//Radix Sort
// Get maximum value from array.
int getMax(int arr[], int n)
{
	int max = arr[0];
	for (int i = 1; i < n; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
}

// Count sort of arr[].
void countSort(int arr[], int n, int exp)
{
	// Count[i] array will be counting the number of array values having that 'i' digit at their (exp)th place.  
	int* output = new int[n], i, count[10] = { 0 };

	// Count the number of times each digit occurred at (exp)th place in every input.
	for (i = 0; i < n; i++)
		count[(arr[i] / exp) % 10]++;

	// Calculating their cumulative count.
	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	// Inserting values according to the digit '(arr[i] / exp) % 10' fetched into count[(arr[i] / exp) % 10].
	for (i = n - 1; i >= 0; i--)
	{
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	// Assigning the result to the arr pointer of main().
	for (i = 0; i < n; i++)
		arr[i] = output[i];
	delete[] output;
}

// Sort arr[] of size n using Radix Sort.
void radixsort(int arr[], int n)
{
	int exp, m;
	m = getMax(arr, n);

	// Calling countSort() for digit at (exp)th place in every input.
	for (exp = 1; m / exp > 0; exp *= 10)
		countSort(arr, n, exp);
}

//Flash Sort
void flashsort(int array[], int length)
{
	if (length == 0) return;

	//20% of the number of elements or 0.2n classes will
	//be used to distribute the input data set into
	//there must be at least 2 classes (hence the addition)
	int m = (int)((0.2 * length) + 2);

	//-------CLASS FORMATION-------

	//O(n)
	//compute the max and min values of the input data
	int min, max, maxIndex;
	min = max = array[0];
	maxIndex = 0;

	for (int i = 1; i < length - 1; i += 2)
	{
		int small;
		int big;
		int bigIndex;

		//which is bigger A(i) or A(i+1)
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

	//do the last element
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
		//all the elements are the same
		return;
	}

	//dynamically allocate the storage for L
	//note that L is in the range 1...m (hence
	//the extra 1)
	int* L = new int[m + 1];

	//O(m)
	//initialize L to contain all zeros (L[0] is unused)
	for (int t = 1; t <= m; t++)
	{
		L[t] = 0;
	}

	//O(n)
	//use the function K(A(i)) = 1 + INT((m-1)(A(i)-Amin)/(Amax-Amin))
	//to classify each A(i) into a number from 1...m
	//(note that this is mainly just a percentage calculation)
	//and then store a count of each distinct class K in L(K)
	//For instance, if there are 22 A(i) values that fall into class
	//K == 5 then the count in L(5) would be 22

	//IMPORTANT: note that the class K == m only has elements equal to Amax

	//precomputed constant
	double c = (m - 1.0) / (max - min);
	int K;
	for (int h = 0; h < length; h++)
	{
		//classify the A(i) value
		K = ((int)((array[h] - min) * c)) + 1;

		//assert: K is in the range 1...m

		//add one to the count for this class
		L[K] += 1;
	}

	//O(m)
	//sum over each L(i) such that each L(i) contains
	//the number of A(i) values that are in the ith
	//class or lower (see counting sort for more details)
	for (K = 2; K <= m; K++)
	{
		L[K] = L[K] + L[K - 1];
	}

	//-------PERMUTATION-------

	//swap the max value with the first value in the array
	int temp = array[maxIndex];
	array[maxIndex] = array[0];
	array[0] = temp;

	//Except when being iterated upwards,
	//j always points to the first A(i) that starts
	//a new class boundary && that class hasn't yet
	//had all of its elements moved inside its borders;

	//This is called a cycle leader since you know 
	//that you can begin permuting again here. You know
	//this becuase it is the lowest index of the class
	//and as such A(j) must be out of place or else all
	//the elements of this class have already been placed
	//within the borders of the this class (which means
	//j wouldn't be pointing to this A(i) in the first place)
	int j = 0;

	//K is the class of an A(i) value. It is always in the range 1..m
	K = m;

	//the number of elements that have been moved
	//into their correct class
	int numMoves = 0;

	//O(n)
	//permute elements into their correct class; each
	//time the class that j is pointing to fills up
	//then iterate j to the next cycle leader
	//
	//do not use the n - 1 optimization because that last element
	//will not have its count decreased (this causes trouble with
	//determining the correct classSize in the last step)
	while (numMoves < length)
	{
		//if j does not point to the begining of a class
		//that has at least 1 element still needing to be
		//moved to within the borders of the class then iterate
		//j upward until such a class is found (such a class
		//must exist). In other words, find the next cycle leader
		while (j >= L[K])
		{
			j++;
			//classify the A(j) value
			K = ((int)((array[j] - min) * c)) + 1;
		}

		//evicted always holds the value of an element whose location
		//in the array is free to be written into //aka FLASH
		int evicted = array[j];

		//while j continues to meet the condition that it is
		//pointing to the start of a class that has at least one
		//element still outside its borders (the class isn't full)
		while (j < L[K])
		{
			//compute the class of the evicted value
			K = ((int)((evicted - min) * c)) + 1;

			//get a location that is inside the evicted
			//element's class boundaries
			int location = L[K] - 1;

			//swap the value currently residing at the new
			//location with the evicted value
			int temp = array[location];
			array[location] = evicted;
			evicted = temp;

			//decrease the count for this class
			//see counting sort for why this is done
			L[K] -= 1;

			//another element was moved
			numMoves++;
		}
	}

	//-------RECURSION or STRAIGHT INSERTION-------

	//if the classes do not have the A(i) values uniformly distributed
	//into each of them then insertion sort will not produce O(n) results;

	//look for classes that have too many elements; ideally each class
	//(except the topmost or K == m class) should have about n/m elements;
	//look for classes that exceed n/m elements by some threshold AND have
	//more than some minimum number of elements to flashsort recursively

	//if the class has 25% more elements than it should
	int threshold = (int)(1.25 * ((length / m) + 1));
	const int minElements = 30;

	//for each class decide whether to insertion sort its members
	//or recursively flashsort its members;
	//skip the K == m class because it is already sorted
	//since all of the elements have the same value
	for (K = m - 1; K >= 1; K--)
	{
		//determine the number of elments in the Kth class
		int classSize = L[K + 1] - L[K];

		//if the class size is larger than expected but not
		//so small that insertion sort could make quick work
		//of it then...
		if (classSize > threshold && classSize > minElements)
		{
			//...attempt to flashsort the class. This will work 
			//well if the elements inside the class are uniformly
			//distributed throughout the class otherwise it will 
			//perform badly, O(n^2) worst case, since we will have 
			//performed another classification and permutation step
			//and not succeeded in making the problem significantly
			//smaller for the next level of recursion. However,
			//progress is assured since at each level the elements
			//with the maximum value will get sorted.
			flashsort(&array[L[K]], classSize);
		}
		else //perform insertion sort on the class
		{
			if (classSize > 1)
			{
				insertionSort(&array[L[K]], classSize);
			}
		}
	}

	delete[] L;
}