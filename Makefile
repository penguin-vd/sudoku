CXX = g++
CXXFLAGS = -Wall -Wextra -O3 -std=c++17
SRCS = ui_library.cpp sudoku.cpp components.cpp main.cpp
BUILD_DIR = build

MAIN = $(BUILD_DIR)/sudoku

.PHONY: depend clean run

all:    $(MAIN)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(MAIN): $(OBJS) | $(BUILD_DIR)
	$(CXX) $(CXXFLAGS) -o $(MAIN) $(SRCS)

clean:
	$(RM) -r $(BUILD_DIR)

depend: $(SRCS)
	makedepend $^

# DO NOT DELETE THIS LINE -- make depend needs it

