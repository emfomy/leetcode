// Source: https://leetcode.com/problems/design-in-memory-file-system
// Title: Design In-Memory File System
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Design a data structure that simulates an in-memory file system.
//
// Implement the FileSystem class:
//
// - `FileSystem()` Initializes the object of the system.
// - `List<String> ls(String path)`
//
// - If `path` is a file path, returns a list that only contains this file's name.
// - If `path` is a directory path, returns the list of file and directory names **in this directory**.
//
// The answer should in **lexicographic order**.
// - `void mkdir(String path)` Makes a new directory according to the given `path`. The given directory path does not exist. If the middle directories in the path do not exist, you should create them as well.
// - `void addContentToFile(String filePath, String content)`
//
// - If `filePath` does not exist, creates that file containing given `content`.
// - If `filePath` already exists, appends the given `content` to original content.
//
// - `String readContentFromFile(String filePath)` Returns the content in the file at `filePath`.
//
// **Example 1:**
// https://assets.leetcode.com/uploads/2021/04/28/filesystem.png
//
// ```
// Input:
// ["FileSystem", "ls", "mkdir", "addContentToFile", "ls", "readContentFromFile"]
// [[], ["/"], ["/a/b/c"], ["/a/b/c/d", "hello"], ["/"], ["/a/b/c/d"]]
//
// Output:
// [null, [], null, null, ["a"], "hello"]
//
// Explanation:
// FileSystem fileSystem = new FileSystem();
// fileSystem.ls("/");                         // return []
// fileSystem.mkdir("/a/b/c");
// fileSystem.addContentToFile("/a/b/c/d", "hello");
// fileSystem.ls("/");                         // return ["a"]
// fileSystem.readContentFromFile("/a/b/c/d"); // return "hello"
// ```
//
// **Constraints:**
//
// - `1 <= path.length,filePath.length <= 100`
// - `path` and `filePath`are absolute paths which begin with `'/'`and do not end with `'/'`except that the path is just`"/"`.
// - You can assume that all directory names and file names only contain lowercase letters, and the same names will not exist in the same directory.
// - You can assume that all operations will be passed valid parameters, and users will not attempt to retrieve file content or list a directory or file that does not exist.
// - You can assume that the parent directory for the file in `addContentToFile` will exist.
// - `1 <= content.length <= 50`
// - At most `300` calls will be made to `ls`, `mkdir`,`addContentToFile`, and`readContentFromFile`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

// Tree Map
//
// This similar to trie.
//
// Note that we skip all the checks.
// Note that parse path could use generator for better performance.
// However, we don't use it since C++'s generator is too complicated.
class FileSystem {
  struct Node {
    map<string, Node> childMap = {};  // name -> child
    string content = "";
    bool isFile = false;
  };

  Node root;

  vector<string> parsePath(const string& path) {
    istringstream iss(path);
    vector<string> segments;
    string segment;
    while (getline(iss, segment, '/')) {
      if (!segment.empty()) segments.push_back(segment);
    }
    return segments;
  }

 public:
  FileSystem() : root() {}

  vector<string> ls(const string& path) {
    const auto& segments = parsePath(path);

    // Find
    Node* node = &root;
    for (const string& segment : segments) {
      if (!node->childMap.contains(segment)) return {};
      node = &node->childMap.at(segment);
    }

    // File
    if (node->isFile) {
      return {segments.back()};
    }

    // Directory
    vector<string> names;
    names.reserve(node->childMap.size());
    for (const auto& [name, _] : node->childMap) {
      names.push_back(name);
    }
    return names;
  }

  void mkdir(const string& path) {
    Node* node = &root;
    for (const string& segment : parsePath(path)) {
      if (!node->childMap.contains(segment)) {
        node->childMap[segment] = Node{};
      }
      node = &node->childMap.at(segment);
    }
  }

  void addContentToFile(string filePath, string content) {
    Node* node = &root;
    for (const string& segment : parsePath(filePath)) {
      if (!node->childMap.contains(segment)) {
        node->childMap[segment] = Node{};
      }
      node = &node->childMap.at(segment);
    }

    // Write file
    node->isFile = true;
    node->content.append(content);
  }

  string readContentFromFile(string filePath) {
    Node* node = &root;
    for (const string& segment : parsePath(filePath)) {
      node = &node->childMap.at(segment);
    }

    return node->content;
  }
};
