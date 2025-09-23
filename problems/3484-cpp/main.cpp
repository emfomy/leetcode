// Source: https://leetcode.com/problems/design-spreadsheet
// Title: Design Spreadsheet
// Difficulty: Medium
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// A spreadsheet is a grid with 26 columns (labeled from `'A'` to `'Z'`) and a given number of `rows`. Each cell in the spreadsheet can hold an integer value between 0 and 10^5.

// Implement the `Spreadsheet` class:

// - `Spreadsheet(int rows)` Initializes a spreadsheet with 26 columns (labeled `'A'` to `'Z'`) and the specified number of rows. All cells are initially set to 0.
// - `void setCell(String cell, int value)` Sets the value of the specified `cell`. The cell reference is provided in the format `"AX"` (e.g., `"A1"`, `"B10"`), where the letter represents the column (from `'A'` to `'Z'`) and the number represents a **1-indexed** row.
// - `void resetCell(String cell)` Resets the specified cell to 0.
// - `int getValue(String formula)` Evaluates a formula of the form `"=X+Y"`, where `X` and `Y` are **either** cell references or non-negative integers, and returns the computed sum.

// **Note:** If `getValue` references a cell that has not been explicitly set using `setCell`, its value is considered 0.

// **Example 1:**

// <div class="example-block">
// Input:<br>
// ["Spreadsheet", "getValue", "setCell", "getValue", "setCell", "getValue", "resetCell", "getValue"]<br>
// [[3], ["=5+7"], ["A1", 10], ["=A1+6"], ["B2", 15], ["=A1+B2"], ["A1"], ["=A1+B2"]]

// Output:<br>
// [null, 12, null, 16, null, 25, null, 15]

// Explanation

// Spreadsheet spreadsheet = new Spreadsheet(3); // Initializes a spreadsheet with 3 rows and 26 columns<br data-end="321" data-start="318">
// spreadsheet.getValue("=5+7"); // returns 12 (5+7)<br data-end="373" data-start="370">
// spreadsheet.setCell("A1", 10); // sets A1 to 10<br data-end="423" data-start="420">
// spreadsheet.getValue("=A1+6"); // returns 16 (10+6)<br data-end="477" data-start="474">
// spreadsheet.setCell("B2", 15); // sets B2 to 15<br data-end="527" data-start="524">
// spreadsheet.getValue("=A1+B2"); // returns 25 (10+15)<br data-end="583" data-start="580">
// spreadsheet.resetCell("A1"); // resets A1 to 0<br data-end="634" data-start="631">
// spreadsheet.getValue("=A1+B2"); // returns 15 (0+15)

// **Constraints:**

// - `1 <= rows <= 10^3`
// - `0 <= value <= 10^5`
// - The formula is always in the format `"=X+Y"`, where `X` and `Y` are either valid cell references or **non-negative** integers with values less than or equal to `10^5`.
// - Each cell reference consists of a capital letter from `'A'` to `'Z'` followed by a row number between `1` and `rows`.
// - At most `10^4` calls will be made in **total** to `setCell`, `resetCell`, and `getValue`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <array>
#include <cctype>
#include <map>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

class Spreadsheet {
  vector<array<int, 26>> data;

 public:
  Spreadsheet(int rows) : data(rows + 1) {}

  void setCell(string cell, int value) {
    auto [row, col] = parseCell(cell);
    data[row][col] = value;
  }

  void resetCell(string cell) {
    auto [row, col] = parseCell(cell);
    data[row][col] = 0;
  }

  int getValue(string formula) {
    auto plusIdx = formula.find("+");
    auto cell1 = formula.substr(1, plusIdx - 1), cell2 = formula.substr(plusIdx + 1);
    auto val1 = 0, val2 = 0;

    if (isdigit(cell1[0])) {
      val1 = stoi(cell1);
    } else {
      auto [row1, col1] = parseCell(cell1);
      val1 = data[row1][col1];
    }

    if (isdigit(cell2[0])) {
      val2 = stoi(cell2);
    } else {
      auto [row2, col2] = parseCell(cell2);
      val2 = data[row2][col2];
    }

    return val1 + val2;
  }

 private:
  pair<int, int> parseCell(string cell) {
    auto col = cell[0] - 'A';
    auto row = stoi(cell.substr(1));
    return {row, col};
  }
};

#include <map>
#include <set>

#include "../../utils/cpp/print.hpp"

int main() {
  // unordered_map<int, set<int>> m;
  // m[1].insert(2);
  // m[3].insert(4);
  // auto p = [](set<int> s) { print_range(s); };
  // print_range(m, p);
  vector<set<map<int, int>>> v = {{{{1, 2}}}};
  print_range(v, [](const auto &d1) { print_range(d1, [](const auto &d2) { print_range(d2); }); });
  return 0;
}
