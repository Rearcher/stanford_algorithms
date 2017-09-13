#include <iostream>
#include <vector>
using namespace std;

int countInversion(vector<int>& arr, int left, int right) {
    if (left >= right) return 0;

    int mid = left + (right - left) / 2;
    int x = countInversion(arr, left, mid);
    int y = countInversion(arr, mid + 1, right);
    int z = 0;

    int i = left, j = mid + 1;
    vector<int> bak(arr.begin(), arr.end());
    for (int k = left; k <= right; ++k) {
        if (i > mid) arr[k] = bak[j++];
        else if (j > right) arr[k] = bak[i++];
        else if (bak[i] > bak[j]) {
            arr[k] = bak[j++];
            z += mid - i + 1;
        } else arr[k] = bak[i++];
    }

    return x + y + z;
}

int main() {
    vector<int> a{3, 2, 1, 4, 2};
    cout << countInversion(a, 0, a.size() - 1) << "\n";
    for (int i = 0; i < a.size(); ++i) cout << a[i] << " ";
}