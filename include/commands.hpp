#include <string>
#include <iostream>
#include <vector>
#include "ObdCommand.hpp"
#include "ObdSerial.hpp"
#define RPM "010C\r"
#define SPEED "010D\r"
#define FUEL "012F\r"
#define DTC "03\r"
#define SDTC "0902\r"
#define ODOMB "220F00\r"
#define ODO "22F100\r"
#define OIL "015C\r"
#define TURBO_TEMP "0176\r"
using s = std::string;
s rpm(ObdSerial &s){
   return s.sendGenCommand(RPM);
}
s speed(ObdSerial &s){
    return s.sendGenCommand(SPEED);
}
s fuel(ObdSerial &s){
    return s.sendGenCommand(FUEL);
}
s dtc(ObdSerial &s){
    return s.sendGenCommand(DTC);
}
s sdtcs(ObdSerial &s){
    return s.sendGenCommand(SDTC);
}
s odo(ObdSerial &s){
    return s.sendGenCommand(ODO);
}
s oil(ObdSerial &s){
    return s.sendGenCommand(OIL);
}
s turboTemp(ObdSerial &s){
    return s.sendGenCommand(TURBO_TEMP);
}