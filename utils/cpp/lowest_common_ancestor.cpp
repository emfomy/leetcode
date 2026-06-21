#include <utility>
#include <vector>

using namespace std;

// We treat parent of root as root
class LCABinaryLifting {
  constexpr static int root = 0;

  int n;
  int logn;
  vector<vector<int>> up;  // up[u][k] = 2^k level ancestor of u
  vector<int> depth;

 private:
  void dfs(int u, int parent, int d, const vector<vector<int>>& graph) {
    up[u][0] = parent;
    depth[u] = d;

    for (int k = 1; k < logn; ++k) {
      up[u][k] = up[up[u][k - 1]][k - 1];
    }

    for (int v : graph[u]) {
      if (v == parent) continue;
      dfs(v, u, d + 1, graph);
    }
  }

 public:
  // Build: O(NlogN)
  LCABinaryLifting(const vector<vector<int>>& graph) {
    n = graph.size();
    logn = bit_width(size_t(n));  // = floor(log2(n))+1
    up.assign(n, vector<int>(logn, root));
    depth.resize(n);

    dfs(root, root, 0, graph);
  }

  // Find: O(logN)
  int lca(int u, int v) const {
    // Ensure depth(u) >= depth(v)
    if (depth[u] <= depth[v]) swap(u, v);

    // Lift u to the same depth of v
    int diff = depth[u] - depth[v];
    for (int k = 0; k < logn; ++k) {
      if ((diff >> k) & 1) u = up[u][k];
    }

    // Early exit
    if (u == v) return u;

    // Jump up together
    for (int k = logn - 1; k >= 0; --k) {
      if (up[u][k] != up[v][k]) {
        u = up[u][k];
        v = up[v][k];
      }
    }

    return up[u][0];
  }
};

class LCASparseTable {
  constexpr static int root = 0;

  class SparseTable {
   public:
    SparseTable(const vector<int>& nums);
    int query(int l, int r) const;
  };

  struct EulerTour {
    int n;
    vector<int> euler;  // nodes on euler tour
    vector<int> depth;  // depths on euler tour
    vector<int> first;  // first occurring index

    void dfs(int u, int parent, int d, const vector<vector<int>>& graph) {
      if (first[u] == -1) first[u] = euler.size();
      euler.push_back(u);
      depth.push_back(d);
      for (int v : graph[u]) {
        if (v == parent) continue;
        dfs(v, u, d + 1, graph);
        euler.push_back(u);
        depth.push_back(d);
      }
    }

    EulerTour(const vector<vector<int>>& graph) : n(graph.size()), euler(), depth(), first(n, -1) {
      euler.reserve(2 * n - 1);
      depth.reserve(2 * n - 1);
      dfs(root, root, 0, graph);
    }
  };

  EulerTour tour;
  SparseTable st;

 public:
  // Build: O(NlogN)
  LCASparseTable(const vector<vector<int>>& graph) : tour(graph), st(tour.depth) {}

  // Find: O(1); depth of lca
  int lcaDepth(int u, int v) const {
    int iu = tour.first[u], iv = tour.first[v];
    if (iu > iv) swap(iu, iv);  // Ensure u is before v
    return st.query(iu, iv + 1);
  }
};
