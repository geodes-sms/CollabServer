#pragma once

#include <vector>

#include "editor/Command.h"
#include "editor/CommandInfo.h"

class GraphShowCommand : public Command {
   public:
    GraphShowCommand(const CommandInfo& info) : Command(info) {}
    int exec(const std::vector<std::string>& args) override;
};

class GraphInfoCommand : public Command {
   public:
    GraphInfoCommand(const CommandInfo& info) : Command(info) {}
    int exec(const std::vector<std::string>& args) override;
};

class GraphDumpCommand : public Command {
   public:
    GraphDumpCommand(const CommandInfo& info) : Command(info) {}
    int exec(const std::vector<std::string>& args) override;
};
