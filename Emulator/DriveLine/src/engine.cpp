#include "engine.hpp"

void Engine::Rpm(const uint8_t& acceleration_req){
    rpm_ = acceleration_req * 3;
}
int Engine::getRpm()const{
    return rpm_;
}