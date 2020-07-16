
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

#include "../include/string_utility.h"
#include "../include/init/command_importer.h"
#include "../include/init/mapper.h"
#include "../include/runtime/interpreter.h"


// usage alpharuntime <inputFilename>

int main(int argc, char * argv[])
{
    if (argc != 2) {
        std::cout << "Usage: alpharuntime <inputFilename>" << std::endl;

        return -1;
    }

    std::ifstream inputFile(argv[1]);
    std::stringstream fileBuffer;
    fileBuffer << inputFile.rdbuf();

    CommandImporter commandImporter;

    std::string alphaLang = fileBuffer.str();

    std::string customCommandsBlock = string_utility::getCharsUntil(alphaLang, '}', 1);
    std::vector<CommandData> customCommands = commandImporter.importCommands(customCommandsBlock);

    std::string commandsBlock = string_utility::getCharsUntil(alphaLang, '}', 3 + customCommandsBlock.length());
    std::vector<CommandData> coreCommands = commandImporter.importCommands(commandsBlock);


    Mapper mapper;
    std::vector<std::unique_ptr<Command>> commands;
    for (auto coreCommand : coreCommands) {
        std::unique_ptr<Command> command = std::move(mapper.getNewCommand(coreCommand, customCommands));
        commands.push_back(std::move(command));
    }
    Interpreter interpreter(std::move(commands));
    interpreter.execute();

    return 0;
}

