

#ifndef BITMAPGRAPHICS_SAVEASCOMMAND_H
#define BITMAPGRAPHICS_SAVEASCOMMAND_H

#include <string>
#include "Command.h"


class SaveAsCommand : public Command{


private:
    std::string path;

public:
    explicit SaveAsCommand(std::string path);

    const std::string &getPath() const;
};


#endif //BITMAPGRAPHICS_SAVEASCOMMAND_H
