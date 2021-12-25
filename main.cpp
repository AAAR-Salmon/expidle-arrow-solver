#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

using index_t = std::tuple<int, int>;
using board_t = std::vector<std::vector<int>>;

const int mod = 6;
const size_t board_row = 7, board_col = 7;

void dfs(board_t &board, board_t &hands, index_t index);
void flip_around(board_t &board, index_t index, int amount);
index_t next(index_t index);
bool is_in_board(index_t index);
void print_board(const board_t board);

const index_t end_index = next({ 6, 6 });

int main() {
  board_t board(board_row, std::vector<int>(board_col));
  board_t hands(board_row, std::vector<int>(board_col));
  for (index_t i = { 0, 0 }; i != end_index; i = next(i)) {
    const auto [r, c] = i;
    std::cout << r << " " << c << ": " << std::flush;
    std::cin >> board[r][c];
    board[r][c]--;
  }
  dfs(board, hands, { 0, 0 });
  return 0;
}

void dfs(board_t &board, board_t &hands, index_t index) {
  if (index == end_index) {
    print_board(hands);
    exit(0);
    return;
  }
  auto [r, c] = index;
  // 右端辺での枝刈り
  if (c == 6 && r > 3 && board[r - 1][c - 1] != board[r - 1][c]) {
    return;
  }
  // 下端辺での枝刈り
  if (r == 6 && c > 3 && board[r - 1][c - 1] != board[r][c - 1]) {
    return;
  }
  // 上端、左端辺以外での枝刈り
  if (r != 0 && c != 0) {
    // 左上マスを0にするように動かす
    const int hand = (mod - board[r - 1][c - 1]) % mod;
    hands[r][c] = hand;
    flip_around(board, index, hand);
    dfs(board, hands, next(index));
    flip_around(board, index, mod - hand);
  } else {
    for (int hand = 0; hand < mod; hand++) {
      hands[r][c] = hand;
      flip_around(board, index, hand);
      dfs(board, hands, next(index));
      flip_around(board, index, mod - hand);
    }
  }
}

void flip_around(board_t &board, index_t index, int amount) {
  // 正体不明だがちゃんと最初だけ初期化処理が走る
  static std::array<index_t, 7u> dpos{
    dpos[0] = { -1, -1 },
    dpos[1] = { -1, 0 },
    dpos[2] = { 0, -1 },
    dpos[3] = { 0, 0 },
    dpos[4] = { 0, 1 },
    dpos[5] = { 1, 0 },
    dpos[6] = { 1, 1 }
  };
  const auto [r, c] = index;
  for (const auto [dr, dc] : dpos) {
    if (!is_in_board({ r + dr, c + dc })) continue;
    board[r + dr][c + dc] += amount;
    board[r + dr][c + dc] %= mod;
  }
}

index_t next(index_t index) {
  auto [r, c] = index;
  if (c == 6 || c - r >= 3) {
    r++;
    c = std::max(r - 3, 0);
  } else {
    c++;
  }
  return { r, c };
}

bool is_in_board(index_t index) {
  auto [r, c] = index;
  return std::abs(r - 3) <= 3 && std::abs(c - 3) <= 3 && std::abs(c - r) <= 3;
}

void print_board(const board_t board) {
  for (size_t i = 0; i < board_row; i++) {
    for (size_t j = 0; j < board_col; j++) {
      if (is_in_board({ i, j })) {
        std::cout << board[i][j] << " ";
      } else {
        std::cout << "  ";
      }
    }
    std::cout << "\n";
  }
  std::cout << std::endl;
}
