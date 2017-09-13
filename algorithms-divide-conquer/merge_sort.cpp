#include <iostream>
#include <vector>
#include <ctime>
using namespace std;

void merge(vector<int>& arr, int left, int mid, int right) {
    vector<int> bak(arr.begin(), arr.end());
    int i = left, j = mid + 1;
    for (int k = left; k <= right; ++k) {
        if (i > mid) arr[k] = bak[j++];
        else if (j > right) arr[k] = bak[i++];
        else if (bak[i] < bak[j]) arr[k] = bak[i++];
        else arr[k] = bak[j++];
    }
}

void mergeSort_recursive(vector<int>& arr, int left, int right) {
    if (left >= right) return;

    int mid = left + (right - left) / 2;
    mergeSort_recursive(arr, left, mid);
    mergeSort_recursive(arr, mid + 1, right);
    merge(arr, left, mid, right);
    
    return;
}

void mergeSort_iterative(vector<int>& arr, int left, int right) {
    int n = arr.size();
    for (int size = 1; size <= n; size += size)
        for (int i = 0; i < n - size; i += size * 2)
            merge(arr, i, i + size - 1, min(i + size * 2 - 1, n - 1));
    return;
}

int main() {
    srand(time(0));
    vector<int> arr;
    for (int i = 0; i < 10; ++i) arr.push_back(rand() % 100);
    // mergeSort_recursive(arr, 0, arr.size() - 1);
    mergeSort_iterative(arr, 0, arr.size() - 1);
    for (int i = 0; i < arr.size(); ++i)
        cout << arr[i] << " ";
}