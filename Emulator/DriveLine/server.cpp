#include "server.hpp"

bool Server::StartEmulate(CanFrame& can_frame){
    engine = new Engine;
    bool isCanUpdated{false};
    if (can_frame.frame_cntr != prev_cntr){
        cout << "Ignition: " << static_cast<int>(can_frame.ignition) << endl;
        printf("data length : %d \n", can_frame.frame_dlc);
        printf("data Cntr : %d \n", can_frame.frame_cntr);
        printf("data id : %d \n", can_frame.frame_id);
        printf("data Requested Acceleration : %d \n", can_frame.acceleration_req);
        printf("data Gear : %d \n", can_frame.gear);
        printf("data Requested : %d \n", can_frame.brake_application);
        engine->Rpm(can_frame.acceleration_req);
        engine_rpm = engine->getRpm(); 
        cout << "RPM in SERVER: " << static_cast<int>(engine_rpm) << endl;
        isCanUpdated = true;
    } else {isCanUpdated = false;}
    return isCanUpdated;
}