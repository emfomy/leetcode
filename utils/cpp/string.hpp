#include <sstream>
#include <string>
#include <vector>

using namespace std;

template <typename T>
vector<string> string_split(const string &s, char delim = ' ') {
  istringstream iss(s);
  vector<string> words;
  string word;
  while (getline(iss, word, delim)) {
    words.push_back(word);
  }
  return words;
}

template <typename T>
string string_join(const vector<string> &words, char delim = ' ') {
  ostringstream oss;
  for (size_t i = 0; i < words.size(); i++) {
    if (i) oss << delim;
    oss << words[i];
  }
  return oss.str();
}
