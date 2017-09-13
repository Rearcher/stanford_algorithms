#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

// coursera version
int partition_1(vector<int>& arr, int left, int right) {
    // choose arr[left] as pivot
    // optimization: choose pivot randomly
    int pivot = arr[left];
    int i = left + 1, j = left + 1;
    while (j <= right) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
        j++;
    }
    swap(arr[i-1], arr[left]);
    return i - 1;
}

// my origin version
int partition_2(vector<int>& arr, int left, int right) {
    // choose arr[left] as pivot
    int pivot = arr[left];
    int i = left, j = right + 1;
    while (i < j) {
        while (++i < right && arr[i] <= pivot);
        while (--j > left && arr[j] >= pivot);
        if (i >= j) break;
        swap(arr[i], arr[j]);
    }
    swap(arr[left], arr[j]);
    return j;
}

void quickSort(vector<int>& arr, int left, int right) {
    if (left >= right) return;

    int pivot = partition_2(arr, left, right);
    quickSort(arr, left, pivot - 1);
    quickSort(arr, pivot + 1, right);
    return;
}

int main() {
    srand(time(0));
    vector<int> arr{4, 3, 2, 1};
    // for (int i = 0; i < 10; ++i) arr.push_back(rand() % 1000);
    quickSort(arr, 0, arr.size() - 1);
    for (int i = 0; i < arr.size(); ++i) cout << arr[i] << " ";
}