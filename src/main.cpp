#include <iostream>
#include "shell.hpp"
#include "ObdCommand.hpp"
#include "ObdSerial.hpp"
#include "commands.hpp"
int main(){
    Shell obdsh;
    // std::string port = "";
    // ObdSerial serial(port.c_str());
    // obdsh.addCommand("rpm", rpm(serial));
    obdsh.run();
    return 0;
}