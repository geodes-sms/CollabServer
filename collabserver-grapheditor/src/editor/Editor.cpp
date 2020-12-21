#include "editor/Editor.h"

#include <cassert>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "editor/CommandInfoPool.h"
#include "editor/commands/AttributeCommands.h"
#include "editor/commands/EdgeCommands.h"
#include "editor/commands/GraphCommands.h"
#include "editor/commands/UserCommands.h"
#include "editor/commands/VertexCommands.h"
#include "utils/utils.h"

// Font: shadow
// See: http://www.patorjk.com/software/taag/#p=display&f=Shadow&t=GraphEditor
#define WELCOME_MENU_TEXT                                                                \
    "________________________________________________________________________________\n" \
    "                                                                                \n" \
    "          ___|                 |       ____|     |_) |                          \n" \
    "         |      __| _` | __ \\  __ \\    __|    _` | | __|  _ \\   __|          \n" \
    "         |   | |   (   | |   | | | |   |     (   | | |   (   | |                \n" \
    "        \\____|_|  \\__,_| .__/ _| |_|  _____|\\__,_|_|\\__|\\___/ _|           \n" \
    "                        _|                                                      \n" \
    "________________________________________________________________________________"

static void addCmd(Command* cmd, std::map<std::string, Command*>& commands) {
    commands[cmd->getName()] = cmd;
    if (cmd->getName() != cmd->getShortName()) {
        commands[cmd->getShortName()] = cmd;
    }
}

Editor::Editor() {
    CommandInfoPool pool;
    pool.loadFromFile("resources/commands.csv");

    // User
    addCmd(new ConnectCommand(pool.get("CONNECT")), _commands);
    addCmd(new DisconnectCommand(pool.get("DISCONNECT")), _commands);
    addCmd(new QuitCommand(pool.get("QUIT")), _commands);
    addCmd(new InfoCommand(pool.get("INFO")), _commands);
    addCmd(new HelpCommand(pool.get("HELP")), _commands);
    addCmd(new UglyCommand(pool.get("UGLY")), _commands);

    // Data
    addCmd(new CreateDataCommand(pool.get("CREA_DATA")), _commands);
    addCmd(new JoinDataCommand(pool.get("JOIN_DATA")), _commands);
    addCmd(new LeaveDataCommand(pool.get("LEAVE_DATA")), _commands);

    // Edge
    addCmd(new EdgeAddCommand(pool.get("EDGE_ADD")), _commands);
    addCmd(new EdgeRemoveCommand(pool.get("EDGE_REM")), _commands);

    // Attr
    addCmd(new AttributeAdd(pool.get("ATTR_ADD")), _commands);
    addCmd(new AttributeRemove(pool.get("ATTR_REM")), _commands);
    addCmd(new AttributeSet(pool.get("ATTR_SET")), _commands);

    // Vertex
    addCmd(new VertexAddCommand(pool.get("VERTEX_ADD")), _commands);
    addCmd(new VertexRemoveCommand(pool.get("VERTEX_REM")), _commands);
    addCmd(new VertexListCommand(pool.get("VERTEX_LIST")), _commands);
    addCmd(new VertexInfoCommand(pool.get("VERTEX_INFO")), _commands);

    // Graph
    addCmd(new GraphShowCommand(pool.get("GRAPH_SHOW")), _commands);
    addCmd(new GraphInfoCommand(pool.get("GRAPH_INFO")), _commands);
    addCmd(new GraphDumpCommand(pool.get("GRAPH_DUMP")), _commands);
}

Editor::~Editor() {
    this->stop();
    for (auto command : _commands) {
        if (command.second->getName() == command.first) {
            delete command.second;
        }
    }
}

void Editor::start() {
    assert(!_commands.empty());
    assert(_running == false);

    if (_running == true) {
        return;
    }
    _running = true;

    std::cout << WELCOME_MENU_TEXT << "\n";
    std::cout << "To display the help, type \"help\"\n";

    std::string word;
    std::string args;

    while (_running) {
        std::cout << "=> ";
        std::cin >> word;
        if (std::cin.eof()) {
            std::cout << "Closing editor...\n";
            this->stop();
        } else if (_commands.count(word) == 1) {
            std::getline(std::cin, args);
            auto argsList = split_no_quotes(args.begin(), args.end());
            _commands[word]->exec(argsList);
        } else {
            std::getline(std::cin, args);
            std::cout << "Unknown command. "
                      << "To see all available commands, type \"help\".\n";
        }
    }
    std::cout << "See you\n";
}

void Editor::stop() { _running = false; }
