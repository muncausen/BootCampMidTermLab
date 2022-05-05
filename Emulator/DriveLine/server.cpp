#include "server.hpp"

bool Server::StartEmulate(const UserInputCanFrame& can_data) {
  engine = new Engine;
  can_tranceiver = new CanTranceiver;
  bool isCanUpdated{false};
  if (can_data.frame_counter != prev_cntr) {
    cout << "Ignition: " << static_cast<int>(can_data.ignition) << endl;
    printf("S: Cntr : %d \n", can_data.frame_counter);
    printf("S: Requested Acceleration : %d \n", can_data.throttle);
    printf("S: Gear : %d \n", can_data.gear_select);
    printf("S: Brake Requested : %d \n", can_data.brake);
    printf("S: TI : %d \n", can_data.blinkers);
    engine->GearCalc(can_data.throttle, can_data.gear_select, can_data.ignition);
    uint8_t auto_gear = engine->getGear();
    // engine->Rpm(can_data.throttle, auto_gear);
    // uint8_t rpm = engine->getRpm();
    // engine->Speed(rpm, auto_gear);
    // uint8_t speed = engine->getSpeed();
    // can_data_to_disp.speed = speed;
    // can_data_to_disp.rpm = rpm;
    // can_data_to_disp.blinkers = can_data.blinkers;
    // can_data_to_disp.ignition = can_data.ignition;
    // can_data_to_disp.gear_select = auto_gear;
    // can_tranceiver->CanToDisplay(can_data_to_disp);
    // cout << "RPM in SERVER: " << static_cast<int>(engine_rpm) << endl;
    isCanUpdated = true;
    prev_cntr = can_data.frame_counter;
  } else {
    isCanUpdated = false;
  }
  return isCanUpdated;
}
