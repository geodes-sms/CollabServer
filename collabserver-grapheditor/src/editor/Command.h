#pragma once

#include <string>
#include <vector>

#include "CommandInfo.h"

/**
 * \brief
 * Command interface. (Command design pattern)
 *
 * Any command usable in editor implements this interface.
 */
class Command {
   private:
    std::string _name;
    std::string _shortname;
    std::string _usage;
    std::string _description;

   protected:
    Command(const CommandInfo& info) {
        _name = info.getName();
        _shortname = info.getShortname();
        _usage = info.getUsage();
        _description = info.getDescription();
    }

   public:
    virtual ~Command() = default;
    virtual int exec(const std::vector<std::string>& args) = 0;

   public:
    const std::string& getName() const { return _name; }
    const std::string& getShortName() const { return _shortname; }
    const std::string& getUsage() const { return _usage; }
    const std::string& getDescription() const { return _description; }
};
