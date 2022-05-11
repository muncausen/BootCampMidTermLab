#include "server.hpp"


bool Server::StartEmulate(const UserInputCanFrame& can_data) {
  //  engine = new Engine;
  //  can_tranceiver = new CanTranceiver;
bool isCanUpdated{false};
if ((can_data.frame_counter != 0) && 
(can_data.throttle != prev_throttle)) {
//     printf("S: Requested Acceleration : %d \n", can_data.throttle);
//     printf("S: CNTR : %d \n", can_data.frame_counter);
    engine->Torquerequest(can_data.throttle, can_data.ignition, can_data.gear_select/*,rpm, speed, gear*/);
    can_data_to_disp.ignition = can_data.ignition;
    can_data_to_disp.blinkers = can_data.blinkers;
    can_data_to_disp.gear_select = can_data.gear_select;
    // cout << "RPM in SERVER: " << static_cast<int>(engine_rpm) << endl;
    isCanUpdated = true;
    prev_cntr = can_data.frame_counter;
    prev_throttle = can_data.throttle;
//    PrintEngine(can_data);
  } else {
    isCanUpdated = false;
  }
  return isCanUpdated;
}

void Server::GetEngineValues(const uint16_t& rpm, const uint16_t & speed, const uint8_t& gear){
  can_data_to_disp.rpm = rpm;
  can_data_to_disp.speed = speed;
  can_data_to_disp.automatic_gear = gear;
//   printf("S::GetEngine::RPM : %d  Speed %d  GEAR  %d  \n", can_data_to_disp.rpm,  can_data_to_disp.speed, can_data_to_disp.automatic_gear);
  can_tranceiver->CanToDisplay(can_data_to_disp);
}
void Server::PrintEngine(const UserInputCanFrame& can_data) {
  cout << "Ignition: " << static_cast<int>(can_data.ignition) << endl;
  printf("S: Cntr : %d \n", can_data.frame_counter);
  printf("S: User Gear : %d \n", can_data.gear_select);
  printf("S: Brake Requested : %d \n", can_data.brake);
  printf("S: TI : %d \n", can_data.blinkers);
  printf("S: Automatic Gear : %d \n", auto_gear_);
}
