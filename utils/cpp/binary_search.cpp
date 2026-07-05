class BinarySearch {
  bool check(int);

 public:
  // check(lo-1) = false, check(lo=hi) = true.
  int bisect(int lo, int hi) {
    while (lo < hi) {  // [lo, hi) is unknown
      int mid = lo + (hi - lo) / 2;
      if (check(mid)) {
        hi = mid;  // [lo, mid) is unknown
      } else {
        lo = mid + 1;  // [mid+1, hi) is unknown
      }
    }

    return lo;
  }
};
