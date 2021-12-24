#include <iostream>
#include <utility>
#include <vector>
#include <tuple>

const uint mod = 6;
const size_t length = 37;
void dfs(size_t index);
std::tuple<uint, uint> decode(size_t index);
inline size_t encode(uint row, uint col);

int main() {
  std::cout << encode(4, 0) << std::endl;
  return 0;
}

void dfs(std::vector<uint> &board, size_t index) {
  if (index == length) {
    return;
  }
  auto [r, c] = decode(index);
}

std::tuple<uint, uint> decode(size_t index) {
  uint row, col;

  if (index < 4) {
    row = 0;
    col = index;
  } else if (index < 9) {
    row = 1;
    col = index - 4;
  } else if (index < 15) {
    row = 2;
    col = index - 9;
  } else if (index < 22) {
    row = 3;
    col = index - 15;
  } else if (index < 28) {
    row = 4;
    col = index - 22 + 1;
  } else if (index < 33) {
    row = 5;
    col = index - 28 + 2;
  } else {
    row = 6;
    col = index - 33 + 3;
  }

  return std::tuple<uint, uint>(row, col);
}

inline size_t encode(uint row, uint col) {
  size_t index = -1;

  if (row == 0) {
    if (0 <= col && col <= 3) index = col;
  } else if (row == 1) {
    if (0 <= col && col <= 4) index = col + 4;
  } else if (row == 2) {
    if (0 <= col && col <= 5) index = col + 9;
  } else if (row == 3) {
    if (0 <= col && col <= 6) index = col + 15;
  } else if (row == 4) {
    if (1 <= col && col <= 6) index = col + 22 - 1;
  } else if (row == 5) {
    if (2 <= col && col <= 6) index = col + 28 - 2;
  } else if (row == 6) {
    if (3 <= col && col <= 6) index = col + 33 - 3;
  }

  return index;
}
