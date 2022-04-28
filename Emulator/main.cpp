//#include"server.hpp"
#include"can_receiver.hpp"
#include <iostream>
#include "server.hpp"
using namespace std;

int main(){
    CanReceiver *can_receiver_ = nullptr;
    can_receiver_ = new CanReceiver();
    cout << "MAIN is runing..." << endl;
    can_receiver_->OpenCan();
    while (true){
        can_receiver_->ReceiveCan();
    };
}