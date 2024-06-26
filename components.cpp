#include "components.h"

#include "sudoku.h"
#include "ui_library.h"

void main_screen(std::vector<std::string> &buffer, int screen_width,
                 int screen_height) {
    std::vector<std::string> options = {"Easy", "Medium", "Hard"};
    int choice = choice_popup(buffer, "Difficulty", options, screen_width);
    std::vector<styling> style_buffer;
    Sudoku sudoku;
    sudoku.generate((choice + 1) * 20);
    int x = 0;
    int y = 0;
    int board_x = (screen_width / 2) - (29 / 2);
    int board_y = (screen_height / 2) - (11 / 2);
    size_t board_width = 3 * 9 + 2;
    char ch;
    std::vector<std::string> info = {
        "Press \'0-9\' on a space to place a number,",
        "Press \'h\' to place an hint,", "Press \'r\' to reset the board,",
        "Press \'f\' to complete the board,", "Press \'q\' to quit."};
    std::string title = "Welcome to Sudoku";
    std::string difficulty = "Current Difficulty: ";
    difficulty += choice == 0 ? "Easy" : choice == 1 ? "Medium" : "Hard";
    while (true) {
        clear_screen();
        int temp_width, temp_height;
        get_console_size(temp_width, temp_height);
        if (temp_width != screen_width || temp_height != screen_height) {
            screen_width = temp_width;
            screen_height = temp_height;
            buffer = std::vector(screen_height, std::string(screen_width, ' '));
            board_x = (screen_width / 2) - (29 / 2);
            board_y = (screen_height / 2) - (11 / 2);
        } else {
            clear_buffer(buffer, screen_width);
        }
        style_buffer.clear();
        sudoku.reset_style();

        if (sudoku.is_board_completed()) {
            std::vector<std::string> y_or_n = {"Yes", "No", "Show Board"};
            int cont = 2;
            bool quit = false;
            while (cont == 2) {
                cont = choice_popup(
                    buffer, "Board Completed! Want to play another game?",
                    y_or_n, screen_width);
                if (cont == 1) {
                    quit = true;
                    break;
                }

                if (cont == 2) {
                    style_buffer.clear();
                    sudoku.reset_style();
                    clear_buffer(buffer, screen_width);
                    insert_board(buffer, style_buffer, sudoku, board_x,
                                 board_y + 1);
                    draw_buffer(buffer, style_buffer);
                    getchar();
                }
            }
            if (quit) break;

            int choice =
                choice_popup(buffer, "Difficulty", options, screen_width);
            sudoku.generate((choice + 1) * 20);
            difficulty = "Current Difficulty: ";
            difficulty += choice == 0   ? "Easy"
                          : choice == 1 ? "Medium"
                                        : "Hard";
            continue;
        }

        sudoku.highlight_number(y, x);

        int start_y = board_y - info.size();
        insert_colored(buffer, style_buffer,
                       (screen_width / 2) - (title.size() / 2), start_y - 1,
                       title, "\033[1m");
        for (size_t i = 0; i < info.size(); i++) {
            insert_colored(buffer, style_buffer,
                           (screen_width / 2) - (info[i].size() / 2),
                           start_y + i, info[i], "\033[3;36m");
        }

        insert_board(buffer, style_buffer, sudoku, board_x, board_y + 1);

        insert_colored(buffer, style_buffer,
                       (screen_width / 2) - (difficulty.size() / 2),
                       board_y + 11 + 3, difficulty, "\033[1m");
        draw_buffer(buffer, style_buffer);

        if (!wait_for_input()) continue;

        ch = getchar();
        if (ch == 27) {
            ch = getchar();
            if (ch != 91) {
                continue;
            }

            ch = getchar();
            switch (ch) {
                case 65:  // UP ARROW
                    if (y == 0) continue;
                    y--;
                    break;
                case 66:  // DOWN ARROW
                    if (y == 8) continue;
                    y++;
                    break;
                case 67:  // RIGHT ARROW
                    if (x == 8) continue;
                    x++;
                    break;
                case 68:  // LEFT ARROW
                    if (x == 0) continue;
                    x--;
                    break;
            }
        } else if (ch == 'q') {
            break;
        } else if (ch >= 48 && ch <= 57) {
            sudoku.place_number(y, x, ch - 48);
        } else if (ch == 'h') {
            sudoku.place_hint();
        } else if (ch == 'f') {
            sudoku.complete_board();
        } else if (ch == 'r') {
            std::vector<std::string> y_or_n = {"Yes", "No"};
            int cont = choice_popup(buffer, "Want to play another game?",
                                    y_or_n, screen_width);
            if (cont != 0) break;
            int choice =
                choice_popup(buffer, "Difficulty", options, screen_width);
            sudoku.generate((choice + 1) * 20);
            difficulty = "Current Difficulty: ";
            difficulty += choice == 0   ? "Easy"
                          : choice == 1 ? "Medium"
                                        : "Hard";
        }
    }
}

