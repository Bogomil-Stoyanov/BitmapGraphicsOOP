

#ifndef BITMAPGRAPHICS_COMMAND_H
#define BITMAPGRAPHICS_COMMAND_H

enum class CommandType{
    ADD,
    CLOSE,
    COLLAGE,
    ERROR,
    EXIT,
    GRAYSCALE,
    HELP,
    LOAD,
    MONOCHROME,
    NEGATIVE,
    ROTATE,
    SAVE_AS,
    SAVE,
    SESSION_INFO,
    SWITCH,
    UNDO
};

class Command {
public:
    virtual ~Command();
    Command(CommandType commandType);

private:
    CommandType commandType;

public:
    CommandType getCommandType() const;
};


#endif //BITMAPGRAPHICS_COMMAND_H
