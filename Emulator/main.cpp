//#include"server.hpp"
#include"can_receiver.hpp"
#include <iostream>
#include "server.hpp"
#include<thread>
using namespace std;

int main(){
    CanReceiver *can_receiver_ = nullptr;
    can_receiver_ = new CanReceiver();
     Server *server_ = nullptr;
     server_ = new Server;
    cout << "MAIN is runing..." << endl;
    thread opencan_thread(&CanReceiver::OpenCan, can_receiver_);
    opencan_thread.join();
    while (true){
        thread receive_can_thread(&CanReceiver::ReceiveCan, can_receiver_);
        receive_can_thread.join();
        thread start_emulate(&Server::StartEmulate, server_, can_receiver_->getCanFrame());
        start_emulate.join();
    }
}