#include <curses.h>

#include <fstream>
#include <iostream>
#include <thread>

#include "ui.hpp"

int main() {
  // Initiate persistent variables.
  bool run{true};
  UserInput ui{};

  InitNcurses();

  std::thread can_thread(SendToCan, std::ref(ui));

  // Will loop until false is returned from input check.
  while (run) {
    if ((ui.ch = getch()) != ERR) {
      run = ui.Cmd(ui.ch);
      ui.UpdateCanFrameBitfield();
    }
  }

  can_thread.join();

  return endwin();
}
