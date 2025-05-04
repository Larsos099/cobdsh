#ifndef SHELL_HPP
#define SHELL_HPP

#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
#include <functional>


class Shell {
public:
    using CommandFunc = std::function<void(const std::vector<std::string>&)>;

    Shell();
    ~Shell();

    void addCommand(const std::string& name, CommandFunc command);

    void run();

private:
    std::unordered_map<std::string, CommandFunc> commands;

    void executeCommand(const std::string& input);
    std::vector<std::string> splitInput(const std::string& input);
};

#endif // SHELL_HPP
