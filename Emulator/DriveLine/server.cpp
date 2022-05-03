#include "server.hpp"

bool Server::StartEmulate(const CanFrame& can_frame){
    engine = new Engine;
    bool isCanUpdated{false};
    if (can_frame.frame_cntr != prev_cntr){
        cout << "Ignition: " << static_cast<int>(can_frame.ignition) << endl;
        printf("length : %d \n", can_frame.frame_dlc);
        printf("Cntr : %d \n", can_frame.frame_cntr);
        printf("id : %d \n", can_frame.frame_id);
        printf("Requested Acceleration : %d \n", can_frame.acceleration_req);
        printf("Gear : %d \n", can_frame.gear);
        printf("Brake Requested : %d \n", can_frame.brake_application);
        engine->Rpm(can_frame.acceleration_req);
        engine_rpm = engine->getRpm(); 
        cout << "RPM in SERVER: " << static_cast<int>(engine_rpm) << endl;
        isCanUpdated = true;
        prev_cntr = can_frame.frame_cntr;
    } else {isCanUpdated = false;}
    return isCanUpdated;
}
