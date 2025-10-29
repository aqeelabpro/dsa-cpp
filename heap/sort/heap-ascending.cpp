#include <iostream>
using namespace std;

// Swap helper
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Maintain max-heap property for subtree rooted at index
void maxHeapify(int* arr, int index, int size) {
    int left = 2 * index;
    int right = 2 * index + 1;
    int largest = index;

    if (left <= size && arr[left] > arr[largest])
        largest = left;

    if (right <= size && arr[right] > arr[largest])
        largest = right;

    if (largest != index) {
        swap(arr[index], arr[largest]);
        maxHeapify(arr, largest, size);  // recursive heapify
    }
}

// Build max heap (bottom-up)
void buildMaxHeap(int* arr, int size) {
    for (int i = size / 2; i > 0; i--)
        maxHeapify(arr, i, size);
}

// Perform heap sort using Max Heap
void heapSort(int* arr, int size) {
    buildMaxHeap(arr, size); // Step 1: Build the heap

    for (int i = size; i >= 2; i--) {
        // Move current root (max) to the end
        swap(arr[1], arr[i]);

        // Heapify the reduced heap
        maxHeapify(arr, 1, i - 1);
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

    // Leave arr[0] unused
    arr[1] = 12;
    arr[2] = 11;
    arr[3] = 13;
    arr[4] = 5;
    arr[5] = 6;
    arr[6] = 7;

    cout << "Original array: ";
    printArray(arr, size);

    heapSort(arr, size);

    cout << "Sorted array: ";
    printArray(arr, size);

    delete[] arr; // free memory
    return 0;
}
