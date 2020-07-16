
#include <string>
#include <vector>

#include "../../include/init/command_importer.h"
#include "../../include/init/command_data.h"
#include "../../include/string_utility.h"


std::vector<CommandData> CommandImporter::importCommands(std::string alphaLangBlock)
{
    if (alphaLangBlock.length() < 2) { // {} = 2
        // throw malformatted exception
    }

    std::vector<std::string> commandsList = string_utility::explode(alphaLangBlock, ';');

    std::vector<CommandData> customCommands;

    for (auto commandStr : commandsList) {

        std::string lineNumberStr = string_utility::getCharsUntil(commandStr, ']', 1);
        int lineNumber = std::stoi(lineNumberStr);

        std::string commandName = string_utility::getCharsUntil(commandStr, '(', 2 + lineNumberStr.length());


        std::vector<std::string> params;
        std::string paramStr = string_utility::getCharsUntil(commandStr, ')', 3 + lineNumberStr.length() + commandName.length());
        if (!paramStr.empty()) {
            params = string_utility::explode(paramStr, ',');
        }

        CommandData commandData(lineNumber, commandName, params);
        customCommands.push_back(commandData);
    }

    return customCommands;
}

