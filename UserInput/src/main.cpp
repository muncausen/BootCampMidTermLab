#include <curses.h>

#include <fstream>
#include <iostream>
#include <thread>

#include "ui.hpp"

int main() {
  // Initiate persistent variables.
  bool run{true};
  ui::UserInput ui{};
  std::mutex mx{};

  ui::InitNcurses();

  std::thread can_thread(ui::SendToCan, std::ref(ui), std::ref(mx));

  // Will loop until false is returned from input check.
  while (run) {
    if ((ui.ch = getch()) != ERR) {
      run = ui.Cmd();

      // Lock mutex and update.
      std::lock_guard<std::mutex> lk(mx);
      ui.UpdateCanFrameBitfield();
    }
  }

  can_thread.join();

  return endwin();
}
