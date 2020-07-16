
#ifndef COMMAND_IMPORTER_H
#define COMMAND_IMPORTER_H

#include "command_data.h"

class CommandImporter{
public:
    std::vector<CommandData> importCommands(std::string alphaLangBlock);
};

#endif // COMMAND_IMPORTER_H
