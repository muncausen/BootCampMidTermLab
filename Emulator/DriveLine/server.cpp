#include "server.hpp"

bool Server::StartEmulate(const UserInputCanFrame& can_data) {
  //  engine = new Engine;
  //  can_tranceiver = new CanTranceiver;
  bool isCanUpdated{false};
  if (can_data.frame_counter != prev_cntr) {
    engine->GearCalc(can_data.throttle, can_data.gear_select, can_data.ignition, can_data.brake);
    auto_gear_ = engine->getGear();
    // engine->Rpm(can_data.throttle, auto_gear);
    // uint8_t rpm = engine->getRpm();
    // engine->Speed(rpm, auto_gear);
    // uint8_t speed = engine->getSpeed();
    // can_data_to_disp.speed = speed;
    // can_data_to_disp.rpm = rpm_;
    // can_data_to_disp.blinkers = can_data.blinkers;
    // can_data_to_disp.ignition = can_data.ignition;
    can_data_to_disp.gear_select = auto_gear_;
    can_tranceiver->CanToDisplay(can_data_to_disp);
    // cout << "RPM in SERVER: " << static_cast<int>(engine_rpm) << endl;
    isCanUpdated = true;
    prev_cntr = can_data.frame_counter;
    PrintEngine(can_data);
  } else {
    isCanUpdated = false;
  }
  return isCanUpdated;
}
void Server::PrintEngine(const UserInputCanFrame& can_data) {
  cout << "Ignition: " << static_cast<int>(can_data.ignition) << endl;
  //  printf("S: Cntr : %d \n", can_data.frame_counter);
  printf("S: Requested Acceleration : %d \n", can_data.throttle);
  printf("S: User Gear : %d \n", can_data.gear_select);
  printf("S: Brake Requested : %d \n", can_data.brake);
  printf("S: TI : %d \n", can_data.turn_indicator);
  printf("S: Automatic Gear : %d \n", auto_gear_);
}