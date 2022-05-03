#include "server.hpp"

bool Server::StartEmulate(const CanUIData& can_data){
    engine = new Engine;
    bool isCanUpdated{false};
    if (can_data.frame_cntr != prev_cntr){
        cout << "Ignition: " << static_cast<int>(can_data.ignition) << endl;
        printf("Cntr : %d \n", can_data.frame_cntr);
        printf("Requested Acceleration : %d \n", can_data.acceleration_req);
        printf("Gear : %d \n", can_data.gear);
        printf("Brake Requested : %d \n", can_data.brake_req);
        printf("TI : %d \n", can_data.blinkers);
        engine->Rpm(can_data.acceleration_req);
        engine_rpm = engine->getRpm(); 
        cout << "RPM in SERVER: " << static_cast<int>(engine_rpm) << endl;
        isCanUpdated = true;
        prev_cntr = can_data.frame_cntr;
    } else {isCanUpdated = false;}
    return isCanUpdated;
}
