#include <vector>

using namespace std;

// Quick Select
//
// Find kth largest element
int quickSelect(vector<int>& nums, int k) {
  const int n = nums.size();
  if (k <= 0 || k > n) return -1;

  // Find in [lo, hi)
  int lo = 0, hi = n;
  while (true) {
    // TODO: random pivot to avoid worst-case O(n^2) on sorted input
    int pivot = nums[lo];

    // [lo, l): greater, [l, i) equal, [i, r): unknown, [r, hi): less
    int l = lo, i = lo, r = hi;
    while (i < r) {
      if (nums[i] > pivot) {
        swap(nums[i++], nums[l++]);
      } else if (nums[i] < pivot) {
        swap(nums[i], nums[--r]);
      } else {
        ++i;
      }
    }

    if (k <= l) {
      hi = l;
    } else if (k > r) {
      lo = r;
    } else {
      return pivot;
    }
  }

  return -1;  // unreachable
}
