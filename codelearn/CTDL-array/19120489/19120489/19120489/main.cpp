#include <iostream>
#include"data.h"
#include"sort.h"
#include<fstream>
#include<time.h>
#include<string>
#include<sstream>

#define MAX 100000

using namespace std;

int main()
{
	int input_size[1] = { 1000 };  //sotre input size in a array  ,3000,10000,30000,100000,300000
	int iter_size = 0; // each input size iterator

	double timeStorage[12];

	int iter_time = 0;
	int array[MAX];
	int temp[MAX];

	string input_state[4] = { "Random","Sorted","Reserve Sorted","Nearly Sorted" };
	int iter_state = 0;
	clock_t start, end;

	// An array of sorting function, pointer use to call and pass through the array
	void(*sorting_fun_array[])(int arr[], int n) = { selectionSort,insertionSort,insertionBinarySort,bubbleSort,shakerSort,shellSort,heapSort,callQuickSort,callMergeSort,counting_sort,radixsort,flashsort };
	string sort_algo_name[12] = { "selection Sort","insertion Sort","insertion Binary Sort","bubble Sort","shaker Sort","shell Sort","heap Sort","Quick Sort","Merge Sort","Counting Sort","Radix Sort","Flash Sort" };
	string locate = "C:/Users/Admin/Desktop/19120489/result";

	ofstream TimeFile, File_sort;

	//iter_size maximum = 5 ,  iter_state maximun = 4,  iter_time maximun = 12

	while (iter_state < 4) {

		TimeFile.open("C:/Users/Admin/Desktop/19120489/result/Time Measure.csv", ios::app);
		if (TimeFile.is_open()) {

			while (iter_size < 5) {
				GenerateData(array, input_size[iter_size], iter_state);


				while (iter_time < 12) {

					//Copy array to temp array
					for (int i = 0; i < input_size[iter_size]; i++) {
						temp[i] = array[i];
					}

					//Measure excute time of the algorithm
					start = clock();
					(*sorting_fun_array[iter_time])(temp, input_size[iter_size]);
					end = clock();

					//Out put to txt file the sorted array
					string file_path = locate + sort_algo_name[iter_time] + '_' + input_state[iter_state] + '_' + to_string(input_size[iter_size]) + ".txt";
					File_sort.open(file_path);
					for (int i = 0; i < input_size[iter_size]; i++) {
						File_sort << temp[i] << ' ';
					}
					File_sort.close();

					timeStorage[iter_time] = double(end - start) / double(CLOCKS_PER_SEC);
					iter_time++;

				}

				iter_time = 0; // reset time storage iterator

				//Write to file
				TimeFile << input_state[iter_state] + ',' + to_string(input_size[iter_size]) + ',';
				while (iter_time < 12)
				{
					TimeFile << timeStorage[iter_time] << ',';
					iter_time++;
				}
				iter_time = 0; //reset time storage iterator

				TimeFile << "\n";
				iter_size++;
			}
		}

		else {
			cout << "Failure";
			break;
			exit(EXIT_FAILURE);

		}

		TimeFile.close();
		iter_size = 0;//Reset input size iterator
		iter_state++;
	}

	return 0;

}