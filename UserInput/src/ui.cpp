#include "ui.hpp"

#include <chrono>
#include <cstring>
#include <iostream>
#include <thread>

#include "socketcan.hpp"

namespace ui {

/*!
 * \brief Initiates required setup for ncurses.
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
 * \param run[in] Boolean for exitinf while loop.
 * \param uibf[in] The user input bitfield containing data to send.
 * \param mx[in] Mutex to not conflict with main thread.
 */
void SendToCan(const bool& run, const UserInputCanFrame& uibf, std::mutex& mx) {
  scpp::SocketCan socket_can;

  if (socket_can.open("vcan0") != scpp::STATUS_OK) {
    std::cout << "Cannot open vcan0." << std::endl;
    std::cout << "Check whether the vcan0 interface is up!" << std::endl;
    return;
  }

  while (run) {
    scpp::CanFrame cf_to_write;

    cf_to_write.id = 123;
    cf_to_write.len = sizeof(uibf);

    // Lock mutex and update.
    {
      std::lock_guard<std::mutex> lk(mx);
      std::memcpy(cf_to_write.data, &uibf, sizeof(uibf));
    }

    auto write_sc_status = socket_can.write(cf_to_write);
    if (write_sc_status != scpp::STATUS_OK) {
      printf("something went wrong on socket write, error code : %d \n", int32_t(write_sc_status));
    }

    // Send CAN frame periodically.
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}

/*!
 * \brief Command handling function.
 *
 * \return true so long as the application is supposed to run.
 * \return false when the application should stop and terminate.
 */
bool UserInput::Cmd() {
  bool run = true;

  std::cout << "\rKey value: " << this->ch << ":\t";

  switch (this->ch) {
    case key::k_Q:
    case key::k_q:
      std::cout << "Exiting\n";
      run = false;
      break;

    case key::k_S:
    case key::k_s:
      this->SetIgnition();

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

    case key::k_comma:
      this->SetBrake(Pedal::kZero);
      break;

    case key::k_period:
    case key::k_B:
    case key::k_b:
      this->SetThrottle(Pedal::kZero);  // Abort cruise control!
      this->SetBrake(Pedal::kOneHundred);
      break;

    case key::k_D:
    case key::k_d:
      this->SetGear(Gear::kDrive);
      break;

    case key::k_N:
    case key::k_n:
      this->SetGear(Gear::kNeutral);
      break;

    case key::k_F:
    case key::k_f:
      this->SetThrottle(Pedal::kOneHundred);  // Full speed ahead!
      break;

    case key::k_P:
    case key::k_p:
      this->SetGear(Gear::kPark);
      break;

    case key::k_R:
    case key::k_r:
      this->SetGear(Gear::kReverse);
      break;

    case KEY_DOWN:
      this->SetGear(Gear::kNext);
      break;

    case KEY_UP:
      this->SetGear(Gear::kPrevious);
      break;

    default:
      std::cout << "Unknown command!\n";
      break;
  }

  return run;
}

/*!
 * \brief Increment frame counter and updates the bitfield data from the private variables.
 */
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
 */
void UserInput::SetIgnition() {
  switch (this->ignition) {
    case Ignition::kOff:
      this->ignition = Ignition::kOn;
      std::cout << "Ignition on.\n";
      break;

    case Ignition::kOn:
      this->ignition = Ignition::kOff;
      std::cout << "Ignition off.\n";
      break;

    default:
      std::cout << "Ignition error! Unknown ignition state.\n";
      break;
  }
}

/*!
 * \brief Sets gear value.
 *
 * \param gr Gear value based on user input.
 */
void UserInput::SetGear(const Gear& gr) {
  std::string curr_gear{};

  switch (gr) {
    case Gear::kPark:
      this->gear_selection = Gear::kPark;
      std::cout << "Gear lever in Park.\n";
      break;

    case Gear::kReverse:
      this->gear_selection = Gear::kReverse;
      std::cout << "Gear lever in Reverse.\n";
      break;

    case Gear::kNeutral:
      this->gear_selection = Gear::kNeutral;
      std::cout << "Gear lever in Neutral.\n";
      break;

    case Gear::kDrive:
      this->gear_selection = Gear::kDrive;
      std::cout << "Gear lever in Drive.\n";
      break;

    case Gear::kNext:
      if (Gear::kPark == this->gear_selection) {
        this->gear_selection = Gear::kReverse;
        std::cout << "Gear lever in Reverse.\n";
      } else if (Gear::kReverse == this->gear_selection) {
        this->gear_selection = Gear::kNeutral;
        std::cout << "Gear lever in Neutral.\n";
      } else if (Gear::kNeutral == this->gear_selection) {
        this->gear_selection = Gear::kDrive;
        std::cout << "Gear lever in Drive.\n";
      } else {
        std::cout << "Gear lever no change.\n";
        break;
      }
      break;

    case Gear::kPrevious:
      if (Gear::kDrive == this->gear_selection) {
        this->gear_selection = Gear::kNeutral;
        std::cout << "Gear lever in Neutral.\n";
      } else if (Gear::kNeutral == this->gear_selection) {
        this->gear_selection = Gear::kReverse;
        std::cout << "Gear lever in Reverse.\n";
      } else if (Gear::kReverse == this->gear_selection) {
        this->gear_selection = Gear::kPark;
        std::cout << "Gear lever in Park.\n";
      } else {
        std::cout << "Gear lever no change.\n";
        break;
      }
      break;

    default:
      std::cout << "Gear error! Really weird gear request. This should not be possible.\n";
      break;
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
