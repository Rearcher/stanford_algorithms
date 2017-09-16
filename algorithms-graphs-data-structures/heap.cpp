#include <iostream>
#include <vector>
using namespace std;

// max heap implementation
class Heap {
public:
    void push(int x) {
        nums.push_back(x);
        maxHeapify(0, nums.size());
    }

    int pop() {
        if (nums.empty()) return -1;

        int result = nums[0];
        swap(nums[0], nums[nums.size()-1]);
        nums.pop_back();
        maxHeapify(0, nums.size());
        return result;
    }

    int top() {
        if (nums.empty()) return -1;
        return nums[0];
    }

private:
    // adjust heap in range [start, end)
    void maxHeapify(int start, int end) {
        int father = start;
        int son = father * 2 + 1;

        while (son < end) {
            if (son + 1 < end && nums[son + 1] > nums[son])
                son += 1;

            if (nums[father] >= nums[son]) return;

            swap(nums[father], nums[son]);
            father = son;
            son = father * 2 + 1;
        }
    }

    vector<int> nums;
};

int main() {
    Heap heap;
    heap.push(2);
    cout << heap.top() << endl;

    heap.push(3);
    cout << heap.top() << endl;

    heap.pop();
    cout << heap.top() << endl;

    heap.push(1);
    cout << heap.top() << endl;
}