/* ===========================================================================
 * Copyright (c) 2023, Josh W <jw48152@gmail.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * ===========================================================================
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

// typedef std::vector<std::vector<State>> board_t;

class Node {
  public:
  Node(int x, int y, int g, int h) : x(x), y(y), g(g), h(h) {
  }

  int x, y, g, h;
};

enum class State { kEmpty, kObstacle, kClosed, kPath };
// "⛰️ "
// "0 "

State CheckState(int n) {
  switch (n) {
    case 0: {
      return State::kEmpty;
    }

    case 1: {
      return State::kObstacle;
    }

    default: {
      break;
    }
  };

  return State::kEmpty;
}

std::vector<State> ParseLine(const std::string &s1);

std::string CellString(State _state) {
  switch (_state) {
    case State::kObstacle:
      return "⛰️  ";

    default:
      return " 0 ";  // kEmpty
  };
}

// void printBoard(const std::vector<std::vector<State>> &grid) {
//   for (const auto &row : grid) {
//     for (const auto &j : row) {
//       std::cout << CellString(j);
//     }
//     std::cout << std::endl;
//   }
// }

void PrintBoard(const std::vector<std::vector<State>> &grid) {
  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      std::cout << CellString(grid[i][j]);
    }

    std::cout << std::endl;
  }
}

std::vector<State> ParseLine(const std::string &s1) {
  std::istringstream iss(s1);
  std::vector<State> row;
  int n;
  char c;
  while (iss >> n >> c && c == ',') {
    State val = CheckState(n);
    row.push_back(val);
  }

  return row;
}

std::vector<std::vector<State>> ReadBoardFile(const std::string &path) {
  std::fstream file(path);
  int n;
  char c;
  std::vector<std::vector<State>> board;

  if (file) {
    std::string line;

    while (getline(file, line)) {
      std::vector<State> row = ParseLine(line);
      board.push_back(row);
    }
  }

  return board;
}

void AddToOpen(int x, int y, int g, int h,
               std::vector<std::vector<int>> openList,
               std::vector<std::vector<State>> grid) {
  // todo
  std::vector<int> new_node{x, y, g, h};
  openList.push_back(new_node);
  grid[x][y] = State::kClosed;
}

int Heuristic(int x, int y, int goal_x, int goal_y) {
  int h = std::abs(goal_x - x) + std::abs(goal_y - y);
  return h;
}

// Helper function to CellSort
bool Compare(std::vector<int> a, std::vector<int> b) {
  // [0] = x, [1] = y
  // [2] = g. [3] = h | f_Val
  return (a[2] + a[3]) > (b[2] + b[3]);
}

/**
 * Sort the two-dimensional vector of ints in descending order.
 */
void CellSort(std::vector<std::vector<int>> *v) {
  std::sort(v->begin(), v->end(), Compare);
}

bool CheckValidCell(int x, int y, std::vector<std::vector<State>> &grid) {
  // 1. Check that the (x, y) coordinate pair is on the grid.
  bool x_valid =
      (x > 0 && x <= grid.size());     // grabs the number of rows within the
                                       // grid [height of grid]
  bool y_valid =
      (y > 0 && y <= grid[0].size());  // grabs the number of elements in the
                                       // first row [number of columns]
  // since the leftmost column in the grid is 0 and the rightmost column is
  // grid[0].size() - 1

  if (x_valid && y_valid) {
    // 2. Check that the grid at (x, y) is kEmpty (this is the default case if
    // the grid cell is not kClosed or a kObstacle).
    if (grid[x][y] == State::kEmpty) {
      // If both of these conditions are true, then
      // CheckValidCell should return true. Otherwise, it should return false.
      return true;
    }
  }

  return false;
}

void ExpandNeighbors() {
  // TODO: ExpandNeighbors {

  // TODO: Get current node's data.

  // TODO: Loop through current node's potential neighbors.

  // TODO: Check that the potential neighbor's x2 and y2 values are on the grid
  // and not closed.

  // TODO: Increment g value, compute h value, and add neighbor to open list.

  // } TODO: End function
}

std::vector<std::vector<State>> Search(std::vector<std::vector<State>> grid,
                                       int start[2], int goal[2]) {
  // create empty open_list vector;
  std::vector<std::vector<int>> openList = {};

  // Initialize starting node
  int x = start[0];
  int y = start[1];
  int g = 0;
  int h = Heuristic(x, y, goal[0], goal[1]);
  // Use AddToOpen to add the starting node to the open vector
  AddToOpen(x, y, g, h, openList, grid);

  // TODO: while open vector is non empty {
  while (!openList.empty()) {
    // TODO: Sort the open list using `CellSort`, and get the current node.
    CellSort(&openList);

    // TODO: Get the x and y values from the current node,
    // and set grid[x][y] to kPath.
    auto curr = openList.back();
    openList.pop_back();  // removes the element
    x = curr[0];
    y = curr[1];
    // int x = openList[0][0];
    // int y = openList[0][1];
    grid[x][y] = State::kPath;

    // TODO: Check if you've reached the goal. If so, return grid.
    if (x == goal[0] && y == goal[1]) {
      return grid;
    }

    // If we're not done, expand search to current node's neighbors. This step
    // will be completed in a later quiz. ExpandNeighbors

  }  // End while loop

  std::cout << "No path found!" << std::endl;
  return std::vector<std::vector<State>>{};

  //
  //
  // A* Search functionality here

  /* 1. while there are still nodes in the open list */
  // while (!openList.empty()) {
  //   CellSort();  // Sorts the openlist according to h + g value

  //   /* 1.2 Get the next node from open list */
  //   /* 1.3 Return if the goal is found */
  //   ExpandNeighbors();  // Loop thru curr nodes neighbors & add valid
  //   neighbors
  //                       // to the open list
  // }

  /*
  CellSort() - sorts the open list according to the sum of h + g

  ExpandNeighbors() - loops through the current node's neighbors and calls
  appropriate functions to add neighbors to the open list

  CheckValidCell() - ensures that the potential neighbor coordinates are
  on the grid and that the cell is open

  Heuristic() - computes the distance to the goal

  AddToOpen() - adds the node to the open list and marks the grid cell as closed
  */
}

void PrintSolution() {
  // print the solution to the terminal with formating.
}

int main(void) {
  // std::vector<std::vector<State>> game_board;
  // game_board = ReadBoardFile("./1.board.txt");
  // PrintBoard(game_board);
  // Search();
  // PrintSolution();

  /* Challenge 1 */
  int init[2] = {0, 0};
  int goal[2] = {4, 5};
  auto board = ReadBoardFile("./1.board.txt");
  auto solution = Search(board, init, goal);

  return 0;
}
