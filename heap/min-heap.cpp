#include <iostream>
using namespace std;

// Swap helper
void swap(int &a, int &b) {
    int temp = a;
    a = b;
    b = temp;
}

// Heapify the subtree rooted at index `index`
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

// Build Min Heap from arbitrary array (1-indexed)
void buildMinHeap(int* arr, int size) {
    for (int i = size / 2; i >= 1; i--)
        minHeapify(arr, i, size);
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

    buildMinHeap(arr, size);

    cout << "Min Heap: ";
    printHeap(arr, size);

    delete[] arr; // free memory
    return 0;
}
