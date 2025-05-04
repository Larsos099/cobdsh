#include "shell.hpp"
#include <sstream>
#include <iterator>
#include <unistd.h>
#include <sys/wait.h>

Shell::Shell() {}


Shell::~Shell() {}

void Shell::addCommand(const std::string& name, CommandFunc command) {
    commands[name] = command;
}


void Shell::run() {
    std::string input;
    while (true) {
        std::cout << "OBD2: ";
        std::getline(std::cin, input);

        if (input == "exit") {
            break;  
        }

        executeCommand(input);
    }
}


void Shell::executeCommand(const std::string& input) {
    auto args = splitInput(input);
    if (args.empty()) return;

    auto cmdIt = commands.find(args[0]);
    if (cmdIt != commands.end()) {
        cmdIt->second(args);
    } else {
        std::cerr << "Befehl nicht gefunden: " << args[0] << std::endl;
    }
}


std::vector<std::string> Shell::splitInput(const std::string& input) {
    std::istringstream stream(input);
    return {std::istream_iterator<std::string>{stream}, std::istream_iterator<std::string>{}};
}
