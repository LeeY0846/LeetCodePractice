// Practice.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。

#include <iostream>
#include <string>
#include <unordered_set>
#include <map>
#include <unordered_map>
#include <vector>
#include <queue>

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
        if (p1 < (int)nums1.size() && p2 < (int)nums2.size()) {
            return nums1[p1] < nums2[p2] ? nums1[p1++] : nums2[p2++];
        }
        else if (p1 < (int)nums1.size()) {
            return nums1[p1++];
        }
        else if (p2 < (int)nums2.size()) {
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


class Solution_Open_The_Lock {
public:
    int openLock(vector<string>& deadends, string target) {
        if (target == "0000") return 0;
        unordered_map<string, string> hash = unordered_map<string, string>();
        queue<string> q = queue<string>();
        q.push("0000");
        for (auto iter = deadends.cbegin(); iter != deadends.cend(); iter++) {
            hash[*iter] = "00";
        }
        if (hash.find("0000") == hash.cend()) {
            hash["0000"] = "00";
        }
        else return -1;
        int step_count = 0;
        string this_node;
        string last_node = "00";
        while (!q.empty()) {
            this_node = q.front();
            q.pop();
            bool target_founded = find_nearby(hash, q, this_node, target);
            if (target_founded) return count_steps(hash, target);
        }
        return -1;
    }

    bool find_nearby(unordered_map<string, string>& hash, queue<string>& q, const string& code, const string& target) {
        string temp = string{ code };
        for (int i = 0; i != 4; i++) {
            vector<char> nearby = find_char_nearby(code[i]);
            for (int j = 0; j != 2; j++) {
                temp[i] = nearby[j];
                if (hash.find(temp) == hash.cend()) {
                    q.push(temp);
                    hash[temp] = code;
                }
                if (temp == target) {
                    return true;
                }
            }
            temp[i] = code[i];
        }
        return false;
    }

    vector<char> find_char_nearby(const char c) {
        vector<char> res;
        res.reserve(2);
        if (c == '0') {
            res.emplace_back('9');
            res.emplace_back('1');
        }
        else if (c == '9') {
            res.emplace_back('0');
            res.emplace_back('8');
        }
        else {
            res.emplace_back(c - 1);
            res.emplace_back(c + 1);
        }
        return res;
    }

    int count_steps(unordered_map<string, string>&hash, const string & target) {
        int steps = 0;
        string this_node = target;
        while (true) {
            this_node = hash[this_node];
            steps++;
            if (this_node == "0000") {
                return steps;
            }
        }
        return -1;
    }
};

class Solution_91_recursion_slow {
public:
    unordered_map<string, int> hash = unordered_map<string, int>();

    int numDecodings(string s) {
        if (hash.find(s) != hash.cend()) return hash[s];
        if (s.size() >= 2) {
            int res = (check_decode_available(s.substr(0, 1)) ? 1 : 0) * numDecodings(s.substr(1, s.size() - 1))
                + (check_decode_available(s.substr(0, 2)) ? 1 : 0) * numDecodings(s.substr(2, s.size() - 2));
            hash[s] = res;
            return res;
        }
        else if (s.size() == 1) {
            int res = check_decode_available(s) ? 1 : 0;
            hash[s] = res;
            return res;
        }
        else return 1; // s.size() == 0
    }

    bool check_decode_available(string s) {
        // the size of s is not greater than 2
        if (s.size() == 1) {
            return s[0] > '0' && s[0] <= '9';
        }
        else {
            return s >= "10" && s <= "26";
        }
    }
};

class Solution_1155_just_use_a_2D_array_not_a_hashmap {
public:

    const int mod = (int)pow(10, 9) + 7;

    struct Key {
        int dices;
        int target;
        Key(int _dices, int _target) :dices(_dices), target(_target) {}

        bool operator<(const Key& other) const {
            if (dices < other.dices) return true;
            else if (dices > other.dices) return false;
            if (target < other.target) return true;
            else return false;
        }
    };

    struct HashFunc
    {
        std::size_t operator()(const Key& key) const
        {
            using std::size_t;
            using std::hash;

            return ((hash<int>()(key.dices)
                ^ (hash<int>()(key.target) << 1)) >> 1);
        }
    };

    struct EqualKey
    {
        bool operator () (const Key& lhs, const Key& rhs) const
        {
            return lhs.dices == rhs.dices
                && lhs.target == rhs.target;
        }
    };

    unordered_map<Key, long long, HashFunc, EqualKey> dp = unordered_map<Key, long long, HashFunc, EqualKey>();

    long long numRollsToTarget(int n, int k, int target) {
        if (target == 0 && n == 0) return 1;
        if (n == 0 || target <= 0) return 0;

        Key new_key = Key(n, target);
        if (dp.find(new_key) != dp.cend()) {
            return dp[new_key];
        }
        long long count = helper(n, k, target);
        return dp[new_key] = count;
    }

    long long helper(int n, int k, int target) {
        // int count = min(target, k);
        long long sum = 0;
        for (int i = 1; i <= k; i++) {
            sum += numRollsToTarget(n - 1, k, target - i) % mod;
        }
        return sum % mod;
    }
};

class Solution_6 {
public:
    string longestPalindrome(string s) {
        if (s.size() == 1) return s;
        size_t n = s.size();
        vector<vector<bool>> table = vector<vector<bool>>(n, vector<bool>(n, false));
        auto ans = make_pair(0, 0);

        for (size_t i = 0; i != n; i++) {
            table[i][i] = true;
        }

        for (size_t i = 0; i != n - 1; i++) {
            if (s[i] == s[i + 1]) {
                table[i][i + 1] = true;
                ans.first = i;
                ans.second = i + 1;
            }
        }

        for (size_t diff = 2; diff != n; diff++) {
            for (size_t i = 0; i < n - diff; i++) {
                int j = i + diff;
                if (s[i] == s[j] && table[i + 1][j - 1]) {
                    table[i][j] = true;
                    ans.first = i;
                    ans.second = j;
                }
            }
        }
        return s.substr(ans.first, ans.second - ans.first + 1);
    }
};

class Solution_1531_dp_need_review {
public:
    int dp[101][101];
    int dfs(string& s, int left, int K) {
        int k = K;
        if (s.size() - left <= k) return 0;
        if (dp[left][k] >= 0) return dp[left][k];
        int res = k ? dfs(s, left + 1, k - 1) : 10000, c = 1;
        for (int i = left + 1; i <= s.size(); ++i) {
            res = min(res, dfs(s, i, k) + 1 + (c >= 100 ? 3 : (c >= 10 ? 2 : (c > 1 ? 1 : 0))));
            if (i == s.size()) break;
            if (s[i] == s[left]) ++c;
            else if (--k < 0) break;
        }
        return dp[left][K] = res;
    }

    int getLengthOfOptimalCompression(string s, int k) {
        memset(dp, -1, sizeof(dp));
        return dfs(s, 0, k);
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

int main()
{
    cout << "Hello" << endl;
}