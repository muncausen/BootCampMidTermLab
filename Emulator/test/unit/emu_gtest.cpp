#include "emu_gtest.hpp"
#include <iostream>

using namespace std;


void TestEmulator::SetUp(){
    cout << "SetUp:: " << endl;
    can_receiver_ = new CanReceiver();
    can_receiver_->OpenCan();
    server_ = new Server();
    engine = new Engine();
while (testcfr.frame_cntr == 0) {
        can_receiver_->ReceiveCan();
        testcfr = can_receiver_->getCanFrame();
    };
}
void TestEmulator::TearDown(){
}

TEST_F(TestEmulator, CanReceived){

    EXPECT_EQ(testcfr.frame_cntr, 12);
}
TEST_F(TestEmulator, carStatus){

    EXPECT_EQ(testcfr.ignition, 1);
}
// TEST_F(TestEmulator, EngineRPM){

//     EXPECT_EQ(engine->getRpm(), 150);
// }

