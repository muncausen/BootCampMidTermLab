#include "ui.hpp"

#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>

#include "socketcan.hpp"

namespace ui {

/*!
 * \brief Initiates required setup for ncurses
 *
 */
void InitNcurses() {
  initscr();
  cbreak();
  noecho();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
}

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
    cf_to_write.len = sizeof(ui.can_frame_bitfield);

    std::memcpy(cf_to_write.data, &ui.can_frame_bitfield, sizeof(ui.can_frame_bitfield));

    auto write_sc_status = socket_can.write(cf_to_write);
    if (write_sc_status != scpp::STATUS_OK)
      printf("something went wrong on socket write, error code : %d \n", int32_t(write_sc_status));

    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
// Command handling function
/*!
 * \brief Command handling function
 *
 * \param ch Character value representing the key the user pressed.
 * \return true so long as the application is supposed to run.
 * \return false when the application should stop and terminate.
 */
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
      this->SetThrottle(Pedal::kZero);
      break;

    case key::k_1:
      this->SetThrottle(Pedal::kTen);
      break;

    case key::k_2:
      this->SetThrottle(Pedal::kTwenty);
      break;

    case key::k_3:
      this->SetThrottle(Pedal::kThirty);
      break;

    case key::k_4:
      this->SetThrottle(Pedal::kForty);
      break;

    case key::k_5:
      this->SetThrottle(Pedal::kFifty);
      break;

    case key::k_6:
      this->SetThrottle(Pedal::kSixty);
      break;

    case key::k_7:
      this->SetThrottle(Pedal::kSeventy);
      break;

    case key::k_8:
      this->SetThrottle(Pedal::kEighty);
      break;

    case key::k_9:
      this->SetThrottle(Pedal::kNinety);
      break;

    case key::k_B:
    case key::k_b:
      this->SetThrottle(Pedal::kZero);  // Abort cruise control!
      this->SetBrake(Pedal::kOneHundred);
      break;

    case key::k_N:
    case key::k_n:
      this->SetBrake(Pedal::kZero);
      break;

    case key::k_F:
    case key::k_f:
      this->SetThrottle(Pedal::kOneHundred);
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

void UserInput::UpdateCanFrameBitfield() {
  this->can_frame_bitfield.frame_counter++;
  this->can_frame_bitfield.ignition = static_cast<uint>(this->ignition);
  this->can_frame_bitfield.gear_select = static_cast<uint>(this->gear_selection);
  this->can_frame_bitfield.throttle = static_cast<uint>(this->throttle);
  this->can_frame_bitfield.brake = static_cast<uint>(this->brake);
  this->can_frame_bitfield.blinkers = static_cast<uint>(this->blinker);
}

/*!
 * \brief Sets the value of ignition state.
 *
 * \param ig Ignition value from user input.
 */
void UserInput::SetIgnition(const Ignition& ig) {
  switch (ig) {
    case Ignition::kOff:
      this->ignition = Ignition::kOff;
      std::cout << "Ignition off.\n";
      break;

    case Ignition::kOn:
      std::cout << "Ignition on.\n";
      this->ignition = Ignition::kOn;
      break;

    default:
      std::cout << "Ignition error! Unknown ignition state\n";
      break;
  }
}

/*!
 * \brief Sets gear value.
 *
 * \param gr Gear value based on user input.
 */
void UserInput::SetGear(const int& gr) {
  std::string curr_gear{};

  if (KEY_DOWN == gr) {
    if (Gear::kPark == this->gear_selection) {
      this->gear_selection = Gear::kReverse;
      curr_gear = "R";
    } else if (Gear::kReverse == this->gear_selection) {
      this->gear_selection = Gear::kNeutral;
      curr_gear = "N";
    } else if (Gear::kNeutral == this->gear_selection) {
      this->gear_selection = Gear::kDrive;
      curr_gear = "D";
    }
    std::cout << "Gear lever in " << curr_gear << "\n";
  } else if (KEY_UP == gr) {
    if (Gear::kDrive == this->gear_selection) {
      this->gear_selection = Gear::kNeutral;
      curr_gear = "N";
    } else if (Gear::kNeutral == this->gear_selection) {
      this->gear_selection = Gear::kReverse;
      curr_gear = "R";
    } else if (Gear::kReverse == this->gear_selection) {
      this->gear_selection = Gear::kPark;
      curr_gear = "P";
    }
    std::cout << "Gear lever in " << curr_gear << "\n";
  } else {
    std::cout << "Gear error! Really weird gear request. This should not be possible.\n";
  }
}

/*!
 * \brief Sets throttle value with sanity check.
 *
 * \param ped Throttle value from user input.
 */
void UserInput::SetThrottle(const Pedal& ped) {
  if (Pedal::kZero <= ped && ped <= Pedal::kOneHundred) {
    this->throttle = ped;
    std::cout << "Throttle: " << static_cast<int>(this->throttle) << " %\n";
  }
}

/*!
 * \brief Sets brake value with sanity check.
 *
 * \param ped Brake value based on user input.
 */
void UserInput::SetBrake(const Pedal& ped) {
  if (Pedal::kZero <= ped && ped <= Pedal::kOneHundred) {
    this->brake = ped;
    std::cout << "Brake: " << static_cast<int>(this->brake) << " %\n";
  }
}

}  // namespace ui
