#include "components.h"

int main() {
    set_raw_mode();

    int screen_width, screen_height;
    get_console_size(screen_width, screen_height);

    std::vector<std::string> buffer(screen_height,
                                    std::string(screen_width, ' '));

    main_screen(buffer, screen_width, screen_height);

    enable_cursor();
    clear_screen();
    reset_raw_mode();
}
