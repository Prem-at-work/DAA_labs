#include <iostream>
using namespace std;

//Linear search
int linearSearch(int arr[], int n, int target) {

    for(int i = 0; i < n; i++) {

        if(arr[i] == target) {
            return i;
        }
    }

    return -1;
}

//Binary search
int binarySearch(int arr[], int n, int target) {

    int start = 0;
    int end = n - 1;

    while(start <= end) {

        int mid = start + (end - start) / 2;

        if(arr[mid] == target) {
            return mid;
        }

        else if(arr[mid] < target) {
            start = mid + 1;
        }

        else {
            end = mid - 1;
        }
    }

    return -1;
}

int main() {

    int arr[] = {10, 20, 30, 40, 50};
    int n = 5;

    int target = 30;

    int index = linearSearch(arr, n, target);

    cout << index;

    return 0;
}