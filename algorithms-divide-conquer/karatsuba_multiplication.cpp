#include <iostream>
#include <string>
#include <ctime>
#include <cassert>
#include <vector>
using namespace std;

class Karatsuba {
public:
    string multiply(string x, string y) {
        // assume x > 0 && y > 0
        int len1 = x.size(), len2 = y.size();
        if (len1 != len2) {
            string prefix(abs(len1-len2), '0');
            if (len1 < len2) x = prefix + x;
            else y = prefix + y;
        }
        
        int n = x.size();
        if (n == 1) return to_string((x[0] - '0') * (y[0] - '0'));

        // x = a * 10^(n/2) + b
        string a = x.substr(0, n / 2), b = x.substr(n / 2);
        // y = c * 10^(n/2) + d
        string c = y.substr(0, n / 2), d = y.substr(n / 2);

        // x * y = ac * 10^n + 10^(n/2)(ad + bc) + bd
        // one optimization: ad + bc = (a+b)(c+d) - ac - bd, which can reduce recursive calls from 4 to 3
        string left = multiply(a, c);
        string right = multiply(b, d);
        string mid = minus(minus(multiply(add(a, b), add(c, d)), left), right);
        left +=  string(n % 2 == 0 ? n : n + 1, '0');
        mid += string(n % 2 == 0 ? n / 2 : n / 2 + 1, '0');

        return add(add(left, mid), right);
    }

private:
    string add(string a, string b) {
        string result;
        int i = a.size() - 1, j = b.size() - 1, carry = 0;

        while (i >= 0 || j >= 0) {
            int sum = carry;
            if (i >= 0) sum += a[i--] - '0';
            if (j >= 0) sum += b[j--] - '0';

            carry = sum / 10;
            sum = sum % 10;
            result.push_back(sum + '0');
        }
        if (carry > 0) result.push_back(carry + '0');

        reverse(result.begin(), result.end());
        i = 0;
        while (i < result.size() - 1 && result[i] == '0') i++;
        return result.substr(i);
    }

    string minus(string a, string b) {
        // assume a - b > 0        
        string result;
        vector<int> aa, bb;
        for (char c : a) aa.push_back(c - '0');
        for (char c : b) bb.push_back(c - '0');

        int i = aa.size() - 1, j = bb.size() - 1;
        while (i >= 0 || j >= 0) {
            int cur = aa[i];
            if (j >= 0) cur -= bb[j];
            if (cur < 0) {
                cur += 10;
                aa[i-1] -= 1;
            }
            result.push_back(cur + '0');

            i--;
            j--;
        }
        
        reverse(result.begin(), result.end());
        i = 0;
        while (i < result.size() - 1 && result[i] == '0') i++;
        return result.substr(i);
    }
};

int main() {
    Karatsuba kara;

    srand(time(0));
    for (int i = 0; i < 10; ++i) {
        int a = rand() % 50000 + 1;
        int b = rand() % 40000 + 1;
        cout << "test " + to_string(a) + " * " + to_string(b) << "\n";
        assert(to_string(a * b) == kara.multiply(to_string(a), to_string(b)));
    }
    cout << "success.\n";
}