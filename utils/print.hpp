#include <cstddef>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p) {
  return os << "(" << p.first << ", " << p.second << ")";
}

template <typename T, size_t N>
void print_array(const array<T, N> data) {
  cout << "[ ";
  for (auto& num : data) {
    cout << num << ", ";
  }
  cout << "]" << endl;
}

template <typename T>
void print_vector(const vector<T> data, size_t start = 0, size_t end = -1) {
  if (end == -1) end = data.size();
  cout << "[ ";
  for (auto i = start; i < end; i++) {
    cout << data[i] << ", ";
  }
  cout << "]" << endl;
}

template <typename T>
void print_vector_vector(const vector<vector<T>> data) {
  cout << "[ ";
  for (auto& value : data) {
    cout << "[ ";
    for (auto& value2 : value) {
      cout << value2 << ", ";
    }
    cout << "], ";
  }
  cout << "]" << endl;
}

template <typename K, typename V>
void print_unordered_map(const unordered_map<K, V> data) {
  cout << "{ ";
  for (auto& [key, value] : data) {
    cout << key << ": " << value << ", ";
  }
  cout << "}" << endl;
}

template <typename K, typename V>
void print_unordered_multimap(const unordered_multimap<K, V> data) {
  cout << "{ ";
  for (auto& [key, value] : data) {
    cout << key << ": " << value << ", ";
  }
  cout << "}" << endl;
}

template <typename K, typename V>
void print_unordered_map_map(const unordered_map<K, unordered_map<K, V>> data) {
  cout << "{ ";
  for (auto& [key, value] : data) {
    cout << key << ": { ";
    for (auto& [key2, value2] : value) {
      cout << key2 << ": " << value2 << ", ";
    }
    cout << "}, ";
  }
  cout << "}" << endl;
}
