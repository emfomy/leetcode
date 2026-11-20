// Source: https://leetcode.com/problems/maximum-profit-from-trading-stocks-with-discounts
// Title: Maximum Profit from Trading Stocks with Discounts
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// You are given an integer `n`, representing the number of employees in a company. Each employee is assigned a unique ID from 1 to `n`, and employee 1 is the CEO. You are given two **1-based **integer arrays, `present` and `future`, each of length `n`, where:
//
// - `present[i]` represents the **current** price at which the `i^th` employee can buy a stock today.
// - `future[i]` represents the **expected** price at which the `i^th` employee can sell the stock tomorrow.
//
// The company's hierarchy is represented by a 2D integer array `hierarchy`, where `hierarchy[i] = [u_i, v_i]` means that employee `u_i` is the direct boss of employee `v_i`.
//
// Additionally, you have an integer `budget` representing the total funds available for investment.
//
// However, the company has a discount policy: if an employee's direct boss purchases their own stock, then the employee can buy their stock at **half** the original price (`floor(present[v] / 2)`).
//
// Return the **maximum** profit that can be achieved without exceeding the given budget.
//
// **Note:**
//
// - You may buy each stock at most **once**.
// - You **cannot** use any profit earned from future stock prices to fund additional investments and must buy only from `budget`.
//
// **Example 1:**
//
// ```
// Input: n = 2, present = [1,2], future = [4,3], hierarchy = [[1,2]], budget = 3
// Output: 5
// Explanation:
// https://assets.leetcode.com/uploads/2025/04/09/screenshot-2025-04-10-at-053641.png
// - Employee 1 buys the stock at price 1 and earns a profit of `4 - 1 = 3`.
// - Since Employee 1 is the direct boss of Employee 2, Employee 2 gets a discounted price of `floor(2 / 2) = 1`.
// - Employee 2 buys the stock at price 1 and earns a profit of `3 - 1 = 2`.
// - The total buying cost is `1 + 1 = 2 <= budget`. Thus, the maximum total profit achieved is `3 + 2 = 5`.
// ```
//
// **Example 2:**
//
// ```
// Input: n = 2, present = [3,4], future = [5,8], hierarchy = [[1,2]], budget = 4
// Output: 4
// Explanation:
// https://assets.leetcode.com/uploads/2025/04/09/screenshot-2025-04-10-at-053641.png
// - Employee 2 buys the stock at price 4 and earns a profit of `8 - 4 = 4`.
// - Since both employees cannot buy together, the maximum profit is 4.
// ```
//
// **Example 3:**
//
// ```
// Input: n = 3, present = [4,6,8], future = [7,9,11], hierarchy = [[1,2],[1,3]], budget = 10
// Output: 10
// Explanation:
// https://assets.leetcode.com/uploads/2025/04/09/image.png
// - Employee 1 buys the stock at price 4 and earns a profit of `7 - 4 = 3`.
// - Employee 3 would get a discounted price of `floor(8 / 2) = 4` and earns a profit of `11 - 4 = 7`.
// - Employee 1 and Employee 3 buy their stocks at a total cost of `4 + 4 = 8 <= budget`. Thus, the maximum total profit achieved is `3 + 7 = 10`.
// ```
//
// **Example 4:**
//
// ```
// Input: n = 3, present = [5,2,3], future = [8,5,6], hierarchy = [[1,2],[2,3]], budget = 7
// Output: 12
// Explanation:
// https://assets.leetcode.com/uploads/2025/04/09/screenshot-2025-04-10-at-054114.png
// - Employee 1 buys the stock at price 5 and earns a profit of `8 - 5 = 3`.
// - Employee 2 would get a discounted price of `floor(2 / 2) = 1` and earns a profit of `5 - 1 = 4`.
// - Employee 3 would get a discounted price of `floor(3 / 2) = 1` and earns a profit of `6 - 1 = 5`.
// - The total cost becomes `5 + 1 + 1 = 7<= budget`. Thus, the maximum total profit achieved is `3 + 4 + 5 = 12`.
// ```
//
// **Constraints:**
//
// - `1 <= n <= 160`
// - `present.length, future.length == n`
// - `1 <= present[i], future[i] <= 50`
// - `hierarchy.length == n - 1`
// - `hierarchy[i] == [u_i, v_i]`
// - `1 <= u_i, v_i <= n`
// - `u_i != v_i`
// - `1 <= budget <= 160`
// - There are no duplicate edges.
// - Employee 1 is the direct or indirect boss of every employee.
// - The input graph `hierarchy `is **guaranteed** to have no cycles.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <stack>
#include <vector>

