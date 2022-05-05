#ifndef ENGINE_HPP
#define ENGINE_HPP
#include<iostream>
#include<cstdio>
#include<ctime>
using namespace std;

class Engine{
    private:
        uint8_t rpm_{0};
        uint8_t speed_{0};
        uint8_t gear_{0};
    public:
    // RPM is a variable of throtle and Gear
        void Rpm(const uint8_t&, const uint8_t&);
    // speed is a variable of Rpm, Gear and if car is in movable mode(gear&ignition)
    //if gear != 0 means ignotion = kOn
        void Speed(const uint8_t&, const uint8_t&);
        //if Ignition is kOn the:
    //Gear is auto, we assume the load is constant 
    //if gear is higer than kPark then will increas constantly in time a max.
        void GearCalc(const uint8_t&, const uint8_t&, const uint8_t&);
        uint8_t getRpm() const;
        uint8_t getSpeed()const;
        uint8_t getGear()const;

};
void Delay(const clock_t&);
#endif // #ifndef ENGINE_HPP