#include "ui.hpp"

#include <cstring>
#include <iostream>

// Initiates required setup for ncurses
void InitNcurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
}

// Command handling function
bool UserInput::Cmd(const int& ch) {
  bool run = true;

  std::cout << "\rKey value: " << ch << ":\t";

  switch (ch) {
    case key::k_Q:
    case key::k_q:
      std::cout << "Exiting\n";
      run = false;
      break;

    case key::k_0:
      this->SetThrottle(pedal::k_zero);
      break;

    case key::k_1:
      this->SetThrottle(pedal::k_ten);
      break;

    case key::k_2:
      this->SetThrottle(pedal::k_twenty);
      break;

    case key::k_3:
      this->SetThrottle(pedal::k_thirty);
      break;

    case key::k_4:
      this->SetThrottle(pedal::k_forty);
      break;

    case key::k_5:
      this->SetThrottle(pedal::k_fifty);
      break;

    case key::k_6:
      this->SetThrottle(pedal::k_sixty);
      break;

    case key::k_7:
      this->SetThrottle(pedal::k_seventy);
      break;

    case key::k_8:
      this->SetThrottle(pedal::k_eighty);
      break;

    case key::k_9:
      this->SetThrottle(pedal::k_ninety);
      break;

    case key::k_B:
    case key::k_b:
      this->SetThrottle(pedal::k_zero);  // Abort cruise control!
      this->SetBrake(pedal::k_one_hundred);
      break;

    case key::k_N:
    case key::k_n:
      this->SetBrake(pedal::k_zero);
      break;

    case key::k_F:
    case key::k_f:
      this->SetThrottle(pedal::k_one_hundred);
      break;

    case KEY_DOWN:
    case KEY_UP:
      this->SetGear(ch);
      break;

    default:
      std::cout << "Unknown command!\n";
      break;
  }

  return run;
}

void UserInput::SetIgnition(const int8_t& ig) {
  switch (ig) {
    case ignition::k_off:
      this->ignition = ignition::k_off;
      std::cout << "Ignition off.\n";
      break;

    case ignition::k_on:
      std::cout << "Ignition on.\n";
      this->ignition = ignition::k_on;
      break;

    default:
      std::cout << "Ignition error! Unknown ignition state\n";
      break;
  }
}

// Sets gear value.
void UserInput::SetGear(const int& gr) {
  if (KEY_DOWN == gr) {
    if (this->gear < static_cast<int8_t>(gear::drive)) this->gear++;
  } else if (KEY_UP) {
    if (this->gear > static_cast<int8_t>(gear::park)) this->gear--;
  } else {
    std::cout << "Gear error! Really weird gear request.\n";
  }

  switch (this->gear) {
    case static_cast<int8_t>(gear::park):
      std::cout << "Gear lever in P.\n";
      break;

    case static_cast<int8_t>(gear::reverse):
      std::cout << "Gear lever in R.\n";
      break;

    case static_cast<int8_t>(gear::neutral):
      std::cout << "Gear lever in N.\n";
      break;

    case static_cast<int8_t>(gear::drive):
      std::cout << "Gear lever in D.\n";
      break;

    default:
      std::cout << "Gear error! Really weird gear lever position.\n";
      break;
  }
}

// Sets throttle value with sanity check.
void UserInput::SetThrottle(const int8_t& th) {
  if (pedal::k_zero <= th && th <= pedal::k_one_hundred) {
    this->throttle = th;
    std::cout << "Throttle: " << static_cast<int>(this->throttle) << " %\n";
  }
}

// Sets brake value with sanity check.
void UserInput::SetBrake(const int8_t& bk) {
  if (pedal::k_zero <= bk && bk <= pedal::k_one_hundred) {
    this->brake = bk;
    std::cout << "Brake: " << static_cast<int>(this->brake) << " %\n";
  }
}
