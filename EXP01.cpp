#include <iostream>
using namespace std;

// Bubble sort
void bubbleSort(int arr[], int n) {

    for(int i = 0; i < n - 1; i++) {

        for(int j = 0; j < n - i - 1; j++) {

            if(arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
            }
        }
    }
}

// Selection Sort
void selectionSort(int arr[], int n) {

    for(int i = 0; i < n - 1; i++) {

        int minIndex = i;

        for(int j = i + 1; j < n; j++) {

            if(arr[j] < arr[minIndex]) {
                minIndex = j;
            }
        }

        swap(arr[i], arr[minIndex]);
    }
}

//Merge sort
void merge(int arr[], int start, int mid, int end) {

    int i = start;
    int j = mid + 1;

    int temp[100];
    int k = 0;

    while(i <= mid && j <= end) {

        if(arr[i] <= arr[j]) {
            temp[k] = arr[i];
            i++;
        }
        else {
            temp[k] = arr[j];
            j++;
        }

        k++;
    }

    while(i <= mid) {
        temp[k] = arr[i];
        i++;
        k++;
    }

    while(j <= end) {
        temp[k] = arr[j];
        j++;
        k++;
    }

    for(int x = start; x <= end; x++) {
        arr[x] = temp[x - start];
    }
}

void mergeSort(int arr[], int start, int end) {

    if(start >= end) {
        return;
    }

    int mid = start + (end - start) / 2;

    mergeSort(arr, start, mid);
    mergeSort(arr, mid + 1, end);

    merge(arr, start, mid, end);
}

//Quick sort
int partition(int arr[], int start, int end) {

    int pivot = arr[end];

    int i = start - 1;

    for(int j = start; j < end; j++) {

        if(arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    swap(arr[i + 1], arr[end]);

    return i + 1;
}

void quickSort(int arr[], int start, int end) {

    if(start >= end) {
        return;
    }

    int pivotIndex = partition(arr, start, end);

    quickSort(arr, start, pivotIndex - 1);
    quickSort(arr, pivotIndex + 1, end);
}

//Heap sort
void heapify(int arr[], int n, int i) {

    int largest = i;

    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if(left < n && arr[left] > arr[largest]) {
        largest = left;
    }

    if(right < n && arr[right] > arr[largest]) {
        largest = right;
    }

    if(largest != i) {

        swap(arr[i], arr[largest]);

        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {

    // Build max heap
    for(int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i);
    }

    // Move largest element to the end
    for(int i = n - 1; i > 0; i--) {

        swap(arr[0], arr[i]);

        heapify(arr, i, 0);
    }
}

int main() {

    int arr[] = {5, 3, 8, 4, 2};
    int n = 5;

    bubbleSort(arr, n);

    for(int i = 0; i < n; i++) {
        cout << arr[i] << " ";
    }

    return 0;
}