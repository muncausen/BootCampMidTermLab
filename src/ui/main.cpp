#include <curses.h>

#include "ui.hpp"

int main() {
  // Initiate persistent variables.
  bool run{true};
  UserInput ui{};

  InitNcurses();

  // Will loop until false is returned from input check.
  while (run) {
    if ((ui.ch = getch()) != ERR) run = ui.Cmd(ui.ch);
  }

  return endwin();
}
