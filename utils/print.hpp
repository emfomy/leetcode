#include <cstddef>
#include <cstdio>
#include <iostream>
#include <unordered_map>
#include <vector>

template <typename T, size_t N>
void print_array(std::array<T, N>& data) {
  std::cout << "[ ";
  for (auto& num : data) {
    std::cout << num << ", ";
  }
  std::cout << "]" << std::endl;
}

template <typename T>
void print_vector(std::vector<T>& data, size_t start = 0, size_t end = -1) {
  if (end == -1) end = data.size();
  std::cout << "[ ";
  for (auto i = start; i < end; i++) {
    std::cout << data[i] << ", ";
  }
  std::cout << "]" << std::endl;
}

template <typename K, typename V>
void print_unordered_map(std::unordered_map<K, V>& data) {
  std::cout << "{ ";
  for (auto& [key, value] : data) {
    std::cout << key << ": " << value << ", ";
  }
  std::cout << "}" << std::endl;
}

template <typename K, typename V>
void print_unordered_multimap(std::unordered_multimap<K, V>& data) {
  std::cout << "{ ";
  for (auto& [key, value] : data) {
    std::cout << key << ": " << value << ", ";
  }
  std::cout << "}" << std::endl;
}

template <typename K, typename V>
void print_unordered_mapmap(std::unordered_map<K, std::unordered_map<K, V>>& data) {
  std::cout << "{ ";
  for (auto& [key, value] : data) {
    std::cout << key << ": { ";
    for (auto& [key2, value2] : value) {
      std::cout << key2 << ": " << value2 << ", ";
    }
    std::cout << "}, ";
  }
  std::cout << "}" << std::endl;
}
