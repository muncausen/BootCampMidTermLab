#include "ui.hpp"

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
      this->SetThrottle(pedal::k_zero); // Abort cruise control!
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

// Sets throttle value with sanity check.
void UserInput::SetThrottle(const int8_t& th) {
  if (pedal::k_zero <= th && th <= pedal::k_one_hundred) {
    this->current_values.throttle = th;
    std::cout << "Throttle: " << static_cast<int>(this->current_values.throttle) << " %\n";
  }
}

// Sets brake value with sanity check.
void UserInput::SetBrake(const int8_t& bk) {
  if (pedal::k_zero <= bk && bk <= pedal::k_one_hundred) {
    this->current_values.brake = bk;
    std::cout << "Brake: " << static_cast<int>(this->current_values.brake) << " %\n";
  }
}

// Sets gear value.
void UserInput::SetGear(const int& gr) {
  if (KEY_DOWN == gr) {
    if (this->current_values.gear > gear::k_drive) this->current_values.gear--;
  } else if (KEY_UP) {
    if (this->current_values.gear < gear::k_park) this->current_values.gear++;
  } else {
    std::cout << "Gear error! Really weird gear request.\n";
  }

  switch (this->current_values.gear) {
    case gear::k_park:
      std::cout << "Gear lever in P.\n";
      break;

    case gear::k_reverse:
      std::cout << "Gear lever in R.\n";
      break;

    case gear::k_neutral:
      std::cout << "Gear lever in N.\n";
      break;

    case gear::k_drive:
      std::cout << "Gear lever in D.\n";
      break;

    default:
      std::cout << "Gear error! Really weird gear lever position.\n";
      break;
  }
}
