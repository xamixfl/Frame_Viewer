#ifndef BASECOMMAND_HPP
#define BASECOMMAND_HPP

class BaseCommand
{
public:
    virtual ~BaseCommand() = default;

    virtual void execute() = 0;

protected:
    BaseCommand() = default;
};

#endif // BASECOMMAND_HPP
