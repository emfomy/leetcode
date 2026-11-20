// Source: https://leetcode.com/problems/implement-router
// Title: Implement Router
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Design a data structure that can efficiently manage data packets in a network router. Each data packet consists of the following attributes:
//
// - `source`: A unique identifier for the machine that generated the packet.
// - `destination`: A unique identifier for the target machine.
// - `timestamp`: The time at which the packet arrived at the router.
//
// Implement the `Router` class:
//
// `Router(int memoryLimit)`: Initializes the Router object with a fixed memory limit.
//
// - `memoryLimit` is the **maximum** number of packets the router can store at any given time.
// - If adding a new packet would exceed this limit, the **oldest** packet must be removed to free up space.
//
// `bool addPacket(int source, int destination, int timestamp)`: Adds a packet with the given attributes to the router.
//
// - A packet is considered a duplicate if another packet with the same `source`, `destination`, and `timestamp` already exists in the router.
// - Return `true` if the packet is successfully added (i.e., it is not a duplicate); otherwise return `false`.
//
// `int[] forwardPacket()`: Forwards the next packet in FIFO (First In First Out) order.
//
// - Remove the packet from storage.
// - Return the packet as an array `[source, destination, timestamp]`.
// - If there are no packets to forward, return an empty array.
//
// `int getCount(int destination, int startTime, int endTime)`:
//
// - Returns the number of packets currently stored in the router (i.e., not yet forwarded) that have the specified destination and have timestamps in the inclusive range `[startTime, endTime]`.
//
// **Note** that queries for `addPacket` will be made in increasing order of `timestamp`.
//
// **Example 1:**
//
// ```
// Input:
// ["Router", "addPacket", "addPacket", "addPacket", "addPacket", "addPacket", "forwardPacket", "addPacket", "getCount"]
// [[3], [1, 4, 90], [2, 5, 90], [1, 4, 90], [3, 5, 95], [4, 5, 105], [], [5, 2, 110], [5, 100, 110]]
//
// Output:
// [null, true, true, false, true, true, [2, 5, 90], true, 1]
//
// Explanation:
// Router router = new Router(3); // Initialize Router with memoryLimit of 3.
// router.addPacket(1, 4, 90); // Packet is added. Return True.
// router.addPacket(2, 5, 90); // Packet is added. Return True.
// router.addPacket(1, 4, 90); // This is a duplicate packet. Return False.
// router.addPacket(3, 5, 95); // Packet is added. Return True
// router.addPacket(4, 5, 105); // Packet is added, `[1, 4, 90]` is removed as number of packets exceeds memoryLimit. Return True.
// router.forwardPacket(); // Return `[2, 5, 90]` and remove it from router.
// router.addPacket(5, 2, 110); // Packet is added. Return True.
// router.getCount(5, 100, 110); // The only packet with destination 5 and timestamp in the inclusive range `[100, 110]` is `[4, 5, 105]`. Return 1.
// ```
//
// **Example 2:**
//
// ```
// Input:
// ["Router", "addPacket", "forwardPacket", "forwardPacket"]
// [[2], [7, 4, 90], [], []]
//
// Output:
// [null, true, [7, 4, 90], []]
//
// Explanation:
// Router router = new Router(2); // Initialize `Router` with `memoryLimit` of 2.
// router.addPacket(7, 4, 90); // Return True.
// router.forwardPacket(); // Return `[7, 4, 90]`.
// router.forwardPacket(); // There are no packets left, return `[]`.
// ```
//
// **Constraints:**
//
// - `2 <= memoryLimit <= 10^5`
// - `1 <= source, destination <= 2 * 10^5`
// - `1 <= timestamp <= 10^9`
// - `1 <= startTime <= endTime <= 10^9`
// - At most `10^5` calls will be made to `addPacket`, `forwardPacket`, and `getCount` methods altogether.
// - queries for `addPacket` will be made in increasing order of `timestamp`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <algorithm>
#include <deque>
#include <queue>
#include <set>
#include <tuple>
#include <unordered_set>
#include <vector>

using namespace std;

// Tree Set + Queue (TLE)
//
// Use Queue to store the order of the packets
// Use Tree Set to store if the packet is in memory
class Router {
  using Packet = tuple<int, int, int>;  // time, src, dst

  int memoryLimit;
  deque<Packet> packetQueue;
  set<Packet> packetSet;

 public:
  Router(int memoryLimit) : memoryLimit(memoryLimit) {}

