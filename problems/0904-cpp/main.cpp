// Source: https://leetcode.com/problems/fruit-into-baskets
// Title: Fruit Into Baskets
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are visiting a farm that has a single row of fruit trees arranged from left to right. The trees are represented by an integer array `fruits` where `fruits[i]` is the **type** of fruit the `i^th` tree produces.
//
// You want to collect as much fruit as possible. However, the owner has some strict rules that you must follow:
//
// - You only have **two** baskets, and each basket can only hold a **single type** of fruit. There is no limit on the amount of fruit each basket can hold.
// - Starting from any tree of your choice, you must pick **exactly one fruit** from **every** tree (including the start tree) while moving to the right. The picked fruits must fit in one of your baskets.
// - Once you reach a tree with fruit that cannot fit in your baskets, you must stop.
//
// Given the integer array `fruits`, return the **maximum** number of fruits you can pick.
//
// **Example 1:**
//
// ```
// Input: fruits = [1,2,1]
// Output: 3
// Explanation: We can pick from all 3 trees.
// ```
//
// **Example 2:**
//
// ```
// Input: fruits = [0,1,2,2]
// Output: 3
// Explanation: We can pick from trees [1,2,2].
// If we had started at the first tree, we would only pick from trees [0,1].
// ```
//
// **Example 3:**
//
// ```
// Input: fruits = [1,2,3,2,2]
// Output: 4
// Explanation: We can pick from trees [2,3,2,2].
// If we had started at the first tree, we would only pick from trees [1,2].
// ```
//
// **Constraints:**
//
// - `1 <= fruits.length <= 10^5`
// - `0 <= fruits[i] < fruits.length`
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <unordered_map>
#include <utility>
#include <vector>

using namespace std;

// Use Sliding Window + Hash Map (size 3)
class Solution {
 public:
  int totalFruit(vector<int>& fruits) {
    int n = fruits.size();

    auto ans = 0;
    auto left = 0;
    unordered_map<int, int> counter;
    for (int right = 0; right < n; right++) {
      auto rFruit = fruits[right];
      counter[rFruit]++;

      while (left < right && counter.size() > 2) {
        auto lFruit = fruits[left];
        counter[lFruit]--;
        if (counter[lFruit] == 0) {
          counter.erase(counter.find(lFruit));
        }
        left++;
      }

      ans = max(ans, right - left + 1);
    }

    return ans;
  }
};

// Use Sliding Window
class Solution2 {
 public:
  int totalFruit(vector<int>& fruits) {
    int n = fruits.size();

    auto left = 0;
    auto right = 1;
    for (; right < n; right++) {
      if (fruits[left] != fruits[right]) {
        break;
      }
    }
    if (right == n) {
      return n;
    }

    auto ans = right - left + 1;
    auto lastIdx = right - 1;
    for (right++; right < n; right++) {
      auto fruit = fruits[right];

      // same as last type
      if (fruit == fruits[right - 1]) {
        ans = max(ans, right - left + 1);
        continue;
      }

      // same another type
      if (fruit == fruits[lastIdx]) {
        lastIdx = right - 1;
        ans = max(ans, right - left + 1);
        continue;
      }

      // new type
      left = lastIdx + 1;
      lastIdx = right - 1;
      ans = max(ans, right - left + 1);
    }

    return ans;
  }
};

// Use Sliding Window + Optimize
class Solution2a {
 public:
  int totalFruit(vector<int>& fruits) {
    int n = fruits.size();

    auto left = 0;
    auto right = 1;
    for (; right < n; right++) {
      if (fruits[left] != fruits[right]) {
        break;
      }
    }
    if (right == n) {
      return n;
    }

    auto ans = right - left + 1;
    auto lastIdx = right - 1;
    for (right++; right < n; right++) {
      auto fruit = fruits[right];

      if (fruit != fruits[right - 1] && fruit != fruits[lastIdx]) {
        left = lastIdx + 1;
      }

      if (fruit != fruits[right - 1]) {
        lastIdx = right - 1;
      }

      ans = max(ans, right - left + 1);
    }

    return ans;
  }
};

// Use Count
class Solution3 {
 public:
  int totalFruit(vector<int>& fruits) {
    auto fruit1 = -1;  // last fruit type
    auto fruit2 = -1;  // second last fruit type

    auto all_count = 0;   // total number of fruits
    auto last_count = 0;  // number of fruits after second last fruit

    auto ans = 0;
    for (auto fruit : fruits) {
      if (fruit == fruit1) {
        all_count++;
        last_count++;
        ans = max(ans, all_count);
        continue;
      }

      if (fruit == fruit2) {
        all_count++;
        last_count = 1;
        swap(fruit1, fruit2);
        ans = max(ans, all_count);
        continue;
      }

      all_count = last_count + 1;
      last_count = 1;
      fruit2 = fruit1;
      fruit1 = fruit;
      ans = max(ans, all_count);
    }

    return ans;
  }
};

// Use Count + Optimize
class Solution3a {
 public:
  int totalFruit(vector<int>& fruits) {
    auto fruit1 = -1;  // last fruit type
    auto fruit2 = -1;  // second last fruit type

    auto all_count = 0;   // total number of fruits
    auto last_count = 0;  // number of fruits after second last fruit

    auto ans = 0;
    for (auto fruit : fruits) {
      if (fruit == fruit1 || fruit == fruit2) {
        all_count++;
      } else {
        all_count = last_count + 1;
      }

      if (fruit == fruit1) {
        last_count++;
      } else {
        last_count = 1;
        fruit2 = fruit1;
        fruit1 = fruit;
      }

      ans = max(ans, all_count);
    }

    return ans;
  }
};
