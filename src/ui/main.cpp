#include <curses.h>
#include <thread>
#include <iostream>
#include <fstream>

#include "ui.hpp"

void SendToCan() {
  std::ofstream f;
  std::string s{"happy threading!\n"};
  f.open("file", std::ios::out);
  f.write(s.c_str(), s.size());
}


int main() {
  // Initiate persistent variables.
  bool run{true};
  UserInput ui{};
  int rc{};

  InitNcurses();

  std::thread can_thread(SendToCan);
  // SendToCan();
  // std::thread(SendToCan);
  // rc = pthread_create(&can_thread, NULL, SendToCan, ui);

  // Will loop until false is returned from input check.
  while (run) {
    if ((ui.ch = getch()) != ERR) run = ui.Cmd(ui.ch);
  }

  can_thread.join();
  
  return endwin();
}