  bool addPacket(int source, int destination, int timestamp) {
    // Insert
    auto packet = Packet(timestamp, source, destination);
    if (packetSet.count(packet)) return false;
    packetSet.insert(packet);
    packetQueue.push_back(packet);

    // Delete
    if (packetQueue.size() > memoryLimit) {
      forwardPacket();
    }

    return true;
  }

  vector<int> forwardPacket() {
    if (packetQueue.empty()) return {};
    auto packet = packetQueue.front();
    packetSet.erase(packet);
    packetQueue.pop_front();
    return {get<1>(packet), get<2>(packet), get<0>(packet)};
  }

  int getCount(int destination, int startTime, int endTime) {
    auto lo = lower_bound(packetQueue.cbegin(), packetQueue.cend(), Packet(startTime, 0, 0));
    auto hi = upper_bound(packetQueue.cbegin(), packetQueue.cend(), Packet(endTime + 1, 0, 0));

    return count_if(lo, hi, [=](Packet packet) -> bool { return get<2>(packet) == destination; });
  }
};

// Tree Set + Hash Map + Queue
//
// Use Queue to store the order of the packets
// Use Tree Set to store if the packet is in memory
// Use Hash Map to store timestamps for each destination
class Router2 {
  using Packet = tuple<int, int, int>;  // time, src, dst

  int memoryLimit;
  queue<Packet> packetQueue;
  set<Packet> packetSet;
  unordered_map<int, deque<int>> destTimes;

 public:
  Router2(int memoryLimit) : memoryLimit(memoryLimit) {}

  bool addPacket(int source, int destination, int timestamp) {
    // Check
    auto packet = Packet(timestamp, source, destination);
    if (packetSet.count(packet)) return false;

    // Insert
    packetSet.insert(packet);
    packetQueue.push(packet);
    destTimes[destination].push_back(timestamp);

    // Delete
    if (packetQueue.size() > memoryLimit) {
      forwardPacket();
    }

    return true;
  }

  vector<int> forwardPacket() {
    if (packetQueue.empty()) return {};
    auto packet = packetQueue.front();
    auto [time, src, dest] = packet;

    packetSet.erase(packet);
    packetQueue.pop();
    destTimes[dest].pop_front();

    return {src, dest, time};
  }

  int getCount(int destination, int startTime, int endTime) {
    if (!destTimes.count(destination)) return 0;
    auto& times = destTimes[destination];
    auto lo = lower_bound(times.cbegin(), times.cend(), startTime);
    auto hi = upper_bound(times.cbegin(), times.cend(), endTime);
    return hi - lo;
  }
};

// Hash Set + Hash Map + Queue
//
// Use Queue to store the order of the packets
// Use Hash Set to store if the packet is in memory
// Use Hash Map to store timestamps for each destination
class Router3 {
  using Packet = tuple<int, int, int>;  // time, src, dst

  struct PacketHash {
    size_t operator()(const Packet& p) const noexcept {
      auto hasher = hash<int>();
      auto seed = 0;
      seed = hash_combine(seed, hasher(get<0>(p)));
      seed = hash_combine(seed, hasher(get<1>(p)));
      seed = hash_combine(seed, hasher(get<2>(p)));
      return seed;
    }

    inline size_t hash_combine(size_t seed, size_t v) const noexcept {
      return seed * size_t(1e9 + 7) + v;  // 常見大質數
    }
  };

  int memoryLimit;
  queue<Packet> packetQueue;
  unordered_set<Packet, PacketHash> packetSet;
  unordered_map<int, deque<int>> destTimes;

 public:
  Router3(int memoryLimit) : memoryLimit(memoryLimit) {}

  bool addPacket(int source, int destination, int timestamp) {
    // Check
    auto packet = Packet(timestamp, source, destination);
    if (packetSet.count(packet)) return false;

    // Insert
    packetSet.insert(packet);
    packetQueue.push(packet);
    destTimes[destination].push_back(timestamp);

    // Delete
    if (packetQueue.size() > memoryLimit) {
      forwardPacket();
    }

    return true;
  }

  vector<int> forwardPacket() {
    if (packetQueue.empty()) return {};
    auto packet = packetQueue.front();
    auto [time, src, dest] = packet;

    packetSet.erase(packet);
    packetQueue.pop();
    destTimes[dest].pop_front();

    return {src, dest, time};
  }

  int getCount(int destination, int startTime, int endTime) {
    if (!destTimes.count(destination)) return 0;
    auto& times = destTimes[destination];
    auto lo = lower_bound(times.cbegin(), times.cend(), startTime);
    auto hi = upper_bound(times.cbegin(), times.cend(), endTime);
    return hi - lo;
  }
};