using namespace std;

// Use DP + DFS (Stack)
//
// DP?[u][b] is the maximum profit of the u-subtree with budget b with different condition.
// DP0[u][b], u doesn't buy.
// DP1[u][b], u buy with full price.
// DP1[u][b], u buy with discount price (i.e. parent must buy).
//
// To compute DP[u][b] from childs v1, v2, v3...
// We first assume that we don't pick any child, then we will have DP[u][b] for all b.
// Next loop through v1 for all b1,
// DP[u][b] = max(DP[u][b0] + DP[v1][b1]) with b0+b1 = b.
// Do the same process for v2, v2...
class Solution {
  constexpr const static int NEG_INF = -10000;

 public:
  int maxProfit(int n, vector<int>& present, vector<int>& future, vector<vector<int>>& hierarchy, int budget) {
    // Construct graph
    auto graph = vector<vector<int>>(n);  // boss -> employees
    for (auto& pair : hierarchy) {
      auto boss = pair[0] - 1, employee = pair[1] - 1;
      graph[boss].push_back(employee);
    }

    // Prepare Stack
    auto st = stack<pair<int, bool>>();  // node, seen
    st.push({0, false});

    // Prepare DP
    auto dp0 = vector(n, vector(budget + 1, NEG_INF));
    auto dp1 = vector(n, vector(budget + 1, NEG_INF));
    auto dp2 = vector(n, vector(budget + 1, NEG_INF));

    // Loop
    auto tmp0 = vector<int>(budget + 1);
    auto tmp1 = vector<int>(budget + 1);
    auto tmp2 = vector<int>(budget + 1);
    while (!st.empty()) {
      auto [node, seen] = st.top();
      st.pop();

      // Handle DFS logic
      if (!seen) {
        st.push({node, true});
        for (auto child : graph[node]) st.push({child, false});
        continue;
      }

      // Current node
      auto price1 = present[node];
      auto price2 = present[node] / 2;
      auto profit1 = future[node] - price1;
      auto profit2 = future[node] - price2;

      // Process current node
      for (auto b = 0; b <= budget; ++b) {
        dp0[node][b] = 0;  // no profit but possible
        dp1[node][b] = (price1 <= b) ? profit1 : NEG_INF;
        dp2[node][b] = (price2 <= b) ? profit2 : NEG_INF;
      }

      // Loop through childs
      for (auto child : graph[node]) {
        for (auto b = 0; b <= budget; ++b) {
          tmp0[b] = tmp1[b] = tmp2[b] = NEG_INF;
          for (auto i = 0; i <= b; ++i) {
            // Current don't buy, child can skip or buy with full price
            tmp0[b] = max(tmp0[b], dp0[node][b - i] + max(dp0[child][i], dp1[child][i]));

            // Current buy, child can skip or buy with discount
            tmp1[b] = max(tmp1[b], dp1[node][b - i] + max(dp0[child][i], dp2[child][i]));
            tmp2[b] = max(tmp2[b], dp2[node][b - i] + max(dp0[child][i], dp2[child][i]));
          }
        }
        for (auto b = 0; b <= budget; ++b) {
          dp0[node][b] = tmp0[b];
          dp1[node][b] = tmp1[b];
          dp2[node][b] = tmp2[b];
        }
      }
    }

    return max({dp0[0][budget], dp1[0][budget]});
  }
};
