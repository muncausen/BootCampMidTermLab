#include <curses.h>

#include <fstream>
#include <iostream>
#include <thread>

#include "ui.hpp"

int main() {
  // Initiate persistent variables.
  bool run{true};
  ui::UserInput ui{};

  ui::InitNcurses();

  // std::thread can_thread(&ui.CanSend);
  ui.StartCanSenderThread();

  // Will loop until false is returned from input check.
  while (run) {
    if ((ui.ch = getch()) != ERR) {
      run = ui.Cmd();
      ui.UpdateCanFrameBitfield();
    }
  }

  ui.StopCanSenderThread();

  int rc{};
  rc &= delwin(stdscr);
  rc &= endwin();
  return rc;
}