int choice_popup(std::vector<std::string> &buffer, const std::string message,
                 const std::vector<std::string> &options, int screen_width) {
    int width = 48;
    int height = 9;
    std::vector<std::string> center_buffer(height, std::string(width, ' '));
    std::vector<styling> style_buffer;
    int start_x = (screen_width / 2) - (width / 2);
    int start_y = (buffer.size() / 2) - (height / 2);

    char ch;
    int choice = 0;

    int middle = width / 2;
    int task_padding = 16;
    size_t max_width_task = width - task_padding;

    while (true) {
        int temp_width, temp_height;
        get_console_size(temp_width, temp_height);
        if (temp_width != screen_width) {
            screen_width = temp_width;
            buffer = std::vector(temp_height, std::string(screen_width, ' '));
            start_x = (screen_width / 2) - (width / 2);
            start_y = (buffer.size() / 2) - (height / 2);
        }
        clear_buffer(center_buffer, width);
        style_buffer.clear();

        size_t size = message.size();
        if (size < max_width_task) {
            int message_pos = middle - (size / 2);
            insert_colored(center_buffer, style_buffer, message_pos, 2, message,
                           "\033[1;38;5;99m");
        } else {
            size_t pos = 0;
            int task_offset = 0;
            const std::string task = message;
            while (size > pos) {
                std::string info = task.substr(pos, max_width_task);
                int message_pos = middle - (info.size() / 2);
                insert_colored(center_buffer, style_buffer, message_pos,
                               2 + task_offset, info, "\033[1;38;5;99m");
                pos += max_width_task;
                task_offset++;
            }
            task_offset--;
        }

        draw_horizontal_line(center_buffer, 0, width, 4, '-');

        int option_area_width = width - task_padding;
        int option_start_pos = (width - option_area_width) / 2;
        int option_space = option_area_width / options.size();

        for (size_t i = 0; i < options.size(); ++i) {
            int option_pos = option_start_pos + (option_space * i) +
                             (option_space / 2) - (options[i].size() / 2);
            insert_colored(center_buffer, style_buffer, option_pos, 6,
                           options[i],
                           static_cast<size_t>(choice) == i ? "\033[7;3m" : "");
        }

        add_border(center_buffer, width);
        for (int y = 0; y < height; y++) {
            insert_into_buffer(buffer, start_x, start_y + y, center_buffer[y]);
        }

        for (auto &style : style_buffer) {
            style.x += start_x;
            style.y += start_y;
        }

        clear_screen();
        draw_buffer(buffer, style_buffer);

        if (!wait_for_input()) continue;

        ch = getchar();
        if (ch == 27) {
            if (!kbhit()) continue;
            ch = getchar();
            ch = getchar();
            switch (ch) {
                case 67:  // RIGHT ARROW
                    choice = (choice + 1) % options.size();
                    break;
                case 68:  // LEFT ARROW
                    choice = (choice - 1 + options.size()) % options.size();
                    break;
            }
        } else if (ch == 'q') {
            choice = 0;
            break;
        } else if (ch == '\n') {
            break;
        }
    }
    return choice;
}
