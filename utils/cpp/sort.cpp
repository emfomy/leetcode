#include <algorithm>
#include <numeric>
#include <vector>

using namespace std;

// orders[rank] = original_idx
// ranks[original_idx] = order
void sortByIndex(const vector<int> &nums) {
  const int n = nums.size();

  // Sort
  auto orders = vector<int>(n);
  const auto comp = [&nums](int i, int j) -> bool { return nums[i] < nums[j]; };
  iota(orders.begin(), orders.end(), 0);
  sort(orders.begin(), orders.end(), comp);

  // Rank
  auto ranks = vector<int>(n);
  for (int i = 0; i < n; i++) {
    ranks[orders[i]] = i;
  }
}
