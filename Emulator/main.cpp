//#include"server.hpp"
#include"can_receiver.hpp"
#include <iostream>
#include "server.hpp"
#include<thread>
using namespace std;

int main(){
    CanTranceiver *can_tranceiver_ = nullptr;
    can_tranceiver_ = new CanTranceiver();
     Server *server_ = nullptr;
     server_ = new Server;
    cout << "MAIN is runing..." << endl;
    thread opencan_thread(&CanTranceiver::OpenCan, can_tranceiver_);
    opencan_thread.join();
    while (true){
        thread receive_can_thread(&CanTranceiver::CanFromUI, can_tranceiver_);
//        printf("Cntr : %d \n", can_tranceiver_->getCanFrame().frame_cntr);
        receive_can_thread.join();
        thread start_emulate(&Server::StartEmulate, server_, can_tranceiver_->getCanFrame());
        start_emulate.join();
    }
}