#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <chrono> 
using namespace std;
using namespace std::chrono;

void generateRandomArray(int arr[], int n);
double bubbleSort(int arr[], int n);
double selectionSort(int arr[], int n);
double binarySort(int arr[], int n);
int binarySearch(int arr[], int low, int high, int key);

void printTableRow(int size, double bubbleTime, double selectionTime, double binaryTime);

int main() {
    const int sizes[] = { 10, 100, 1000, 10000, 100000}; 
    const int numSizes = 5;            
    cout << setw(10) << "Size" << setw(20) << "Bubble Sort (ms)"
        << setw(20) << "Selection Sort (ms)" << setw(20) << "Binary Sort (ms)" << endl;
    cout << string(70, '-') << endl;

    for (int i = 0; i < numSizes; ++i) {
        int size = sizes[i];
        int* arr = new int[size]; 

        generateRandomArray(arr, size);
        double bubbleTime = bubbleSort(arr, size);

        generateRandomArray(arr, size);
        double selectionTime = selectionSort(arr, size);

        generateRandomArray(arr, size);
        double binaryTime = binarySort(arr, size);

        printTableRow(size, bubbleTime, selectionTime, binaryTime);

        delete[] arr; 
    }

    return 0;
}

void generateRandomArray(int arr[], int n) {
    srand(static_cast<unsigned int>(time(NULL))); 
    for (int i = 0; i < n; ++i) {
        arr[i] = rand() % 1000; 
    }
}

double bubbleSort(int arr[], int n) {
    auto start = high_resolution_clock::now(); // Start time

    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }

    auto end = high_resolution_clock::now(); // End time
    duration<double> duration = end - start; // Calculate the time taken
    return duration.count() * 1000; // Convert to milliseconds
}

double selectionSort(int arr[], int n) {
    auto start = high_resolution_clock::now(); // Start time

    for (int i = 0; i < n - 1; ++i) {
        int minIndex = i;
        for (int j = i + 1; j < n; ++j) {
            if (arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }
        swap(arr[i], arr[minIndex]);
    }

    auto end = high_resolution_clock::now(); // End time
    duration<double> duration = end - start; // Calculate the time taken
    return duration.count() * 1000; // Convert to milliseconds
}

double binarySort(int arr[], int n) {
    auto start = high_resolution_clock::now(); // Start time

    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int low = 0;
        int high = i;

        int pos = binarySearch(arr, low, high, key);
        for (int j = i; j > pos; --j) {
            arr[j] = arr[j - 1];
        }

        arr[pos] = key; 
    }

    auto end = high_resolution_clock::now(); // End time
    duration<double> duration = end - start; // Calculate the time taken
    return duration.count() * 1000; // Convert to milliseconds
}
int binarySearch(int arr[], int low, int high, int key) {
    while (low < high) {
        int mid = (low + high) / 2;
        if (key < arr[mid]) {
            high = mid;
        }
        else {
            low = mid + 1;
        }
    }
    return low;
}
void printTableRow(int size, double bubbleTime, double selectionTime, double binaryTime) {
    cout << setw(10) << size
        << setw(20) << fixed << setprecision(4) << bubbleTime
        << setw(20) << fixed << setprecision(4) << selectionTime
        << setw(20) << fixed << setprecision(4) << binaryTime
        << endl;
}

