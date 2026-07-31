#include "structs.h"
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>

class Solution {
public:
    // 1
    std::vector<int> twoSum(std::vector<int>& nums, int target)
    {
        std::unordered_map<int, int> um;

        for (int i = 0; i < nums.size(); i++)
        {
            int diff = target - nums[i];
            if (um.contains(diff))
                return { um[diff], i };

            um.insert_or_assign(nums[i], i);
        }
        return {0};
    }

    // 2
    ListNode* addTwoNumbers(ListNode* l1, ListNode* l2)
    {
        ListNode* head = new ListNode();

        ListNode* _head = head;
        ListNode* _l1 = l1;
        ListNode* _l2 = l2;

        int res_div = 0;

        while (_l1 != nullptr || _l2 != nullptr)
        {
            ListNode* temp = new ListNode(0);

            temp->val = ((((_l1 != nullptr ? _l1->val : 0) + (_l2 != nullptr ? _l2->val : 0)) % 10) + res_div) % 10;
            res_div = ((_l1 != nullptr ? _l1->val : 0) + (_l2 != nullptr ? _l2->val : 0) + res_div) / 10;

            _head->next = temp;
            _head = _head->next;

            _l1 = (_l1 != nullptr ? _l1->next : nullptr);
            _l2 = (_l2 != nullptr ? _l2->next : nullptr);
        };

        if (res_div != 0)
            _head->next = new ListNode(res_div);

        return head->next;
    }

    // 3
    int lengthOfLongestSubstring(std::string s)
    {
        int current_longest = 0;
        int len = s.length();
        int last_valid_index = -1;
        int chars[256];
        std::fill(chars, chars + 256, -1);

        for (int i = 0; i < len; i++)
        {
            unsigned char c = s[i];
            if (chars[c] > last_valid_index)
                last_valid_index = chars[c];

            current_longest = std::max(current_longest, i - last_valid_index);
            chars[c] = i;
        }
        return current_longest;
    }

    // 4
    double findMedianSortedArrays(std::vector<int>& nums1, std::vector<int>& nums2) {
        std::vector<int> merged = nums1;
        merged.reserve(merged.size() + nums2.size());
        merged.insert(merged.end(), nums2.begin(), nums2.end());
        std::sort(merged.begin(), merged.end());
        if (merged.size() % 2 == 1)
            return merged[merged.size() / 2];
        else
            return (((double)merged[merged.size() / 2] + merged[merged.size() / 2 - 1]) / 2);
    }

    std::string longestPalindrome(std::string s) {
        //badfdab
        //badffdab
        //asdbaadfdfdaab
        //baadfdfdaabdsa

        int s_len = s.length();

        std::unordered_map<int, std::pair<int, int>> pals;
        std::pair<int, int> longest_index_n_size = { 0 /*start index*/,1 /*length*/ };
        std::string longest_pal = std::string{ s[0] };

        for (int i = 1; i < s_len; i++)
        {
            int j = i - 1;
            for (;j >= 0 && s[j] == s[i]; --j)
                pals[i] = { j , i };

            if (j == i - 1 && i - 2 >= 0 && s[i] != s[i - 1] && s[i] == s[i - 2])
                pals[i] = { i - 2, i };

            for (auto it = pals.begin(); it != pals.end();)//ccbbddd
            {
                auto& pair = it->second;

                if (pair.second - pair.first + 1 > longest_index_n_size.second)
                    longest_index_n_size = { pair.first, pair.second - pair.first + 1 };

                if (pair.first - 1 < 0 || pair.second - 1 >= s_len || s[pair.first - 1] != s[pair.second + 1])
                {
                    it = pals.erase(it);
                    continue;
                }

                --pair.first;
                ++pair.second;

                it++;
            }
        }

        return s.substr(longest_index_n_size.first, longest_index_n_size.second);
    }
};


int main()
{
    std::cout << "Hello World!\n";
}