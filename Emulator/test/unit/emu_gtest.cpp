#include "emu_gtest.hpp"
#include <iostream>

using namespace std;


void TestEmulator::SetUp(){
    cout << "SetUp:: " << endl;
    can_receiver_ = new CanReceiver();
    can_receiver_->OpenCan();
    server_ = new Server();

}
void TestEmulator::TearDown(){
}

TEST_F(TestEmulator, test1){
    CanFrame testcfr;
    do {
        can_receiver_->ReceiveCan();
        testcfr = can_receiver_->getCanFrame();
    }while (testcfr.frame_cntr == 0);
    EXPECT_EQ(testcfr.frame_cntr, 12);
}
