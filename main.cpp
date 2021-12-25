#include <iostream>
#include <vector>
#include <tuple>

using index_t = std::tuple<int, int>;

const int mod = 6;
const size_t length = 37;
void dfs(std::vector<int> &board, std::vector<int> &hands, size_t index);
std::tuple<int, int> decode(size_t index);
size_t encode(int row, int col);
void flip_around(std::vector<int> &board, size_t index, int amount);
template<typename T>
void print_vector(std::vector<T> vec);

int main() {
  std::vector<int> board(length);
  std::vector<int> hands(length);
  for (size_t i = 0; i < length; i++) {
    std::cout << i << ": ";
    std::cin >> board[i];
  }

  dfs(board, hands, 0);
  return 0;
}

void dfs(std::vector<int> &board, std::vector<int> &hands, size_t index) {
  if (index == length) {
    print_vector(hands);
    return;
  }
  auto [r, c] = decode(index);
  // 右端辺での枝刈り
  if (c == 6 && r > 3 && board[encode(r - 1, c - 1)] != board[encode(r - 1, c)]) {
    return;
  }
  // 下端辺での枝刈り
  if (r == 6 && c > 3 && board[encode(r - 1, c - 1)] != board[encode(r, c - 1)]) {
    return;
  }
  // 上端、左端辺以外での枝刈り
  if (r != 0 && c != 0) {
    // 左上マスを0にするように動かす
    const int hand = (mod - board[encode(r - 1, c - 1)]) % mod;
    hands[index] = hand;
    flip_around(board, index, hand);
    dfs(board, hands, index + 1);
    flip_around(board, index, mod - hand);
  } else {
    for (int hand = 0; hand < mod; hand++) {
      hands[index] = hand;
      flip_around(board, index, hand);
      dfs(board, hands, index + 1);
      flip_around(board, index, mod - hand);
    }
  }
}

std::tuple<int, int> decode(size_t index) {
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

  return std::tuple<int, int>(row, col);
}

size_t encode(int row, int col) {
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

void flip_around(std::vector<int> &board, size_t index, int amount) {
  // 正体不明だがちゃんと最初だけ初期化処理が走る
  static std::array<std::tuple<int, int>, 7u> dpos{
    dpos[0] = { -1, -1 },
    dpos[1] = { -1, 0 },
    dpos[2] = { 0, -1 },
    dpos[3] = { 0, 0 },
    dpos[4] = { 0, 1 },
    dpos[5] = { 1, 0 },
    dpos[6] = { 1, 1 }
  };
  auto [r, c] = decode(index);
  for (const auto &[dr, dc] : dpos) {
    board[encode(r + dr, c + dc)] += amount;
    board[encode(r + dr, c + dc)] %= mod;
  }
}

index_t next(index_t index) {
  auto [r, c] = index;
  if (c - r > 3) {
    r++;
    c = std::max(r - 3, 0);
  } else {
    c++;
  }
  return { r, c };
}

template<typename T>
void print_vector(std::vector<T> vec) {
  for (const auto &v : vec) {
    std::cout << v << " ";
  }
  std::cout << std::endl;
}
