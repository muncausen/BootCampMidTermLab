#include <curses.h>

#include <fstream>
#include <iostream>
#include <thread>

#include "socketcan.hpp"
#include "ui.hpp"

#include <chrono>

/*!
 * \brief Populates a can frame and sends it on the CAN bus.
 *
 * \param ui The user input object containing the info to send.
 */
void SendToCan(const UserInput& ui) {
  scpp::SocketCan socket_can;

  if (socket_can.open("vcan0") != scpp::STATUS_OK) {
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    exit(-1);
  }

  while (true) {
    scpp::CanFrame cf_to_write;

    cf_to_write.id = 123;
    cf_to_write.len = 8;

    cf_to_write.data[0]++;  // put data from input here
    cf_to_write.data[1] = static_cast<uint8_t>(ui.throttle);
    cf_to_write.data[2] = static_cast<uint8_t>(ui.brake);
    cf_to_write.data[3] = static_cast<uint8_t>(ui.gear);
    cf_to_write.data[4] = 0;
    cf_to_write.data[5] = 0;
    cf_to_write.data[6] = 0;
    cf_to_write.data[7] = 0;

    auto write_sc_status = socket_can.write(cf_to_write);
    if (write_sc_status != scpp::STATUS_OK)
      printf("something went wrong on socket write, error code : %d \n", int32_t(write_sc_status));

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }

}

int main() {
  // Initiate persistent variables.
  bool run{true};
  UserInput ui{};

  InitNcurses();

  std::thread can_thread(SendToCan, std::ref(ui));

  // Will loop until false is returned from input check.
  while (run) {
    if ((ui.ch = getch()) != ERR) run = ui.Cmd(ui.ch);
  }

  can_thread.join();

  return endwin();
}
