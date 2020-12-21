#pragma once

#include <vector>

#include "editor/Command.h"
#include "editor/CommandInfo.h"

class AttributeAdd : public Command {
   public:
    AttributeAdd(const CommandInfo& info) : Command(info) {}
    int exec(const std::vector<std::string>& args) override;
};

class AttributeRemove : public Command {
   public:
    AttributeRemove(const CommandInfo& info) : Command(info) {}
    int exec(const std::vector<std::string>& args) override;
};

class AttributeSet : public Command {
   public:
    AttributeSet(const CommandInfo& info) : Command(info) {}
    int exec(const std::vector<std::string>& args) override;
};
