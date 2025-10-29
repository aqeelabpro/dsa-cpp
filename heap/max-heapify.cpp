#include <iostream>
using namespace std;

// Swap helper
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

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
        maxHeapify(arr, largest, size);
    }
}


// Build Max Heap from arbitrary array (1-indexed)
void buildMaxHeap(int* arr, int size) {
    for (int i = size / 2; i >= 1; i--)
        maxHeapify(arr, i, size);
}

// Print heap contents
void printHeap(int* arr, int size) {
    for (int i = 1; i <= size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int size = 5;
    int* arr = new int[size + 1]; // +1 for index 0 (unused)

    // Leave arr[0] empty
    arr[1] = 30;
    arr[2] = 40;
    arr[3] = 15;
    arr[4] = 10;
    arr[5] = 20;

    cout << "Original array: ";
    printHeap(arr, size);

    buildMaxHeap(arr, size);

    cout << "Min Heap: ";
    printHeap(arr, size);

    delete[] arr; // free memory
    return 0;
}
