#include <iostream>
#include <vector>
using namespace std;

int partition(vector<int>& arr, int left, int right) {
    int pivot = arr[left];
    int i = left + 1, j = left + 1;
    while (j <= right) {
        if (arr[j] < pivot) {
            swap(arr[i], arr[j]);
            i++;
        }
        j++;
    }
    swap(arr[left], arr[i-1]);
    return i - 1;
}

// find the ith number in arr, assume arr's elements are different
int randomizedSelection(vector<int>& arr, int left, int right, int i) {
    // invalid i
    if (i <= 0 || i > right - left + 1) return -1;

    if (left == right) return arr[left];
    
    int pivot = partition(arr, left, right);
    int order = pivot - left + 1;
    if (i == order) return arr[pivot];
    else if (i > order) return randomizedSelection(arr, pivot + 1, right, i - order);
    else return randomizedSelection(arr, left, pivot - 1, i);
}

int main() {
    vector<int> arr{2, 5, 3, 4, 1};
    cout << randomizedSelection(arr, 0, arr.size() - 1, 4) << "\n";
}