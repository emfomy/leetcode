

#include <vector>
using namespace std;

struct Container {
  bool empty();
  void push(int);
  void pop();
  int peek();  // front / top
};

class CFS {
  using Bool = unsigned char;
  using Graph = vector<vector<int>>;  // node -> neighbor list

  // BFS: use std::queue as Container
  // DFS: use std::stack as Container

  // NOTE: The DFS version only ensures reachability,
  // since it marks all neighbors at once,
  // while recursive DFS visits one neighbor at a time.

  // Template
  bool cfs(const Graph& graph, int src, int dst) {
    if (src == dst) return true;
    const int n = graph.size();

    // Init
    vector<Bool> seen(n, false);
    Container container{};
    container.push(src);
    seen[src] = true;

    // Loop
    while (!container.empty()) {
      const int node = container.peek();
      container.pop();

      // Traverse
      for (const int next : graph[node]) {
        if (seen[next]) continue;
        if (next == dst) return true;
        seen[next] = true;
        container.push(next);
      }
    }

    return false;
  }
};
