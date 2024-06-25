#include "sudoku.h"

#include <algorithm>

using namespace std;

Sudoku::Sudoku() {
    board = vector<vector<point>>(9, vector(9, point{0, "", true}));
    random_device rd;
    rng = mt19937(rd());
}

void Sudoku::generate(int count) {
    board = vector<vector<point>>(9, vector(9, point{0, "", true}));
    fill_diagonal();
    fill_remaining(0, 3);
    remove_digits(count);
}

vector<vector<point>> Sudoku::get_board() { return board; }

void Sudoku::highlight_number(int row, int col) {
    int num = board[row][col].value;
    board[row][col].value = 0;
    board[row][col].style += "\033[1;7m";
    if (num != 0 && !is_safe(row, col, num)) {
        for (int i = 0; i < 9; i++) {
            if (board[row][col].value == num) {
                board[row][i].style += "\033[1;7m";
            }
            if (board[i][col].value == num) {
                board[i][col].style += "\033[1;7m";
            }
        }

        int box_row = row - row % 3;
        int box_col = col - col % 3;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (board[i + box_row][j + box_col].value == num) {
                    board[i + box_row][j + box_col].style += "\033[1;7m";
                }
            }
        }
    }
    board[row][col].value = num;
}

bool Sudoku::place_number(int row, int col, int num) {
    if (board[row][col].is_permanent) {
        return false;
    }
    board[row][col].value = num;
    return true;
}

bool Sudoku::is_board_completed() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            int num = board[row][col].value;
            if (num == 0) return false;
            board[row][col].value = 0;
            if (!is_safe(row, col, num)) {
                board[row][col].value = num;
                return false;
            }
            board[row][col].value = num;
        }
    }
    return true;
}

void Sudoku::reset_style() {
    for (int row = 0; row < 9; row++) {
        for (int col = 0; col < 9; col++) {
            board[row][col].style = "";
            int num = board[row][col].value;
            board[row][col].value = 0;
            if (board[row][col].is_permanent) {
                board[row][col].style = "\033[2m";
            } else if (num == 0) {
                board[row][col].style = "\033[1;96m";
            } else if (is_safe(row, col, num)) {
                board[row][col].style = "\033[1;92m";
            } else {
                board[row][col].style = "\033[1;91m";
            }
            board[row][col].value = num;
        }
    }
}

void Sudoku::fill_diagonal() {
    for (int i = 0; i < 9; i += 3) fill_box(i, i);
}

void Sudoku::fill_box(int row, int col) {
    vector<int> num(9);
    iota(num.begin(), num.end(), 1);
    shuffle(num.begin(), num.end(), rng);

    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[row + i][col + j].value = num[i * 3 + j];
}

bool Sudoku::is_safe(int row, int col, int num) {
    return !used_in_row(row, num) && !used_in_col(col, num) &&
           !used_in_box(row - row % 3, col - col % 3, num);
}

bool Sudoku::used_in_row(int row, int num) {
    for (int col = 0; col < 9; ++col)
        if (board[row][col].value == num) return true;
    return false;
}

bool Sudoku::used_in_col(int col, int num) {
    for (int row = 0; row < 9; ++row)
        if (board[row][col].value == num) return true;
    return false;
}

bool Sudoku::used_in_box(int box_start_row, int box_start_col, int num) {
    for (int row = 0; row < 3; ++row)
        for (int col = 0; col < 3; ++col)
            if (board[row + box_start_row][col + box_start_col].value == num)
                return true;
    return false;
}

bool Sudoku::complete_board() { return fill_remaining(0, 0); }

bool Sudoku::solve_board() {
    solved_board = board;
    return fill_remaining(0, 0);
}

bool Sudoku::place_hint() {
    std::vector<std::vector<point>> temp = board;
    if (!fill_remaining(0, 0)) return false;

    std::vector<std::pair<int, int>> emptyCells;
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            if (temp[i][j].value == 0) {
                emptyCells.emplace_back(i, j);
            }
        }
    }

    if (emptyCells.empty()) {
        return false;
    }
    std::shuffle(emptyCells.begin(), emptyCells.end(), rng);

    auto [row, col] = emptyCells.front();
    temp[row][col].value = board[row][col].value;
    board = temp;

    return true;
}

bool Sudoku::fill_remaining(int row, int col) {
    if (row == 8 && col == 9) return true;

    if (col == 9) {
        row++;
        col = 0;
    }

    if (board[row][col].value > 0) {
        return fill_remaining(row, col + 1);
    }

    for (int num = 1; num <= 9; num++) {
        if (is_safe(row, col, num)) {
            board[row][col].value = num;
            if (fill_remaining(row, col + 1)) {
                return true;
            }
        }
        board[row][col].value = 0;
    }

    return false;
}

void Sudoku::remove_digits(int count) {
    while (count != 0) {
        int cellId = rand() % 81;
        int i = cellId / 9;
        int j = cellId % 9;
        if (board[i][j].value != 0) {
            board[i][j].value = 0;
            board[i][j].is_permanent = false;
            count--;
        }
    }
}
