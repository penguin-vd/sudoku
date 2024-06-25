#ifndef COMPONENTS_H
#define COMPONENTS_H
#include "ui_library.h"

void main_screen(std::vector<std::string> &buffer, int screen_width,
               int screen_heigth);
int choice_popup(std::vector<std::string> &buffer, const std::string message,
                const std::vector<std::string> &options,
                 int screen_width);
#endif
