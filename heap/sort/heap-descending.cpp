#include <iostream>
using namespace std;

// Swap helper
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Maintain min-heap property
void minHeapify(int* arr, int index, int size) {
    int left = 2 * index;
    int right = 2 * index + 1;
    int smallest = index;

    if (left <= size && arr[left] < arr[smallest])
        smallest = left;

    if (right <= size && arr[right] < arr[smallest])
        smallest = right;

    if (smallest != index) {
        swap(arr[index], arr[smallest]);
        minHeapify(arr, smallest, size);
    }
}

// Build min heap (bottom-up)
void buildMinHeap(int* arr, int size) {
    for (int i = size / 2; i > 0; i--)
        minHeapify(arr, i, size);
}

// Perform heap sort (descending order)
void heapSortDescending(int* arr, int size) {
    buildMinHeap(arr, size); // Step 1: Build Min Heap

    for (int i = size; i >= 2; i--) {
        swap(arr[1], arr[i]);       // Move smallest to end
        minHeapify(arr, 1, i - 1);  // Heapify reduced heap
    }
}

// Utility: Print array (1-indexed)
void printArray(int* arr, int size) {
    for (int i = 1; i <= size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int size = 6;
    int* arr = new int[size + 1];  // +1 for index 0 (unused)

    arr[1] = 12;
    arr[2] = 11;
    arr[3] = 13;
    arr[4] = 5;
    arr[5] = 6;
    arr[6] = 7;

    cout << "Original array: ";
    printArray(arr, size);

    heapSortDescending(arr, size);

    cout << "Sorted (descending): ";
    printArray(arr, size);

    delete[] arr;
    return 0;
}
