
#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include"can_receiver.hpp"
#include <iostream>
#include "server.hpp"
#include "engine.hpp"
using namespace std;

class TestEmulator : public ::testing::Test
{
    public:
        TestEmulator() = default;
        void SetUp() override;
        void TearDown() override;
        bool UpdateCanData(CanUIData& can_frame){
            CanUIData test_cfr;
            test_cfr.frame_cntr = can_frame.frame_cntr;
            cout << "TEST:: Frame_Cntr: " << test_cfr.frame_cntr << endl;
        }
        CanTranceiver *can_receiver_ = nullptr;
        Server* server_ = nullptr;
        CanUIData testcfr;
        Engine* engine = nullptr;
        
};