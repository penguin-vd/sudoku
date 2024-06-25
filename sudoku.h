#ifndef SUDOKU_H
#define SUDOKU_H
#include <vector>
#include <random>
#include "ui_library.h"

class Sudoku {
public:
    Sudoku();
    void generate(int count);
    void printBoard();
    std::vector<std::vector<point>> get_board();
    void highlight_number(int row, int col);
    bool place_number(int row, int col, int num);
    bool is_board_completed();
    void reset_style();
    bool complete_board();
    bool place_hint();

private:
    std::vector<std::vector<point>> board;
    std::vector<std::vector<point>> solved_board;
    std::mt19937 rng;
    
    bool solve_board();
    void fill_diagonal();
    void fill_box(int row, int col);
    bool is_safe(int row, int col, int num);
    bool used_in_row(int row, int num);
    bool used_in_col(int col, int num);
    bool used_in_box(int box_start_row, int box_start_col, int num);
    bool fill_remaining(int i, int j);
    void remove_digits(int count);
};

#endif
