// Source: https://leetcode.com/problems/sliding-window-median
// Title: Sliding Window Median
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// The **median** is the middle value in an ordered integer list. If the size of the list is even, there is no middle value. So the median is the mean of the two middle values.
//
// - For examples, if `arr = [2,3,4]`, the median is `3`.
// - For examples, if `arr = [1,2,3,4]`, the median is `(2 + 3) / 2 = 2.5`.
//
// You are given an integer array `nums` and an integer `k`. There is a sliding window of size `k` which is moving from the very left of the array to the very right. You can only see the `k` numbers in the window. Each time the sliding window moves right by one position.
//
// Return the median array for each window in the original array. Answers within `10^-5` of the actual value will be accepted.
//
// **Example 1:**
//
// ```
// Input: nums = [1,3,-1,-3,5,3,6,7], k = 3
// Output: [1.00000,-1.00000,-1.00000,3.00000,5.00000,6.00000]
// Explanation:
// Window position                Median
// ---------------                -----
// [**1  3  -1**] -3  5  3  6  7        1
//  1 [**3  -1  -3**] 5  3  6  7       -1
//  1  3 [**-1  -3  5**] 3  6  7       -1
//  1  3  -1 [**-3  5  3**] 6  7        3
//  1  3  -1  -3 [**5  3  6**] 7        5
//  1  3  -1  -3  5 [**3  6  7**]       6
// ```
//
// **Example 2:**
//
// ```
// Input: nums = [1,2,3,4,2,3,1,4,2], k = 3
// Output: [2.00000,3.00000,3.00000,3.00000,2.00000,3.00000,2.00000]
// ```
//
// **Constraints:**
//
// - `1 <= k <= nums.length <= 10^5`
// - `-2^31 <= nums[i] <= 2^31 - 1`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cctype>
#include <set>
#include <vector>

using namespace std;

// Tree Set
class Solution {
  struct MedianSet {
    // size(upper) >= size(lower) >= size(upper)-1
    multiset<int, less<int>> upper;
    multiset<int, greater<int>> lower;

    void balance() {
      // Ensure size(lower) >= size(upper)-1
      while (!(lower.size() + 1 >= upper.size())) {
        auto it = upper.cbegin();
        lower.insert(*it);
        upper.erase(it);
      }

      // Ensure size(upper) >= size(lower)
      while (!(upper.size() >= lower.size())) {
        auto it = lower.cbegin();
        upper.insert(*it);
        lower.erase(it);
      }
    }

    void add(const int num) {
      if (upper.empty() || num >= *upper.cbegin()) {
        upper.insert(num);
      } else {
        lower.insert(num);
      }
      balance();
    }

    void remove(const int num) {
      auto it = upper.find(num);
      if (it != upper.cend()) {
        upper.erase(it);
      } else {
        lower.erase(lower.find(num));
      }
      balance();
    }

    double getMedian() const {
      if (upper.size() > lower.size()) {
        return double(*upper.cbegin());
      } else {
        return (double(*upper.cbegin()) + double(*lower.cbegin())) / 2;
      }
    }
  };

 public:
  vector<double> medianSlidingWindow(const vector<int>& nums, const int k) {
    const int n = nums.size();

    auto ans = vector<double>();
    ans.reserve(n - k + 1);

    auto data = MedianSet();
    for (int i = 0; i < n; ++i) {
      data.add(nums[i]);
      if (i >= k) {
        data.remove(nums[i - k]);
      }

      if (i >= k - 1) {
        ans.push_back(data.getMedian());
      }
    }

    return ans;
  }
};

// Tree Set
class Solution2 {
  struct MedianSet {
    using Item = pair<int, int>;  // number, index

    // size(upper) >= size(lower) >= size(upper)-1
    set<Item, less<Item>> upper;
    set<Item, greater<Item>> lower;

    void balance() {
      // Ensure size(lower) >= size(upper)-1
      while (!(lower.size() + 1 >= upper.size())) {
        auto it = upper.cbegin();
        lower.insert(*it);
        upper.erase(it);
      }

      // Ensure size(upper) >= size(lower)
      while (!(upper.size() >= lower.size())) {
        auto it = lower.cbegin();
        upper.insert(*it);
        lower.erase(it);
      }
    }

    void add(const Item item) {
      if (upper.empty() || item >= *upper.cbegin()) {
        upper.insert(item);
      } else {
        lower.insert(item);
      }
      balance();
    }

    void remove(const Item item) {
      upper.erase(item) || lower.erase(item);
      balance();
    }

    double getMedian() const {
      if (upper.size() > lower.size()) {
        return double(upper.cbegin()->first);
      } else {
        return (double(upper.cbegin()->first) + double(lower.cbegin()->first)) / 2;
      }
    }
  };

 public:
  vector<double> medianSlidingWindow(const vector<int>& nums, const int k) {
    const int n = nums.size();

    auto ans = vector<double>();
    ans.reserve(n - k + 1);

    auto data = MedianSet();
    for (int i = 0; i < n; ++i) {
      data.add({nums[i], i});
      if (i >= k) {
        data.remove({nums[i - k], i - k});
      }

      if (i >= k - 1) {
        ans.push_back(data.getMedian());
      }
    }

    return ans;
  }
};
