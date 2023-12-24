// Practice.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <string>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution1758 {
public:
    int minOperations(string s) {
        int start0 = 0;

        for (int i = 0; i < (int)s.length(); i++) {
            if (i % 2 == 0) {
                if (s[i] == '1') {
                    start0++;
                }
            }
            else {
                if (s[i] == '0') {
                    start0++;
                }
            }
        }

        return min(start0, (int)s.size() - start0);
    }
};



class Solution2 {
public:
    struct ListNode {
        int val;
        ListNode* next;
        ListNode() : val(0), next(nullptr) {}
        ListNode(int x) : val(x), next(nullptr) {}
        ListNode(int x, ListNode* next) : val(x), next(next) {}
    };

    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
        int first = l1->val + l2->val;
        int carry = first / 10;
        first = first % 10;

        ListNode* sum = new ListNode(first);
        ListNode* res = sum;

        l1 = l1->next;
        l2 = l2->next;

        bool l1_not_end = l1, l2_not_end = l2;

        while (l1_not_end || l2_not_end) {
            int next_val = (l1_not_end ? l1->val : 0) + (l2_not_end ? l2->val : 0) + carry;
            if (next_val >= 10) {
                carry = 1;
                next_val -= 10;
            }
            else carry = 0;

            sum->next = new ListNode(next_val);
            sum = sum->next;

            if (l1_not_end) {
                l1 = l1->next;
                l1_not_end = l1;
            }

            if (l2_not_end) {
                l2 = l2->next;
                l2_not_end = l2;
            }
        }
        if (carry != 0) {
            sum->next = new ListNode(carry);
        }
        return res;
    }
};

class Solution3 {
public:
    int lengthOfLongestSubstring(string s) {
        unordered_map<char, int> m;
        int longest = 0;
        int start = 0;
        int i = 0;
        for (int i = 0; i != s.length(); i++) {
            if (m.count(s[i]) == 0) {
                m.emplace(s[i], i);
            }
            else {
                if (m[s[i]] >= start) {
                    int new_start = m[s[i]] + 1;
                    int this_length = i - start;
                    if (this_length > longest) longest = this_length;
                    m[s[i]] = i;
                    start = new_start;
                }
                else {
                    m[s[i]] = i;
                }
            }
        }
        if ((int)s.length() - start > longest) longest = s.size() - start;
        return longest;
    }
};

class Solution4 { // Binary search. Need review. **
public:
    int p1 = 0, p2 = 0;

    // Get the smaller value between nums1[p1] and nums2[p2] and move the pointer forward.

    int getMin(vector<int>& nums1, vector<int>& nums2) {
        if (p1 < nums1.size() && p2 < nums2.size()) {
            return nums1[p1] < nums2[p2] ? nums1[p1++] : nums2[p2++];
        }
        else if (p1 < nums1.size()) {
            return nums1[p1++];
        }
        else if (p2 < nums2.size()) {
            return nums2[p2++];
        }
        return -1;
    }
    // O(m+n)
    double findMedianSortedArrays_direct(vector<int>& nums1, vector<int>& nums2) {
        int m = int(nums1.size()), n = int(nums2.size());

        if ((m + n) % 2 == 0) {
            for (int i = 0; i < (m + n) / 2 - 1; ++i) {
                int _ = getMin(nums1, nums2);
            }
            return (double)(getMin(nums1, nums2) + getMin(nums1, nums2)) / 2;
        }
        else {
            for (int i = 0; i < (m + n) / 2; ++i) {
                int _ = getMin(nums1, nums2);
            }
            return getMin(nums1, nums2);
        }

        return -1;
    }

    // Binary Search O(log(m+n))

};

int main()
{
    cout << "Hello" << endl;
}

class MyCircularQueue {
public:
    vector<int> values;
    int max_capacity;
    int start_p = 0, end_p = 1;


    MyCircularQueue(int k) {
        values = vector<int>();
        values.reserve(k);
        max_capacity = k;
    }

    bool enQueue(int value) {
        if (isFull()) return false;
        values[end_p] = value;
        end_p += 1;
        if (end_p == max_capacity) end_p = 0;
        return true;
    }

    bool deQueue() {
        if (isEmpty()) return false;
        start_p += 1;
        if (start_p == max_capacity) start_p = 0;
        return true;
    }

    int Front() {
        return values[start_p];
    }

    int Rear() {
        if (!isEmpty()) {
            return values[end_p == 0 ? max_capacity - 1 : end_p - 1];
        }
        return -100;
    }

    bool isEmpty() {
        if (end_p < start_p) return end_p + max_capacity - start_p == 1;
        return end_p - start_p == 1;
    }

    bool isFull() {
        return start_p == end_p;
    }
};

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
