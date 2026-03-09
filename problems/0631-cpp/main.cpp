// Source: https://leetcode.com/problems/design-excel-sum-formula
// Title: Design Excel Sum Formula
// Difficulty: Hard
// Author: Mu Yang <http://muyang.pro>

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Design the basic function of **Excel** and implement the function of the sum formula.
//
// Implement the `Excel` class:
// - `Excel(int height, char width)` Initializes the object with the `height` and the `width` of the sheet. The sheet is an integer matrix `mat` of size `height x width` with the row index in the range `[1, height]` and the column index in the range `['A', width]`. All the values should be **zero** initially.
// - `void set(int row, char column, int val)` Changes the value at `mat[row][column]` to be `val`.
// - `int get(int row, char column)` Returns the value at `mat[row][column]`.
// - `int sum(int row, char column, List<String> numbers)` Sets the value at `mat[row][column]` to be the sum of cells represented by `numbers` and returns the value at `mat[row][column]`. This sum formula **should exist** until this cell is overlapped by another value or another sum formula. `numbers[i]` could be on the format:
//   - `"ColRow"` that represents a single cell.
//     - For example, `"F7"` represents the cell `mat[7]['F']`.
//   - `"ColRow1:ColRow2"` that represents a range of cells. The range will always be a rectangle where `"ColRow1"` represent the position of the top-left cell, and `"ColRow2"` represents the position of the bottom-right cell.
//     - For example, `"B3:F7"` represents the cells `mat[i][j]` for `3 <= i <= 7` and `'B' <= j <= 'F'`.
//
// **Note:** You could assume that there will not be any circular sum reference.
// - For example, `mat[1]['A'] == sum(1, "B")` and `mat[1]['B'] == sum(1, "A")`.
//
// **Example 1:**
//
// ```
// Input:
// ["Excel", "set", "sum", "set", "get"]
// [[3, "C"], [1, "A", 2], [3, "C", ["A1", "A1:B2"]], [2, "B", 2], [3, "C"]]
//
// Output:
// [null, null, 4, null, 6]
//
// Explanation:
// Excel excel = new Excel(3, "C");
//  // construct a 3*3 2D array with all zero.
//  //   A B C
//  // 1 0 0 0
//  // 2 0 0 0
//  // 3 0 0 0
// excel.set(1, "A", 2);
//  // set mat[1]["A"] to be 2.
//  //   A B C
//  // 1 2 0 0
//  // 2 0 0 0
//  // 3 0 0 0
// excel.sum(3, "C", ["A1", "A1:B2"]); // return 4
//  // set mat[3]["C"] to be the sum of value at mat[1]["A"] and the values sum of the rectangle range whose top-left cell is mat[1]["A"] and bottom-right cell is mat[2]["B"].
//  //   A B C
//  // 1 2 0 0
//  // 2 0 0 0
//  // 3 0 0 4
// excel.set(2, "B", 2);
//  // set mat[2]["B"] to be 2. Note mat[3]["C"] should also be changed.
//  //   A B C
//  // 1 2 0 0
//  // 2 0 2 0
//  // 3 0 0 6
// excel.get(3, "C"); // return 6
// ```
//
// **Constraints:**
//
// - `1 <= height <= 26`
// - `'A' <= width <= 'Z'`
// - `1 <= row <= height`
// - `'A' <= column <= width`
// - `-100 <= val <= 100`
// - `1 <= numbers.length <= 5`
// - `numbers[i]` has the format `"ColRow"` or `"ColRow1:ColRow2"`.
// - At most `100` calls will be made to `set`, `get`, and `sum`.
//
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#include <cstdio>
#include <string>
#include <vector>

using namespace std;

// Compute the sum in runtime (TLE)
class Excel {
  struct Formula {
    int rowStart;
    char colStart;
    int rowEnd;
    char colEnd;

    Formula(const string& raw) {
      int count = sscanf(raw.c_str(), "%c%d:%c%d", &colStart, &rowStart, &colEnd, &rowEnd);
      if (count < 4) {
        rowEnd = rowStart;
        colEnd = colStart;
      }
    }
  };

  struct Cell {
    int val;
    vector<Formula> formulas;

    Cell(int val = 0) : val(val) {}
    Cell(const vector<string>& rawFormula) {
      formulas.reserve(rawFormula.size());
      for (const auto& rawFormula : rawFormula) {
        formulas.emplace_back(rawFormula);
      }
    }
  };

