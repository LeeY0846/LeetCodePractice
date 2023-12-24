// Practice.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <string>
#include <unordered_set>
#include <map>
#include <unordered_map>

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

class Solution {
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

int main()
{
    string s{ "abba" };
    Solution sol = Solution();
    cout << sol.lengthOfLongestSubstring(s);
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
