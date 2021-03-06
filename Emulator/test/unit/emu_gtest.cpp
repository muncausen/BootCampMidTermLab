#include "emu_gtest.hpp"
#include <iostream>
#include<thread>
using namespace std;


void TestEmulator::SetUp(){
    cout << "SetUp:: " << endl;
    can_receiver_ = new CanTranceiver();
    can_receiver_->OpenCan();
    server_ = new Server();
    engine = new Engine();
    thread opencan_thread(&CanTranceiver::OpenCan, can_receiver_);
    opencan_thread.join();
while (testcfr.frame_counter == 0) {
        thread receive_can_thread(&CanTranceiver::CanReceive, can_receiver_);
        receive_can_thread.join();
        thread start_emulate(&Server::StartEmulate, server_, can_receiver_->getCanFrame());
        start_emulate.join();
        testcfr = can_receiver_->getCanFrame();
    };
}
void TestEmulator::TearDown(){
}

TEST_F(TestEmulator, CanReceived){

    EXPECT_EQ(testcfr.frame_counter, 12);
}
TEST_F(TestEmulator, carStatus){

    EXPECT_EQ(testcfr.ignition, 1);
}
// TEST_F(TestEmulator, EngineRPM){

//     EXPECT_EQ(engine->getRpm(), 150);
// }

