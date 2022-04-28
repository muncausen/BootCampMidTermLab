#include "server.hpp"

bool Server::UpdateCanData(CanFrame& can_frame){
    bool same_flag{false};
    if (can_frame.frame_cntr != prev_cntr){
        printf("data length : %d \n", can_frame.frame_dlc);
        printf("data Cntr : %d \n", can_frame.frame_cntr);
        printf("data id : %d \n", can_frame.frame_id);
        printf("data Requested Acceleration : %d \n", can_frame.acceleration_req);
        printf("data Gear : %d \n", can_frame.gear);
        printf("data Requested Brake : %d \n", can_frame.brake_application);
        prev_cntr = can_frame.frame_cntr;
        same_flag = true;
    } else if (same_flag) {
        cout << "Same data as received before!" << endl;
    } else { same_flag = true;}
    return true;
}

int main(){
    CanFrame* cf;
    CanReceiver *can_receiver_ = nullptr;
    can_receiver_ = new CanReceiver();
    cout << "MAIN is runing..." << endl;
    
    while (true){
    can_receiver_->ReceiveCan();
    };
    cf = can_receiver_->getCanFrame();
    printf("****data ----length : %d \n", cf->frame_dlc);

}