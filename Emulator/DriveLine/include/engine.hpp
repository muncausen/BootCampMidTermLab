#ifndef ENGINE_HPP
#define ENGINE_HPP
#include<iostream>
using namespace std;

class Engine{
    private:
        int rpm_;
    public:
        void Rpm(const uint8_t& acceleration_req);
        int getRpm() const;
};

#endif // #ifndef ENGINE_HPP