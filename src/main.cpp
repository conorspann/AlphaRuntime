
#include "../include/init/mapper.h"
#include "../include/runtime/interpreter.h"

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>



std::string getCharsUntil(std::string sourceStr, char delimiter, int startIndex=0)
{
    std::string resultStr;
    for (int charIndex = startIndex; charIndex < sourceStr.length(); charIndex++) {
        if (sourceStr[charIndex] == delimiter) {
            break;
        }
        resultStr += sourceStr[charIndex];
    }

    return resultStr;
}

std::vector<std::string> explode(std::string sourceStr, char delimiter)
{
    std::vector<std::string> explodedResult;
    std::string currentStr;
    for (int charIndex = 0; charIndex < sourceStr.length(); charIndex++) {
        if (sourceStr[charIndex] == delimiter) {
            explodedResult.push_back(currentStr);
            currentStr = "";

            continue;
        }
        currentStr += sourceStr[charIndex];
    }
    if (!currentStr.empty()) {
        explodedResult.push_back(currentStr);
    }

    return explodedResult;
}



std::vector<CommandData> importCommands(std::string alphaLangBlock)
{
    if (alphaLangBlock.length() < 2) { // {} = 2
        // throw malformatted exception
    }

    std::vector<std::string> commandsList = explode(alphaLangBlock, ';');

    std::vector<CommandData> customCommands;

    for (auto commandStr : commandsList) {

        std::string lineNumberStr = getCharsUntil(commandStr, ']', 1);
        int lineNumber = std::stoi(lineNumberStr);

        std::string commandName = getCharsUntil(commandStr, '(', 2 + lineNumberStr.length());


        std::vector<std::string> params;
        std::string paramStr = getCharsUntil(commandStr, ')', 3 + lineNumberStr.length() + commandName.length());
        if (!paramStr.empty()) {
            params = explode(paramStr, ',');
        }

        CommandData commandData(lineNumber, commandName, params);
        customCommands.push_back(commandData);
    }

    return customCommands;
}




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

    std::string alphaLang = fileBuffer.str();

    std::string customCommandsBlock = getCharsUntil(alphaLang, '}', 1);
    std::vector<CommandData> customCommands = importCommands(customCommandsBlock);

    std::string commandsBlock = getCharsUntil(alphaLang, '}', 3 + customCommandsBlock.length());
    std::vector<CommandData> coreCommands = importCommands(commandsBlock);


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