  vector<vector<Cell>> cells;

 public:
  Excel(int height, char width) : cells(height, vector<Cell>(width - 'A' + 1)) {}

  void set(int row, char column, int val) {  //
    cells[row - 1][column - 'A'] = Cell{val};
  }

  int get(int row, char column) {
    const Cell& cell = cells[row - 1][column - 'A'];

    if (cell.formulas.empty()) return cell.val;

    int val = 0;
    for (const auto& ref : cell.formulas) {
      for (int r = ref.rowStart; r <= ref.rowEnd; ++r) {
        for (char c = ref.colStart; c <= ref.colEnd; ++c) {
          val += get(r, c);
        }
      }
    }

    return val;
  }

  int sum(int row, char column, const vector<string>& numbers) {  //
    cells[row - 1][column - 'A'] = Cell{numbers};
    return get(row, column);
  }
};

// Lazy Flag
//
// We use a dirty (lazy) flag for cell update.
// For each cells, we records the cells that depends on this cell.
// When a cell updates, we run BFS/DFS to mark all its dependencies on dirty.
//
// Notes:
// Instead of storing the formula, we use the dependency matrix to compute the sum.
// Since a cell might exist in multiple formula, we count the occurrences the dependency matrix.
class Excel2 {
  struct Formula {
    int rowStart;
    char colStart;
    int rowEnd;
    char colEnd;

    Formula(const string& raw) {
      int count = sscanf(raw.c_str(), "%c%d:%c%d", &colStart, &rowStart, &colEnd, &rowEnd);
      if (count < 4) {
        rowEnd = rowStart;
        colEnd = colStart;
      }
    }
  };

  struct Cell {
    mutable bool dirty = false;
    mutable int val = 0;
    bool isFormula = false;

    void clear() {
      dirty = false;
      val = 0;
      isFormula = false;
    }
  };

  int width;
  int height;
  int size;

  vector<Cell> cells;
  vector<vector<int>> deps;  // source -> target: source depends on target (how many times)

  inline int getID(int row, char col) const {  //
    return (row - 1) * width + (col - 'A');
  }

 public:
  Excel2(int rawHeight, char rawWidth) : height(rawHeight), width(rawWidth - 'A' + 1) {
    size = height * width;
    cells.resize(size);
    deps.assign(size, vector<int>(size, 0));
  }

  int get(int row, char col) const {  //
    return get(getID(row, col));
  }

  void set(int row, char col, int val) {  //
    set(getID(row, col), val);
  }

  int sum(int row, char col, const vector<string>& formulas) {  //
    return sum(getID(row, col), formulas);
  }

 private:
  int get(int id) const {
    const Cell& cell = cells[id];

    // Update dirty value
    if (cell.dirty && cell.isFormula) {
      int val = 0;
      for (int depID = 0; depID < size; ++depID) {
        if (deps[id][depID]) val += deps[id][depID] * get(depID);
      }

      cell.val = val;
      cell.dirty = false;
    };

    return cell.val;
  }

  void set(int id, int val) {  //
    Cell& cell = cells[id];

    // Reset cell
    resetCell(id);

    // Set value
    cell.val = val;
    cell.dirty = false;
  }

  int sum(int id, const vector<string>& rawFormulas) {  //
    Cell& cell = cells[id];

    // Reset cell
    resetCell(id);

    // Parse formula
    cell.isFormula = true;
    for (const auto& rawFormula : rawFormulas) {
      Formula formula{rawFormula};
      for (int r = formula.rowStart; r <= formula.rowEnd; ++r) {
        for (char c = formula.colStart; c <= formula.colEnd; ++c) {
          int dstID = getID(r, c);
          ++deps[id][dstID];
        }
      }
    }

    // Update value
    cell.dirty = true;  // mark dirty to force update value
    return get(id);
  }

  void resetCell(int id) {
    // Mark dirty
    markDirty(id);

    // Clear cell
    cells[id].clear();

    // Clear dependencies
    for (int dstID = 0; dstID < size; ++dstID) {
      deps[id][dstID] = 0;
    }
  }

  void markDirty(int id) {
    // Escape
    if (cells[id].dirty) return;

    // Mark
    cells[id].dirty = true;

    // Propagate
    for (int srcID = 0; srcID < size; ++srcID) {
      if (deps[srcID][id]) markDirty(srcID);
    }
  }
};
